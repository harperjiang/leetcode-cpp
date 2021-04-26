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
            if(length <= 1) {
                return s;
            }

            int longest_pa = 0;

            vector<char> buffer;
            buffer.push_back(s[0]);
            int buffer_pointer = 0;
            for (int i = 1; i < length; ++i) {
                buffer.push_back(s[i]);
                if (s[i] == buffer[buffer_pointer]) { // "a<palindrome>a" type
                    buffer_pointer--;
                    if (buffer_pointer == -1) {
                        // Found one
                        longest_pa = buffer.size();
                        buffer_pointer = buffer.size() - 1;
                    }
                } else if (buffer.size() >= 3 && buffer_pointer == buffer.size() - 2 &&
                           s[i] == buffer[buffer_pointer - 1]) {// "aba" type
                    buffer_pointer -= 2;
                    if (buffer_pointer == -1) {
                        longest_pa = buffer.size();
                        buffer_pointer = buffer.size() - 1;
                    }
                } else {
                    buffer_pointer += 1;
                }
            }

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
                result[i] = result[result.length()- 1 - i];
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
//        assert("aabaa" == solution.shortestPalindrome("abaa"));
//        assert("aaacecaaa" == solution.shortestPalindrome("aacecaaa"));
//        assert("dcbabcd" == solution.shortestPalindrome("abcd"));
        assert("aaaaa"==solution.shortestPalindrome("aaaaa"));
    }
}

#endif //LEETCODE_LC214_H
