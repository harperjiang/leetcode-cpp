//
// Created by harper on 4/26/21.
//

#ifndef LEETCODE_LC214_H
#define LEETCODE_LC214_H

#include <string>
#include <vector>
#include <cassert>

using namespace std;

namespace lc214 {

    class Solution {
    public:
        string shortestPalindrome(string s) {
            // This is equivalent to find the longest leading palindrome
            int length = s.length();
            if (length <= 1) {
                return s;
            }
            if (length == 2) {
                return (s[0] == s[1]) ? s : string(s.data() + 1, 1) + s;
            }
            if (length == 3) {
                if (s[0] == s[2]) {
                    return s;
                }
                if (s[0] == s[1]) {
                    return string(s.data() + 2, 1) + s;
                }
                return string(s.data() + 2, 1) + string(s.data() + 1, 1) + s;
            }

            vector<int> records;
            records.push_back(1);

            int pointer = 0;
            if (s[0] == s[1]) {
                // Record one "aa"
                records.push_back(2);
                pointer = 2;
                while (pointer <= length - 1){
                    if(s[pointer] == s[0]) {
                        pointer++;
                    } else {
                        break;
                    }
                }
                if (pointer > 2)
                    records.push_back(pointer);
            } else if (s[0] == s[2]) {
                records.push_back(3);
                pointer = 3;
                while (pointer < length - 1) {
                    if (s[pointer] == s[1] && s[pointer + 1] == s[2]) {
                        pointer += 2;
                    } else {
                        break;
                    }
                }
                if (pointer > 3) {
                    records.push_back(pointer);
                }
            }

            pointer = std::max(pointer,2);
            int back_pointer = 0;
            while (pointer < length - 1) {
                if (s[pointer] == s[pointer - 1] || s[pointer] == s[pointer - 2]) {
                    if (s[pointer] == s[pointer - 1]) {
                        back_pointer = pointer - 1;
                    } else {
                        back_pointer = pointer - 2;
                    }
                    while (back_pointer >= 0 && pointer <= length - 1 && s[pointer] == s[back_pointer]) {
                        pointer++;
                        back_pointer--;
                    }
                    pointer--;
                    back_pointer++;
                    if (back_pointer == 0) {// Got one palindrome
                        records.push_back(pointer - back_pointer + 1);
                        pointer++;
                        // Extend all sub-repeating
                        int len_long = records[records.size() - 1];
                        int len_short = records[records.size() - 2];
                        int region = len_long - len_short;
                        while (s[pointer] == s[len_short + (pointer - len_long) % region]) {
                            pointer++;
                        }
                        pointer = len_long + (pointer - len_long) / region * region;
                        records.push_back(pointer);
                    } else {
                        // Fail to create a palindrome, continue searching
                        pointer++;
                    }
                } else {
                    pointer++;
                }
            }

            int longest_pa = records[records.size() - 1];
            string result;
            if (longest_pa == 0) {
                // No leading palindrome
                longest_pa = 1;
            }
            result.append(s.data() + longest_pa, s.length() - longest_pa);
            // inverse result
            int inv_len = result.length() / 2;
            for (int i = 0; i < inv_len; ++i) {
                int temp = result[i];
                result[i] = result[result.length() - 1 - i];
                result[result.length() - 1 - i] = temp;
            }
            result.append(s);
            return result;
        }
    };

    void run() {
        Solution solution;

//        assert("" == solution.shortestPalindrome(""));
//        assert("a" == solution.shortestPalindrome("a"));
//        assert("aba" == solution.shortestPalindrome("ba"));
//        assert("aabaa" == solution.shortestPalindrome("abaa"));
//        assert("abbaabba" == solution.shortestPalindrome("aabba"));
//        assert("ababa" == solution.shortestPalindrome("ababa"));
//        assert("aaacecaaa" == solution.shortestPalindrome("aacecaaa"));
//        assert("dcabbacd"== solution.shortestPalindrome("abbacd"));
//        assert("dcbabcd" == solution.shortestPalindrome("abcd"));
//        assert("aaaaa" == solution.shortestPalindrome("aaaaa"));
        assert("ababbabbbabbaba"==solution.shortestPalindrome("babbbabbaba"));
//        assert("efbabababababfe" == solution.shortestPalindrome("abababababfe"));
//        assert("dddabaccabaccabaddd" == solution.shortestPalindrome("abaccabaccabaddd"));
    }

}

#endif //LEETCODE_LC214_H
