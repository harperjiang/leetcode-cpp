//
// Created by harper on 5/7/21.
//

#ifndef LEETCODE_LC327_H
#define LEETCODE_LC327_H

#include <vector>
#include <cassert>
#include <algorithm>
#include <unordered_map>

using namespace std;

namespace lc327 {

    class BIT {
    private:
        vector<int64_t> data_;
    public:
        BIT(int size) {
            data_.resize(size);
            data_.assign(size, 0);
        }

        void add(int index, int value) {
            int i = index;
            while (i < data_.size()) {
                data_[i] += value;
                i += i | (i + 1);
            }
        }

        int64_t query(int index) {
            long res = 0;
            int i = index;
            while (i > 0) {
                res += data_[i];
                i = (i & (i + 1)) - 1;
            }
            return res;
        }
    };

    class Solution {
    public:
        int countRangeSum(vector<int> &nums, int lower, int upper) {

            vector<int64_t> sums;
            for (auto &num:nums) {
                if (sums.empty()) {
                    sums.push_back(num);
                } else {
                    sums.push_back(num + sums.back());
                }
            }

            vector<int64_t> sorted;
            sorted.insert(sorted.begin(), sums.begin(), sums.end());
            sort(sorted.begin(), sorted.end());

            unordered_map<int64_t, int> backind;
            for (int i = 0; i < sums.size(); ++i) {
                backind[sums[i]] = i;
            }

            BIT bit(nums.size());

            int result = 0;

            for (auto sum: sums) {
                int uv = sum - lower;
                int lv = sum - upper;

                int uindex = lower_bound(sorted.begin(), sorted.end(), uv) - sorted.begin();
                int lindex = upper_bound(sorted.begin(), sorted.end(), lv) - sorted.begin();

                result += bit.query(uindex) - bit.query(lindex);

                bit.add(backind[sum], 1);
            }
            return result;
        }
    };

    void run() {
        Solution solution;
        {
            vector<int> nums{-2, 5, -1};
            assert(3 == solution.countRangeSum(nums, -2, 2));
        }
        {
            vector<int> nums{0};
            assert(1 == solution.countRangeSum(nums, 0, 0));
        }
        {
            vector<int> nums{0, 0};
            assert(3 == solution.countRangeSum(nums, 0, 0));
        }
        {
            vector<int> nums{-1, 1};
            assert(1 == solution.countRangeSum(nums, 0, 0));
        }
    }
}
#endif //LEETCODE_LC327_H
