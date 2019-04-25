#ifndef _QUICKSELECT_HPP
#define _QUICKSELECT_HPP

#include <vector>
#include <random>

using namespace std;

namespace {

    int quickselect(vector<int>& nums, const int k) {
        const int N = nums.size();
        // randomly pick v
        default_random_engine gen;
        const int v = nums[uniform_int_distribution<int>(0, N-1)(gen)]; 

        vector<int> numL, numR;
        for (int i(0); i < N; ++i) {
            if (nums[i] < v) {
                numL.push_back(nums[i]);
            }
            else if (nums[i] > v) {
                numR.push_back(nums[i]);
            }
        }

        if (k < numL.size()) {
            return quickselect(numL, k);
        }
        else if (k >= N - numR.size()) {
            return quickselect(numR, k - N + numR.size());
        }
        else {
            return v;
        }
    }
};

#endif // _QUICKSELECT_HPP
