//
// Created by Harper on 4/24/21.
//

#ifndef LEETCODE_LC188_H
#define LEETCODE_LC188_H

#include <vector>
#include <queue>

using namespace std;

namespace lc188 {
    class Solution {
    public:
        int maxProfit(int k, vector<int> &prices) {
            // find all the pivot points
            int length = prices.size();

            priority_queue<int, std::vector<int>, std::less<int>> profits;

            // Find increasing sequences


            int result = 0;
            for (int i = 0; i < k && !profits.empty(); ++i) {
                result += profits.top();
                profits.pop();
            }
            return result;
        }
    };

    void run() {

    }
}

#endif //LEETCODE_LC188_H
