//
// Created by harper on 4/22/21.
//

#ifndef LEETCODE_LC8_H
#define LEETCODE_LC8_H

#include <iostream>
#include <string>

using namespace std;

namespace lc8 {
    class Solution {
    public:
        int myAtoi(string s) {
            int buffer[200];
            int factor[]{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
            int buffer_index = 0;
            bool negative = false;

            // 0: beginning
            // 1: reading leading space
            // 2: reading leading 0
            // 3: read subsequent numbers
            // 4: after sign
            int state = 0;

            // Parse
            int read_index = 0;
            while (read_index < s.size()) {
                int current = s[read_index];
                if (current == '+' || current == '-') {
                    if (state == 0 || state == 1) {
                        negative = s[read_index] == '-';
                        state = 4;
                        read_index++;
                    } else {
                        break;
                    }
                } else if (current == ' ') {
                    if (state == 0 || state == 1) {
                        state = 1;
                        read_index++;
                    } else {
                        break;
                    }
                } else if (current == '0') {
                    if (state == 0 || state == 1 || state == 2 || state == 4) {
                        state = 2;
                        read_index++;
                    } else {
                        buffer[buffer_index++] = current;
                        read_index++;
                    }
                } else if (current > '0' && current <= '9') {
                    state = 3;
                    buffer[buffer_index++] = current;
                    read_index++;
                } else {
                    break;
                }
            }
            // Convert
            buffer_index--;
            if (buffer_index >= 10) { // Off bound
                return negative ? INT32_MIN : INT32_MAX;
            }
            uint64_t sum = 0;
            for (int i = buffer_index; i >= 0; i--) {
                sum += (uint64_t)(buffer[i] - '0') * factor[buffer_index - i];
                if (sum > INT32_MAX) { // overflow
                    return negative ? INT32_MIN : INT32_MAX;
                }
            }
            // Check if off bound
            uint32_t intsum = (uint32_t)sum;
            return negative ? -sum : sum;
        }
    };

    void run() {
        std::cout << Solution().myAtoi("-00000000001") << '\n';
        std::cout << Solution().myAtoi("   -000000000021323") << '\n';
    }

}

#endif //LEETCODE_LC8_H
