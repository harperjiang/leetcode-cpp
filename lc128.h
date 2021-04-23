//
// Created by Harper on 4/23/21.
//

#ifndef LEETCODE_LC128_H
#define LEETCODE_LC128_H

#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

namespace lc128 {
    class Solution {
    public:
        int longestConsecutive(vector<int>& nums) {
            // lower bound, range length
            unordered_map<int, pair<int,int>> lower;
            // upper bound, range length
            unordered_map<int, pair<int,int>> upper;

            int max_range = 0;
            for(auto num: nums) {
                if(lower.find(num) != lower.end() || upper.find(num)!= upper.end()) {
                    continue;
                }

                auto lfound = lower.find(num+1);
                auto ufound = upper.find(num-1);

                if(lfound!= lower.end() && ufound != upper.end()) {
                    // This number connect two ranges
                    int lower_bound = ufound->second.first;
                    int upper_bound = lfound->second.second;
                    lower.erase(lfound);
                    upper.erase(ufound);
                    lower[lower_bound].second = upper_bound;
                    upper[upper_bound].first = lower_bound;
                    int range = upper_bound-lower_bound+1;
                    if(range >max_range) {
                        max_range = range;
                    }
                } else if(lfound!= lower.end()) {
                    // This number extend lower
                    int upper_bound = lfound->second.second;
                    lower.erase(lfound);
                    lower[num] = pair<int,int>(num,upper_bound);
                    upper[upper_bound] = pair<int,int>(num,upper_bound);
                    int range = upper_bound-num+1;
                    if(range >max_range) {
                        max_range = range;
                    }

                } else if(ufound!= upper.end()) {
                    // This number extend upper
                    int lower_bound = ufound->second.first;
                    upper.erase(ufound);
                    upper[num] = pair<int,int>(lower_bound,num);
                    lower[lower_bound] =pair<int,int>(lower_bound,num);

                    int range = num-lower_bound+1;
                    if(range >max_range) {
                        max_range = range;
                    }
                } else {
                    // This number is independent
                    lower[num] = pair<int,int>(num,num);
                    upper[num] = pair<int,int>(num,num);
                    if(1> max_range) {
                        max_range = 1;
                    }
                }
            }

            return max_range;
        }
    };
//    class Solution {
//    public:
//        int longestConsecutive(vector<int> &nums) {
//            if (nums.size() == 0)
//                return 0;
//
//            int i, c = 1, res = 1;
//            set<int> s;
//            for (i = 0; i < nums.size(); i++)
//                s.insert(nums[i]);
//            vector<int> v;
//            for (auto x: s)
//                v.push_back(x);
//
//            for (i = 1; i < v.size(); i++) {
//                if (i > 0 && v[i] == v[i - 1] + 1) {
//                    c++;
//                    res = max(res, c);
//                } else
//                    c = 1;
//            }
//            return res;
//        }
//    };

    void run() {
        Solution solution;
        {
            auto nums = vector<int>{100, 4, 200, 1, 3, 2};
            auto result = solution.longestConsecutive(nums);
            assert(result == 4);
        }
        {
            auto nums = vector<int>{-7, -1, 3, -9, -4, 7, -3, 2, 4, 9, 4, -9, 8, -7, 5, -1, -7};
            auto result = solution.longestConsecutive(nums);
            assert(result == 4);
        }
        {
            auto nums = vector<int>{0, 3, 7, 2, 5, 8, 4, 6, 0, 1};
            auto result = solution.longestConsecutive(nums);
            assert(result == 9);
        }
    }
}
#endif //LEETCODE_LC128_H
