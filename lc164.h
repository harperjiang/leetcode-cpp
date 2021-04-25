//
// Created by Harper on 4/24/21.
//

#ifndef LEETCODE_LC164_H
#define LEETCODE_LC164_H

#include <vector>

using namespace std;

namespace lc164 {

    class Solution {
    public:
        int maximumGap(vector<int> &nums) {
            if (nums.size() < 2) {
                return 0;
            }

            int max = INT32_MIN;
            int min = INT32_MAX;
            for (auto &num: nums) {
                if (num > max) {
                    max = num;
                }
                if (num < min) {
                    min = num;
                }
            }
            if (max == min) {
                return 0;
            }
            int region = max - min;
            double width = (double) region / nums.size();
            int num_bucket = (int) (region / width) + 1;

            int bucket_min[num_bucket];
            int bucket_max[num_bucket];
            for (int i = 0; i < num_bucket; ++i) {
                bucket_max[i] = INT32_MIN;
                bucket_min[i] = INT32_MAX;
            }
            for (auto &num: nums) {
                int bucket_idx = (int) ((num - min) / width);
                if (bucket_max[bucket_idx] < num) {
                    bucket_max[bucket_idx] = num;
                }
                if (bucket_min[bucket_idx] > num) {
                    bucket_min[bucket_idx] = num;
                }
            }

            int res = 0;
            int prev = bucket_max[0];
            for (int i = 1; i < num_bucket; ++i) {
                auto lower = bucket_min[i];
                if (lower != INT32_MAX) {
                    int space = lower - prev;
                    if (res < space) {
                        res = space;
                    }
                    prev = bucket_max[i];
                }
            }
            return res;
        }
    };

    void run() {
        Solution solution;
//        {
//            vector<int> nums{3, 6, 9, 1};
//            int gap = solution.maximumGap(nums);
//            assert(gap == 3);
//        }
//        {
//            vector<int> nums{1, 1, 1, 1};
//            int gap = solution.maximumGap(nums);
//            assert(gap == 0);
//        }
        {
            vector<int> nums{1, 2, 2, 1};
            int gap = solution.maximumGap(nums);
            assert(gap == 1);
        }
    }
}
#endif //LEETCODE_LC164_H
