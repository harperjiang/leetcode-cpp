//
// Created by harper on 4/27/21.
//

#ifndef LEETCODE_224_H
#define LEETCODE_224_H

#include <string>
#include <stack>
#include <vector>

using namespace std;

namespace lc224 {
    class Solution {
    public:
        constexpr static int const FACTOR[]{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

        int PREC[256];

        Solution() {
            PREC['+'] = 1;
            PREC['-'] = 1;
            PREC[','] = 2;
            PREC['.'] = 2;
            PREC['('] = 0;
            PREC['#'] = -1;
            PREC[')'] = 10;
        }

        int build_num(vector<int> &input) {
            int sum = 0;
            for (int i = 0; i < input.size(); ++i) {
                sum += input[input.size() - 1 - i] * FACTOR[i];
            }
            return sum;
        }

        void execute_opr(stack<int> &nums, int opr) {
            switch (opr) {
                case '+': {
                    int num2 = nums.top();
                    nums.pop();
                    int num1 = nums.top();
                    nums.pop();
                    nums.push(num1 + num2);
                    break;
                }
                case '-': {
                    int num2 = nums.top();
                    nums.pop();
                    int num1 = nums.top();
                    nums.pop();
                    nums.push(num1 - num2);
                    break;
                }
                case ',': {
                    int num2 = nums.top();
                    nums.pop();
                    nums.push(num2);
                    break;
                }
                case '.': {
                    int num1 = nums.top();
                    nums.pop();
                    nums.push(-num1);
                    break;
                }
                default:
                    break;
            }
        }

        int calculate(string s) {
            stack<int> values;
            stack<int> operators;
            vector<int> numbuilder;

            operators.push('#');

            // we use '~' for unitary '+' and '_' for unitary '-'
            bool num_mode = false;
            bool last_token_num = false;

            s.append(1, '#');
            for (auto &c: s) {
                if (c >= '0' && c <= '9') {
                    num_mode = true;
                    numbuilder.push_back(c - '0');
                } else {
                    if (num_mode) {
                        values.push(build_num(numbuilder));
                        numbuilder.clear();
                        num_mode = false;
                        last_token_num = true;
                    }

                    if (c == ' ') {
                    }
                    // Operators
                    if (c == '+' || c == '-') {
                        bool unitary = !last_token_num;
                        c += unitary;
                        int prec = PREC[c];
                        while (PREC[operators.top()] >= prec) {
                            execute_opr(values, operators.top());
                            operators.pop();
                        }
                        operators.push(c);
                        last_token_num = false;
                    }
                    if (c == '#') {
                        while (!operators.empty()) {
                            execute_opr(values, operators.top());
                            operators.pop();
                        }
                    }

                    if (c == '(') {
                        operators.push('(');
                        last_token_num = false;
                    }
                    if (c == ')') {
                        while (operators.top() != '(') {
                            execute_opr(values, operators.top());
                            operators.pop();
                        }
                        operators.pop();
                        last_token_num = true;
                    }
                }
            }

            while (!operators.empty()) {
                execute_opr(values, operators.top());
                operators.pop();
            }
            return values.top();
        }
    };

    void run() {
        Solution solution;

        assert(5 == solution.calculate("1+2+2"));
        assert(2147483647 == solution.calculate("2147483647"));
        assert(2 == solution.calculate("1 + 1"));
        assert(3 == solution.calculate("2-1 + 2"));
        assert(23 == solution.calculate("(1+(4+5+2)-3)+(6+8)"));
        assert(-1 == solution.calculate("-2+1"));
        assert(-1 == solution.calculate("1-(+1+1)"));
    }
}

#endif //LEETCODE_224_H
