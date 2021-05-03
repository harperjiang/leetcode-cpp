//
// Created by harper on 4/30/21.
//

#ifndef LEETCODE_LC282_H
#define LEETCODE_LC282_H

#include <vector>
#include <string>
#include <array>
#include <deque>
#include <stack>
#include <math.h>

using namespace std;

namespace lc282 {

    class SolutionO {
        constexpr static int PREC[]{0, 1, 2, 2, 3};
    public:
        int64_t operate(int64_t a, int64_t b, int opr) {
            switch (opr) {
                case 0:
                    return a * 10 + b;
                case 1:
                    return a * b;
                case 2:
                    return a + b;
                case 3:
                    return a - b;
            }
            return 0;
        }

        string construct(string &num, vector<int> &opr_history) {
            string result;
            for (int i = 0; i < opr_history.size(); ++i) {
                result.push_back(num[i]);
                switch (opr_history[i]) {
                    case 0:
                        break;
                    case 1:
                        result.push_back('*');
                        break;
                    case 2:
                        result.push_back('+');
                        break;
                    case 3:
                        result.push_back('-');
                        break;
                }
            }
            result.push_back(num.back());

            return result;
        }

        void compute(string &num, int pos, vector<string> &result, int target) {
            stack<int64_t> intermediate;
            stack<int> oprs;
            vector<int> opr_history;

            intermediate.push(num[0] - '0');
            // Stack Top symbol
            oprs.push(4);
            forward(num, 1, result, target, intermediate, oprs, opr_history);
        }

        void forward(string &num, int pos, vector<string> &result, int target,
                     stack<int64_t> &intermediate, stack<int> &oprs, vector<int> &opr_history) {
            if (pos == num.size()) {
                // evaluate and compare vs target
                while (oprs.top() != 4) {
                    auto v2 = intermediate.top();
                    intermediate.pop();
                    auto v1 = intermediate.top();
                    intermediate.pop();
                    int opr = oprs.top();
                    oprs.pop();
                    intermediate.push(operate(v1, v2, opr));
                }
                if (intermediate.top() == target) {
                    result.push_back(construct(num, opr_history));
                }
                return;
            }
            int digit = num[pos] - '0';
            stack<int64_t> intermediate_backup = intermediate;
            stack<int> oprs_backup = oprs;
            for (int o = 0; o < 4; ++o) {
                if (o == 0 && intermediate.top() == 0) {
                    // do not stack 0
                    continue;
                }
                // compute all high priority oprs
                while (PREC[oprs.top()] <= PREC[o]) {
                    int v2 = intermediate.top();
                    intermediate.pop();
                    int v1 = intermediate.top();
                    intermediate.pop();
                    int opr = oprs.top();
                    oprs.pop();
                    intermediate.push(operate(v1, v2, opr));
                }
                if (o == 0) {
                    int v1 = intermediate.top();
                    if (v1 > INT32_MAX / 10) {
                        continue;
                    }
                    intermediate.pop();
                    intermediate.push(operate(v1, digit, 0));
                } else {
                    oprs.push(o);
                    intermediate.push(digit);
                }
                opr_history.push_back(o);
                forward(num, pos + 1, result, target, intermediate, oprs, opr_history);
                opr_history.pop_back();
                intermediate = intermediate_backup;
                oprs = oprs_backup;
            }
        }

        vector<string> addOperators(string num, int target) {
            int length = num.size();

            vector<string> result;

            auto string_t = to_string(target);
            int slen = string_t.size();
            if (target < 0) {
                slen--;
            }
            if (num.size() <= slen) {
                if (stol(num.data()) == target) {
                    result.push_back(num);
                }
                return result;
            }


            compute(num, 0, result, target);

            return result;
        }
    };

    class Solution2 {
    public:

        void rec(const string &num, int i, long long lastMult, long long result,
                 vector<pair<int, char>> &signs, int target,
                 vector<string> &results) {
            if (i == num.size()) {
                if (result + lastMult == target) {
                    string s = num;
                    for (int j = signs.size() - 1; j >= 0; --j) {
                        int index = signs[j].first;
                        char op = signs[j].second;
                        s.insert(s.begin() + index, op);
                    }
                    results.push_back(s);
                }
                return;
            }

            long long acc = 0;
            for (int j = i; j < (num[i] == '0' ? i + 1 : num.size()); ++j) {
                acc = acc * 10 + num[j] - '0';

                if (i != 0) {
                    // *
                    signs.emplace_back(i, '*');
                    rec(num, j + 1, lastMult * acc, result, signs, target, results);
                    signs.pop_back();

                    // -
                    signs.emplace_back(i, '-');
                    rec(num, j + 1, -acc, result + lastMult, signs, target, results);
                    signs.pop_back();
                }

                // +
                if (i != 0) {
                    signs.emplace_back(i, '+');
                }
                rec(num, j + 1, acc, result + lastMult, signs, target, results);
                if (i != 0) {
                    signs.pop_back();
                }
            }
        }

        vector<string> addOperators(string num, int target) {
            vector<string> results;
            vector<pair<int, char>> signs;

            rec(num, 0, 0, 0, signs, target, results);

            return results;
        }
    };

    class Solution {
    public:
        string construct(string &num, vector<int> &opr_history) {
            string result;
            for (int i = 0; i < opr_history.size(); ++i) {
                result.push_back(num[i]);
                switch (opr_history[i]) {
                    case 0:
                        break;
                    case 1:
                        result.push_back('*');
                        break;
                    case 2:
                        result.push_back('+');
                        break;
                    case 3:
                        result.push_back('-');
                        break;
                }
            }
            result.push_back(num.back());

            return result;
        }

        void compute(string &num, int pos, vector<string> &result, int target) {
            vector<int> opr_history;
            forward(num, 0, result, target, 1, 0, opr_history);
        }

        void forward(string &num, int pos, vector<string> &results, int target,
                     int64_t last_multi, int64_t result, vector<int> &opr_history) {
            if (pos == num.size()) {
                if (result + last_multi == target) {
                    results.push_back(construct(num, opr_history));
                }
                return;
            }

            int64_t consec = 0;
            int limit = num[pos] == '0' ? pos + 1 : num.size();
            for (int j = pos; j < limit; ++j) {
                int digit = num[j] - '0';
                consec = consec * 10 + digit;

                if (pos != 0) {
                    int opr_size = opr_history.size();
                    // multi
                    opr_history.push_back(1);
                    for (int k = pos; k < j; ++k) {
                        opr_history.push_back(0);
                    }
                    forward(num, j + 1, results, target, last_multi * consec, result, opr_history);
                    opr_history.resize(opr_size);
                    // add
                    opr_history.push_back(2);
                    for (int k = pos; k < j; ++k) {
                        opr_history.push_back(0);
                    }
                    forward(num, j + 1, results, target, consec, result + last_multi, opr_history);
                    opr_history.resize(opr_size);
                    // sub
                    opr_history.push_back(3);
                    for (int k = pos; k < j; ++k) {
                        opr_history.push_back(0);
                    }
                    forward(num, j + 1, results, target, -consec, result + last_multi, opr_history);
                    opr_history.resize(opr_size);
                } else {
                    for (int k = pos; k < j; ++k) {
                        opr_history.push_back(0);
                    }
                    forward(num, j + 1, results, target, consec, 0, opr_history);
                    opr_history.resize(0);
                }
            }
        }

        vector<string> addOperators(string num, int target) {
            int length = num.size();

            vector<string> result;

            auto string_t = to_string(target);
            int slen = string_t.size();
            if (target < 0) {
                slen--;
            }
            if (num.size() <= slen) {
                if (stol(num.data()) == target) {
                    result.push_back(num);
                }
                return result;
            }


            compute(num, 0, result, target);

            return result;
        }
    };

    void run() {
        Solution solution;

        {
            auto result = solution.addOperators("123", 6);
            auto expect = vector<string>{"1*2*3", "1+2+3"};
            assert(expect == result);
        }
        {
            auto result = solution.addOperators("232", 8);
            auto expect = vector<string>{"2*3+2", "2+3*2"};
            assert(expect == result);
        }
        {
            auto result = solution.addOperators("105", 5);
            auto expect = vector<string>{"1*0+5","10-5"};
            assert(expect == result);
        }
        {
            auto result = solution.addOperators("00", 0);
            auto expect = vector<string>{"0*0", "0+0", "0-0"};
            assert(expect == result);
        }
        {
            auto result = solution.addOperators("3456237490", 9191);
            auto expect = vector<string>{};
            assert(expect == result);
        }
        {
            auto result = solution.addOperators("2147483648", -2147483648);
            auto expect = vector<string>{};
            assert(expect == result);
        }
        {
            auto result = solution.addOperators("7878", -871);
            auto expect = vector<string>{"7-878"};
            assert(expect == result);
        }
    }
}

#endif //LEETCODE_LC282_H
