//
// Created by harper on 4/22/21.
//

#ifndef LEETCODE_LC6_H
#define LEETCODE_LC6_H

#include <string>
#include <iostream>

using namespace std;

namespace lc6 {

    class Solution {
    public:
        string convert(string s, int numRows) {
            int len = s.length();
            int period = 2 * numRows - 2;

            if(period == 0) {
                return s;
            }
            string result;
            // First line
            for (int i = 0; i < len; i += period) {
                result.append(1,s[i]);
            }
            // Middle
            for (int r = 1; r < numRows - 1; ++r) {
                for (int i = r; i < len; i += period) {
                    // First char in the group
                    result.append(1,s[i]);
                    // second char in the group
                    int idx = 2 * ((numRows-1+ period*((i / period)))) - i;
                    if (idx < len) {
                        result.append(1,s[idx]);
                    }
                }
            }
            // Last line
            for (int i = numRows - 1; i < len; i += period) {
                result.append(1,s[i]);
            }

            return result;
        }
    };

    void run() {
//        cout << Solution().convert("PAYPALISHIRING", 3) << '\n';
        cout << Solution().convert("A", 1) << '\n';
    }
}

#endif //LEETCODE_LC6_H
