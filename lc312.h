//
// Created by harper on 5/6/21.
//

#ifndef LEETCODE_LC312_H
#define LEETCODE_LC312_H

#include <vector>
#include <queue>
#include <cassert>
#include <cstring>
#include <iostream>

using namespace std;

namespace lc312 {

    class Solution {
        int dp[502][502];
    public:
        int range(vector<int> &nums, int i, int j) {
            if (i == j) {
                return 0;
            }
            if (i == j - 1) {
                return nums[i - 1] * nums[i] * nums[i + 1];
            }
            if (dp[i][j] != -1) {
                return dp[i][j];
            }
            int result=-1;
            for (int k = i; k < j; ++k) {
                result = std::max(result, range(nums, i, k) + range(nums, k + 1, j) + nums[i - 1] * nums[k] * nums[j]);
            }
            dp[i][j] = result;
            return result;
        }

        int maxCoins(vector<int> &nums) {
            if (nums.size() == 1) {
                return nums[0];
            }
            if (nums.size() == 2) {
                return nums[0] * nums[1] + std::max(nums[0], nums[1]);
            }

            nums.push_back(1);
            nums.insert(nums.begin(), 1);
            int length = nums.size();
            memset(dp, -1, sizeof(dp));

            int result = range(nums, 1, length - 1);
            return result;
        }
    };

    void run() {
        Solution solution;

        {
            vector<int> nums{3, 1, 5, 8};
            assert(167 == solution.maxCoins(nums));
        }
        {
            vector<int> nums{1, 5};
            assert(10 == solution.maxCoins(nums));
        }
        {
            vector<int> nums{9, 76, 64, 21, 97, 60};
            assert(1086136 == solution.maxCoins(nums));
        }
    }
}

#endif //LEETCODE_LC312_H
