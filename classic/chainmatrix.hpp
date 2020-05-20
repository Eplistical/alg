#ifndef _CHAINMATRIX_HPP
#define _CHAINMATRIX_HPP

#include <vector>
#include <climits>

using namespace std;

namespace {

    int chainmatrix(const vector<int>& m) {
        /*
         * input m = [m0, m1, m2, ..., mN],
         *  return the minimum cost to perform a chain matrix multiplication A0 * A1 * ... * A_N-1, 
         *  where Aj is of shape m_j * m_j+1
         *
         *  cost is measured by # of multiplication op needed
         */

        const int N = m.size() - 1;
        vector< vector<int> > dp(N, vector<int>(N, INT_MAX));

        // F(j,k) : opt cost for Aj * A_j+1 * ... * Ak
        for (int l(0); l < N; ++l) {
            for (int j(0); j < N - l; ++j) {
                int k = j + l;
                if (l == 0) {
                    dp[j][k] = 0;
                }
                for (int p(j); p < k; ++p) {
                    // F(j,k) => F(j,p) + F(p+1,k) + m_j * m_p+1 * m_k+1
                    dp[j][k] = min(dp[j][k], 
                            dp[j][p] + dp[p+1][k] + m[j] * m[p+1] * m[k+1]);
                }
            }
        }
        return dp[0][N-1];
    }
};

#endif // _CHAINMATRIX_HPP
