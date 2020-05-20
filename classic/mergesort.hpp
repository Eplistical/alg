#ifndef _MERGESORT_HPP
#define _MERGESORT_HPP

#include <vector>

using namespace std;

namespace {
    vector<int> _mergesort_combine(const vector<int>& v1, const vector<int>& v2) {
        const int N1 = v1.size(), N2 = v2.size();
        vector<int> rst(N1 + N2);
        int i = 0, j = 0;

        while (i < N1 and j < N2) {
            if (v1[i] > v2[j]) {
                rst[i+j] = v2[j];
                ++j;
            }
            else {
                rst[i+j] = v1[i];
                ++i;
            }
        }

        if (i == N1) {
            while (j < N2) {
                rst[i+j] = v2[j];
                ++j;
            }
        }
        else if (j == N2) {
            while (i < N1) {
                rst[i+j] = v1[i];
                ++i;
            }
        }
        return rst;
    }

    vector<int> mergesort(const vector<int>& nums) {
        const int N = nums.size();
        if (N == 1) {
            return nums;
        } 
        else {
            return _mergesort_combine(
                    mergesort(vector<int>(nums.begin(), nums.begin() + N / 2)),
                    mergesort(vector<int>(nums.begin() + N / 2, nums.end()))
                    );
        }
    }

};

#endif // _MERGESORT_HPP
