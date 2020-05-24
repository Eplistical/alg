#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <mutex>
#include <thread>
#include <random>
#include <cassert>
#include <chrono>
#include <condition_variable>
#include <string>
#include <map>
using namespace std;

/*
 * dispatcher-worker model FIFO job manager 
 */

// thread basics
int Nworker = 8; 
vector<thread> threadPool;
map<thread::id, int> thIdIdx;
mutex mtxIO;
mutex mtxIdx;

// buffer
queue<string> inpBuf;
mutex mtxBuf;
condition_variable bufEmpty;


void do_work(const string& inp) {
    static default_random_engine generator;
    static uniform_int_distribution<int> dist(400, 1600);
    // spend for a while working on the input
    this_thread::sleep_for(chrono::milliseconds(dist(generator)));
}


void run_worker(void) {
    {
        // register current thread
        lock_guard<mutex> lock(mtxIdx);
        thIdIdx.insert(make_pair(this_thread::get_id(), thIdIdx.size() + 1));
    }

    while (true) {
        string inp;
        {
            // fetch a job from buf
            unique_lock<mutex> lock(mtxBuf);
            while (inpBuf.empty()) {
                bufEmpty.wait(lock);
            }
            inp = inpBuf.front();
            inpBuf.pop();
        }

        {
            lock_guard<mutex> lock(mtxIO);
            cout << "worker " << thIdIdx.at(this_thread::get_id()) << " is processing " << inp << endl;
        }
        do_work(inp);
    }

}


void run_dispatcher(void) {
    string inp;
    while (true) {
        cin >> inp;
        if (!cin.eof()) {
            // push input into buffer
            lock_guard<mutex> lock(mtxBuf);
            inpBuf.push(inp);
            bufEmpty.notify_one();
        }
    }
}



int main(int argc, char** argv) {
    // spawn dispatcher thread
    threadPool.push_back(thread(run_dispatcher));

    // spawn workers threads
    for (int i(0); i < Nworker; ++i) {
        threadPool.push_back(thread(run_worker));
    }

    // ending
    for (auto& t : threadPool) {
        t.join();
    }
    return 0;
}
