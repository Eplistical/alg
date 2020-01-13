#ifndef _KNAPSACK_HPP
#define _KNAPSACK_HPP

#include <vector>

using namespace std;

namespace {

    int knapscak01(const vector<int>& v, const vector<int>& w, const int W) {
        vector<int> dp(W+1, 0);
        dp[0] = 0;
        for (int i(1); i <= W; ++i) {
            for (int j(0); j < w.size(); ++j) {
                if (w[j] <= i and dp[i] < dp[i - w[j]] + v[j]) {
                    dp[i] = dp[i - w[j]] + v[j];
                }
            }
        }
        ioer::info(dp);
        return dp[W];
    }
};

#endif // _KNAPSACK_HPP
