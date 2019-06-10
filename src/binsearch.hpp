#ifndef _BINSEARCH_HPP
#define _BINSEARCH_HPP

#include <vector>
#include <random>

using namespace std;

namespace {
    int _binsearch(const vector<int>& nums, const int target, const int l, const int r) {
        // implement binary search algorithm
        if (l > r) {
            return -1;
        }
        else if (l == r) {
            if (target == nums[l]) {
                return l;
            }
            else {
                return -1;
            }
        }
        else {
            const int m = (l + r) / 2;
            if (nums[m] == target) {
                return m;
            }
            else if (nums[m] > target) {
                return _binsearch(nums, target, l, m-1);
            }
            else {
                return _binsearch(nums, target, m+1, r);
            }
        }
    }

    int binsearch(const vector<int>& nums, const int target) {
        // binary search, nums has already been increasingly sorted
        // return index of target number
        // if not found, return -1
        const int N = nums.size();
        if (N == 0) {
            return -1;
        }
        else if (nums[0] > target or nums[N-1] < target) {
            return -1;
        }
        else {
            return _binsearch(nums, target, 0, N-1);
        }
    }
};

#endif // _BINSEARCH_HPP
