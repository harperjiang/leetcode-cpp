//
// Created by harper on 5/6/21.
//

#ifndef LEETCODE_LC301_H
#define LEETCODE_LC301_H

#include <string>
#include <vector>
#include <cassert>
#include <unordered_set>

using namespace std;

namespace lc301 {

    class Solution {
    public:
        void remove(unordered_set<string> &results, string &s, string &buffer, int pos, int diff) {
            if (pos == s.length()) {
                if (diff == 0) {
                    int removed = s.length() - buffer.length();
                    int current = results.size() == 0 ? INT32_MAX : (s.length() - (*results.begin()).length());
                    if (removed > current) {
                        return;
                    }
                    if (removed < current) {
                        results.clear();
                    }
                    results.insert(buffer);
                    return;
                }
            }
            while (pos < s.length()) {
                switch (s[pos]) {
                    case '(': {
                        // Branch, have it or skip it
                        // have it
                        int limit = buffer.length();
                        buffer.append(1, '(');
                        remove(results, s, buffer, pos + 1, diff + 1);
                        // not having it
                        buffer.resize(limit);
                        remove(results, s, buffer, pos + 1, diff);
                        return;
                    }
                    case ')': {
                        if (diff > 0) {
                            // Branches, have it or skip it
                            int limit = buffer.size();
                            // Have it
                            buffer.append(1, ')');
                            remove(results, s, buffer, pos + 1, diff - 1);
                            buffer.resize(limit);
                            // Not having it
                            remove(results, s, buffer, pos + 1, diff);
                            return;
                        } else {
                            // have to ignore
                            pos++;
                        }
                        break;
                    }
                    default:
                        buffer.append(1, s[pos++]);
                        break;
                }
            }
            if (diff == 0) {
                int removed = s.length() - buffer.length();
                int current = results.size() == 0 ? INT32_MAX : (s.length() - (*results.begin()).length());
                if (removed > current) {
                    return;
                }
                if (removed < current) {
                    results.clear();
                }
                results.insert(buffer);
                return;
            }
        }

        vector<string> removeInvalidParentheses(string s) {
            unordered_set<string> results;
            string buffer;
            remove(results, s, buffer, 0, 0);

            vector<string> ret;
            ret.insert(ret.begin(), results.begin(), results.end());
            return ret;
        }
    };

    void run() {
        Solution solution;
//        {
//            auto result = solution.removeInvalidParentheses("()())()");
//            assert(2 == result.size());
//        }
        {
            auto result = solution.removeInvalidParentheses("(a)())()");
            assert(2 == result.size());
        }
    }
}

#endif //LEETCODE_LC301_H
