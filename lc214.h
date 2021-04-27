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
                while (pointer <= length - 1) {
                    if (s[pointer] == s[0]) {
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

            pointer = std::max(pointer, 2);
            int back2_pointer = 0; // for aa
            int back3_pointer = 0; // for aba
            int half_way = length / 2 + 1;
            while (pointer <= half_way) {
                int track_pointer = pointer;
                if (s[pointer] == s[pointer - 1]) {
                    back2_pointer = pointer - 1;
                } else {
                    back2_pointer = INT32_MIN;
                }
                if (s[pointer] == s[pointer - 2]) {
                    back3_pointer = pointer - 2;
                } else {
                    back3_pointer = INT32_MIN;
                }
                if(back2_pointer < 0 && back3_pointer < 0) {
                    pointer++;
                    continue;
                }

                while ((back2_pointer >= 0 || back3_pointer >= 0) && track_pointer <= length - 1) {
                    int inc = 0;
                    if (back2_pointer >= 0 && s[track_pointer] == s[back2_pointer]) {
                        back2_pointer--;
                        inc = 1;
                    } else {
                        back2_pointer = INT32_MIN;
                    }

                    if (back3_pointer >= 0 && s[track_pointer] == s[back3_pointer]) {
                        back3_pointer--;
                        inc = 1;
                    } else {
                        back3_pointer = INT32_MIN;
                    }
                    if (inc == 0) {
                        break;
                    } else {
                        track_pointer++;
                    }
                }
                track_pointer--;

                if (back2_pointer == -1 || back3_pointer == -1) { // palindrome found
                    pointer = track_pointer+1;
                    // Extend all sub-repeating
                    int len_long = pointer;
                    int len_short = records[records.size() - 1];
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

        assert("" == solution.shortestPalindrome(""));
        assert("a" == solution.shortestPalindrome("a"));
        assert("aba" == solution.shortestPalindrome("ba"));
        assert("aabaa" == solution.shortestPalindrome("abaa"));
        assert("abbaabba" == solution.shortestPalindrome("aabba"));
        assert("ababa" == solution.shortestPalindrome("ababa"));
        assert("aaacecaaa" == solution.shortestPalindrome("aacecaaa"));
        assert("dcabbacd"== solution.shortestPalindrome("abbacd"));
        assert("dcbabcd" == solution.shortestPalindrome("abcd"));
        assert("aaaaa" == solution.shortestPalindrome("aaaaa"));
        assert("ababbabbbabbaba" == solution.shortestPalindrome("babbbabbaba"));
        assert("efbabababababfe" == solution.shortestPalindrome("abababababfe"));
        assert("dddabaccabaccabaddd" == solution.shortestPalindrome("abaccabaccabaddd"));
        assert("aababaabababababaababaa" == solution.shortestPalindrome("aabababababaababaa"));
    }


}

#endif //LEETCODE_LC214_H
