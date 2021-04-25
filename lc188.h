//
// Created by Harper on 4/24/21.
//

#ifndef LEETCODE_LC188_H
#define LEETCODE_LC188_H

#include <vector>
#include <queue>
#include <cassert>

using namespace std;

namespace lc188 {
    class Solution {
    public:
        int maxProfit(int k, vector<int> &prices) {
            // find all the pivot points
            int length = prices.size();

            vector<int> starts;
            vector<int> ends;

            // Find increasing sequences
            int prev = 0;
            for (int i = 1; i < length; ++i) {
                if (prices[i] <= prices[i - 1]) {
                    // an increase ends
                    int profit = prices[i - 1] - prices[prev];
                    if (profit > 0) {
                        starts.push_back(prev);
                        ends.push_back(i - 1);
                    }
                    prev = i;
                }
            }
            int profit = prices[length - 1] - prices[prev];
            if (profit > 0) {
                starts.push_back(prev);
                ends.push_back(length - 1);
            }

            // Construct graphs
            int sec_length = starts.size();
            int transition[length][length];

            for (int i = 0; i < sec_length; ++i) {
                transition[starts[i]][ends[i]+1] = prices[ends[i]] - prices[starts[i]];
                for (int j = i + 1; j < sec_length; ++j) {
                    if()
                }
            }

            int result = 0;
            return result;
        }
    };

    void run() {
        Solution solution;

//        {
//            vector<int> prices{2,4,1};
//            assert(2 == solution.maxProfit(2,prices));
//        }
        {
            vector<int> prices{3, 2, 6, 5, 0, 3};
            assert(7 == solution.maxProfit(2, prices));
        }
    }
}

#endif //LEETCODE_LC188_H
