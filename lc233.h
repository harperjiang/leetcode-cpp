//
// Created by Harper on 4/27/21.
//

#ifndef LEETCODE_LC233_H
#define LEETCODE_LC233_H

#include <math.h>

namespace lc233 {
    class Solution {
    public:

        constexpr static int RECORDS[10]{0, 1, 20, 300, 4000, 50000, 600000, 7000000, 80000000, 900000000};
        constexpr static int DIGITS[10]{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

        int countDigitOne(int n) {
            // First get digits
            if(n == 0) {
                return 0;
            }
            int digits = (int)log10(n);
            int remain = n;
            int sum = 0;
            int count1 = 0;
            for (int i = digits; i >= 0; i--) {
                int step_sum = 0;
                int digit = remain / DIGITS[i];
                remain %= DIGITS[i];

                if (digit > 1) {
                    step_sum += DIGITS[i];
                    step_sum += digit * RECORDS[i];
                } else if (digit == 1) {
                    count1 += 1;
                    step_sum += RECORDS[i];
                    step_sum += remain + 1;
                }

                sum += step_sum;
            }
            return sum;
        }
    };

    void run() {
        Solution solution;
        assert(6 == solution.countDigitOne(13));
        assert(0 == solution.countDigitOne(0));
        assert(12 == solution.countDigitOne(20));
        assert(21 == solution.countDigitOne(100));
        assert(301 == solution.countDigitOne(1000));
    }
}

#endif //LEETCODE_LC233_H
