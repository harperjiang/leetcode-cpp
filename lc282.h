//
// Created by harper on 4/30/21.
//

#ifndef LEETCODE_LC282_H
#define LEETCODE_LC282_H

#include <vector>
#include <string>
#include <array>
#include <math.h>

using namespace std;

namespace lc282 {

    class Solution {
        constexpr static int FACTOR[]{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    public:
        vector<array<int, 4>> forward(string num, int limit) {

        }

        vector<array<int, 4>> backward(string num, int limit) {

        }

        int eval(vector<int> &exp) {

        }

        string print(string num, int inst) {

        }

        vector<string> addOperators(string num, int target) {
            int length = num.size();

            int forward_len = length / 2;
            int backward_len = length - forward_len;

            auto forward_choices = forward(num, forward_len);
            auto backward_choices = backward(num, backward_len);

            vector<string> result;
            for (auto &left: forward_choices) {
                for (auto &right: backward_choices) {
                    // merge
                    vector<int> exp;
                    int inst;
                    exp.push_back(left[0]);
                    exp.push_back(left[2]);
                    exp.push_back(left[1] * FACTOR[(int) log10(right[0]) + 1] + right[0]);
                    exp.push_back(right[2]);
                    exp.push_back(right[1]);
                    if (eval(exp) == target) {
                        int inst = right[2];
                        inst += left[2] << (backward_len * 2);
                        result.push_back(print(num, inst));
                    }
                    // multiply
                    exp[2] = left[1];
                    exp[3] = 1;
                    exp[4] = right[0];
                    exp.push_back(right[2]);
                    exp.push_back(right[1]);
                    if (eval(exp) == target) {
                        int inst = right[2];
                        inst += 1 << ((backward_len - 1) * 2);
                        inst += left[2] << (backward_len * 2);
                        result.push_back(print(num, inst));
                    }
                    // plus
                    exp[3] = 2;
                    if (eval(exp) == target) {
                        int inst = right[2];
                        inst += 2 << ((backward_len - 1) * 2);
                        inst += left[2] << (backward_len * 2);
                        result.push_back(print(num, inst));
                    }
                    // minus
                    exp[3] = 3;
                    if (eval(exp) == target) {
                        int inst = right[2];
                        inst += 3 << ((backward_len - 1) * 2);
                        inst += left[2] << (backward_len * 2);
                        result.push_back(print(num, inst));
                    }
                }
            }
            return result;
        }
    };

    void run() {

    }
}

#endif //LEETCODE_LC282_H
