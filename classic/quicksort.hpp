#ifndef _QUICKSORT_HPP
#define _QUICKSORT_HPP

#include <vector>
#include <random>

using namespace std;

namespace {
    void _quicksort_impl(vector<int>& nums, int start, int end) {
        if (end - start >= 1) {
            // pick pivot
            default_random_engine gen;
            int p = uniform_int_distribution<int>(start, end)(gen); 

            // move pivot to correct position
            int i = start, j = end;
            while (i != p or j != p) {
                while (i < p and nums[i] < nums[p]) {
                    i += 1;
                }
                while (j > p and nums[j] >= nums[p]) {
                    j -= 1;
                }

                if (i != p and j != p) {
                    swap(nums[i], nums[j]);
                }
                else if (i == p) {
                    swap(nums[p], nums[j]);
                    p = j;
                }
                else if (j == p) {
                    swap(nums[p], nums[i]);
                    p = i;
                }
            }

            // D&C
            if (p != 0) {
                _quicksort_impl(nums, start, p-1);
            }
            if (p != end) {
                _quicksort_impl(nums, p+1, end);
            }
        }
    }

    void quicksort(vector<int>& nums) {
        // inplace quick sort
        const int N = nums.size();
        _quicksort_impl(nums, 0, N-1);
    }
};

#endif // _QUICKSORT_HPP
