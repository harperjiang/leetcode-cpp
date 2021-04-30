//
// Created by Harper on 4/28/21.
//

#ifndef LEETCODE_239_H
#define LEETCODE_239_H

#include <vector>
#include <cassert>
#include <deque>

using namespace std;

namespace lc239 {
    class Solution {
    public:
        vector<int> maxSlidingWindow(vector<int>& nums, int k) {
            vector<int> ans;
            deque<int> de;
            int i=0,j=0;

            while(j<nums.size())
            {
                while(!de.empty() && de.back()<nums[j])
                    de.pop_back();
                de.push_back(nums[j]);

                if(j-i+1<k) j++;
                else{
                    ans.push_back(de.front());
                    if(nums[i] == de.front())
                        de.pop_front();
                    i++;
                    j++;
                }
            }
            return ans;
        }
    };

    void run() {
        Solution solution;

//        {
//            vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};
//            vector<int> expected{3, 3, 5, 5, 6, 7};
//            assert(expected == solution.maxSlidingWindow(nums, 3));
//        }
//        {
//            vector<int> nums{1};
//            vector<int> expected{1};
//            assert(expected == solution.maxSlidingWindow(nums, 1));
//        }
//        {
//            vector<int> nums{1, -1};
//            vector<int> expected{1, -1};
//            assert(expected == solution.maxSlidingWindow(nums, 1));
//        }
//
//        {
//            vector<int> nums{9, 11};
//            vector<int> expected{11};
//            assert(expected == solution.maxSlidingWindow(nums, 2));
//        }
//        {
//            vector<int> nums{4, -2};
//            vector<int> expected{4};
//            assert(expected == solution.maxSlidingWindow(nums, 2));
//        }
//        {
//            vector<int> nums{1, 3, 1, 2, 0, 5};
//            vector<int> expected{3, 3, 2, 5};
//            assert(expected == solution.maxSlidingWindow(nums, 3));
//        }
        {
            vector<int> nums{9, 10, 9, -7, -4, -8, 2, -6};
            vector<int> expected{10, 10, 9, 2};
            assert(expected == solution.maxSlidingWindow(nums, 5));
        }
    }
}
#endif //LEETCODE_239_H
