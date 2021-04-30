//
// Created by harper on 4/30/21.
//

#ifndef LEETCODE_LC273_H
#define LEETCODE_LC273_H

#include <string>
#include <cassert>

using namespace std;

namespace lc273 {

    class Solution {
    public:
        static string SEP[4];
        static int FACTOR[4];
        static string DIGIT[10];
        static string TEENDIGIT[10];
        static string TENDIGIT[10];

    public:
        void express_group(int group, int i, string &target) {
            if (group == 0) {
                return;
            }
            string group_string;
            int remain = group;
            // hundred
            int hundred = remain / 100;
            remain %= 100;
            if (hundred != 0) {
                group_string.append(DIGIT[hundred]);
                group_string.append(" ");
                group_string.append("Hundred");
                if (remain != 0) {
                    group_string.append(" ");
                }
            }

            int ten = remain / 10;
            int digit = remain % 10;
            if (ten == 1) {
                group_string.append(TEENDIGIT[digit]);
            } else if (ten > 1) {
                group_string.append(TENDIGIT[ten]);
                if (digit != 0) {
                    group_string.append(" ");
                }
                group_string.append(DIGIT[digit]);
            } else {
                group_string.append(DIGIT[digit]);
            }
            group_string.append(SEP[i]);

            if (!target.empty()) {
                target.append(" ");
            }
            target.append(group_string);
        }

        string numberToWords(int num) {
            string result;
            if (num == 0) {
                return "Zero";
            }
            int remain = num;
            // Split num into groups
            for (int i = 0; i < 4; ++i) {
                int group = remain / FACTOR[3 - i];
                remain %= FACTOR[3 - i];
                express_group(group, 3 - i, result);
            }
            return result;
        }
    };

    int Solution::FACTOR[] = {1, 1000, 1000000, 1000000000};
    string Solution::SEP[] = {"", " Thousand", " Million", " Billion"};
    string Solution::DIGIT[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
    string Solution::TEENDIGIT[] = {"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen",
                                    "Seventeen", "Eighteen", "Nineteen"};
    string Solution::TENDIGIT[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty",
                                   "Ninety"};

    void run() {
        Solution solution;

        assert("Twenty" == solution.numberToWords(20));
        assert("One Thousand One" == solution.numberToWords(1001));
        assert("One Hundred Twenty Three" == solution.numberToWords(123));
        assert("Twelve Thousand Three Hundred Forty Five" == solution.numberToWords(12345));
        assert("One Million Two Hundred Thirty Four Thousand Five Hundred Sixty Seven" ==
               solution.numberToWords(1234567));
        assert("One Billion Two Hundred Thirty Four Million Five Hundred Sixty Seven Thousand Eight Hundred Ninety One" ==
               solution.numberToWords(1234567891));
    }
}

#endif //LEETCODE_LC273_H
