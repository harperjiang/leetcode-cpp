//
// Created by harper on 5/7/21.
//

#ifndef LEETCODE_LC315_H
#define LEETCODE_LC315_H

#include <vector>
#include <array>
#include <algorithm>
#include <cassert>

using namespace std;

namespace lc315 {
    class Solution {
    public:
        vector<int> countSmaller(vector<int> &nums) {

            vector<int> result(nums.size());
            array<vector<int>, 100> buckets;

            for (int i = nums.size() - 1; i >= 0; --i) {
                int num = nums[i];
                int bucket_index = num / 256 + 50;

                int counter = 0;
                for (int j = 0; j < bucket_index; ++j) {
                    counter += buckets[j].size();
                }
                // insert into current bucket
                auto &bucket = buckets[bucket_index];
                auto index = lower_bound(bucket.begin(), bucket.end(), num);
                counter += index - bucket.begin();
                bucket.insert(index,num);
                result[i] = counter;
            }

            return result;
        }
    };

    void run() {
        Solution solution;

        {
            vector<int> nums{5, 2, 6, 1};
            vector<int> expect{2, 1, 1, 0};
            auto result = solution.countSmaller(nums);
            assert(result == expect);
        }
        {
            vector<int> nums{-1};
            vector<int> expect{0};
            auto result = solution.countSmaller(nums);
            assert(result == expect);
        }
        {
            vector<int> nums{-1, -1};
            vector<int> expect{0, 0};
            auto result = solution.countSmaller(nums);
            assert(result == expect);
        }
    }
}

#endif //LEETCODE_LC315_H
