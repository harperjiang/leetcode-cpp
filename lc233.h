//
// Created by Harper on 4/27/21.
//

#ifndef LEETCODE_LC233_H
#define LEETCODE_LC233_H

#include <math.h>

namespace lc233 {
    class Solution {
    public:

        constexpr static int RECORDS[10]{0, 1, 21, 321, 4321, 54321, 654321, 7654321, 87654321, 987654321};
        constexpr static int DIGITS[10]{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

        int countDigitOne(int n) {
            // First get digits
            int digits = (int) (log(n) / log(10));
            // 1000-2401
            // 1000-1999 1000+ 321*2
            // 2000-2400 100 + 21*4
            // 2400-2400
            // 2400-2401 1 + 0*1
            // 13
            // 0-9  10+1*1
            // 10-13
            int remain = n;
            int sum = 0;
            for (int i = digits; i >= 0; i--) {
                int digit = remain / DIGITS[i];
                if (digit > 1) {
                    sum += DIGITS[digit];
                } else if (digit == 1) {
                    sum += remain + 1;
                }
                sum += RECORDS[digit] * digit;

                remain %= DIGITS[i];
            }
            return sum;
        }
    };

    void run() {
        Solution solution;
        assert(6 == solution.countDigitOne(13));
        assert(0 == solution.countDigitOne(0));
    }
}

#endif //LEETCODE_LC233_H
