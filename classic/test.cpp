#include <cmath>
#include <cstdlib>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>
#include <cassert>
#include "misc/ioer.hpp"
#include "misc/randomer.hpp"

#include "mergesort.hpp"
#include "quicksort.hpp"
#include "quickselect.hpp"
#include "graph.hpp"
#include "knapsack.hpp"
#include "chainmatrix.hpp"
#include "binsearch.hpp"


int main(int argc, char** argv) {
    if (argc > 1) {
        randomer::seed(atoi(argv[1]));
    }
    else {
        randomer::seed(42);
    }

    /*
    // -- merge sort test
    vector<int> orinums = randomer::vrandint(400000, -100000, 100000); 
    vector<int> nums = orinums;
    ioer::info("mergesort:");
    ioer::info("original nums = ", nums);
    ioer::info("sorted nums = ", mergesort(nums));

    // -- quick sort test
    nums = orinums;
    ioer::info("quicksort:");
    ioer::info("original nums = ", nums);
    quicksort(nums);
    ioer::info("sorted nums = ", nums);
    */

    
    /*
    // -- quick select test
    vector<int> nums = randomer::vrandint(100, -10000000, 10000000); 
    int k= randomer::randint(0, nums.size() - 1);

    ioer::info("quickselect:");
    ioer::info("nums = ", nums);
    ioer::info("k = ", k);
    ioer::info("ans = ", mergesort(nums)[k]);
    ioer::info("rst = ", quickselect(nums, k));
    */

    /*
    // -- graph algorithm test
    Graph G(6);
    G.add_edge(0,2);
    G.add_edge(1,0);
    G.add_edge(1,3);
    G.add_edge(2,4);
    G.add_edge(2,5);
    G.add_edge(3,2);

    ioer::info("G:");
    G.show_adjmat();

    reset_buf(G.size());

    dfs(G);
    ioer::info(visited);
    ioer::info("pre: ", pre);
    ioer::info("post: ", post);

    Graph GR = revGraph(G);
    ioer::info("GR:");
    GR.show_adjmat();
    */

    /*
    vector<int> a { 1,4,8,5,0,3,7,2 };
    priority_queue<int> q(a.begin(), a.end());

    while (not q.empty()) {
        ioer::info(q.top());
        q.pop();
    }
    */

    /*
    // knapsack
    ioer::info("knapsack01 test");
    //vector<int> w { 1,2,2,4,3,5,3,8 };
    //vector<int> v { 1,1,2,3,4,4,5,6 };
    vector<int> w { 1,2,2,3 };
    vector<int> v { 1,1,4,3 };
    int W = 5;
    ioer::info("w = ", w);
    ioer::info("v = ", v);
    ioer::info("W = ", W);
    ioer::info("knapsack01 value = ", knapscak01(v, w, W));
    */

    /*
    // chainmatrix
    ioer::info("chainmatrix test");
    vector<int> m { 50, 20, 1, 10, 100 };
    ioer::info("m = ", m);
    ioer::info("chainmatrix(m) = ", chainmatrix(m));
    */


    // binary search
    int target = 42;
    for (int N(0); N < 20000; ++N) {
        ioer::info("N = ", N);
        for (int itrail(0); itrail < 1; ++itrail) {
            vector<int> nums = randomer::vrandint(N, -1000, 1000);
            unordered_set<int> s(nums.begin(), nums.end());
            copy(s.begin(), s.end(), nums.begin());
            nums.resize(s.size());
            quicksort(nums);

            ioer::info("nums = ", nums);
            int rst = binsearch(nums, target);
            ioer::info("size = ", nums.size(), " rst = ", rst);

            if (rst != -1) {
                assert(nums[rst] == target);
            }
            else {
                assert(find(nums.begin(), nums.end(), target) == nums.end());
            }
        }
    }

    return 0;
}
