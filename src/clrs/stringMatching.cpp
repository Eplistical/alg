#include <vector>
#include <random>
#include <iostream>
#include <string>

using namespace std;

namespace {

    class StringMatching {
        public:
            vector<int> naive(const string& T, const string& P) {
                const int m = T.size();
                const int n = P.size();
                vector<int> rst;
                if (m >= n) {
                    for (int i(0); i < m - n + 1; ++i) {
                        if (isMatch(T, i, P, 0, n)) {
                            rst.push_back(i);
                        }
                    }
                }
                return rst;
            }

       private:
            bool isMatch(const string& s, int j, const string& t, int k, int n) {
                // check if s[j:j+n] and t[k:k+n] matches
                for (int l(0); l < n; ++l) {
                    if (s[j+l] != t[k+l]) {
                        return false;
                    }
                }
                return true;
            }
    };

};


int main(int argc, char** argv) {
    StringMatching s;
    string T = "abcabaabcabac";
    string P = "abc";

    if (argc >= 2) {
        T = argv[1];
        P = argv[2];
    }

    cout << "T = " << T << endl;
    cout << "P = " << P << endl;
    // NAIVE
    vector<int> rst = s.naive(T, P);
    cout << "naive:" << endl;
    for (int x : rst) cout << x << " ";
    cout << endl;
    return 0;
}
