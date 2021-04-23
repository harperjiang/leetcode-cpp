//
// Created by harper on 4/22/21.
//

#ifndef LEETCODE_LC126_H
#define LEETCODE_LC126_H

#include <string>
#include <vector>
#include <cstring>
#include <unordered_map>
#include <forward_list>
#include <iostream>

using namespace std;

namespace lc126 {
    class Solution {
    private:
        vector<string> &word_list_;
        unordered_map<string, uint32_t> rev_index_;
        uint8_t *transition_;

        void buildTransition() {
            int length = word_list_.size();
            transition_ = malloc(length * length);
            memset(transition_, 0, length * length);
            for (int i = 0; i < word_list_.size(); ++i) {
                for (int j = i + 1; j < word_list_.size(); ++j) {
                    if (check(word_list_[i], word_list_[j])) {
                        transition_[i * length + j] = 1;
                        transition_[j * length + i] = 1;
                    }
                }
            }
        }

        void clear() {
            free(transition_);
        }

        // Check if two words has transition
        bool check(string word1, string word2) {
            if (word1.size() == word2.size()) {
                int diff = 0;
                for (uint32_t i = 0; i < word1.size(); ++i) {
                    if (word1[i] != word2[i]) {
                        diff++;
                        if (diff > 1)
                            return false;
                    }
                }
                return true;
            }
            return false;
        }


        vector<vector<int>> shortest_path(int from, int to) {
            auto length = word_list_.size();

            int shortest[length];
            memset(shortest, INT32_MAX, length);
            shortest[from] = 0;
            vector<vector<int>> path_link;
            last.resize(length);

            forward_list<int> frontier;
            frontier.push_back(from);

            while (!frontier.empty()) {
                int current = frontier[0];
                frontier.pop_front();
                for (auto i = 0; i < length; ++i) {
                    if (transition_[current * length + i]) {
                        if (shortest[i] > shortest[current] + 1) {
                            shortest[i] = shortest[current] + 1;
                            path_link[i].clear();
                            path_link[i].push_back(current);
                            frontier.push_back(i);
                        } else if (shortest[i] == shortest[current] + 1) {
                            path_link[i].push_back(current);
                        }
                    }
                }
            }

            auto shortest_len = shorest[to];
            vector<vector<int>> result;
            result.push_back(vector<int>{to});
            for (int i = 1; i < shortest_len; ++i) {
                vector<vector<int>> new_result;
                for(auto v: result) {
                    auto last = v[v.size()-1];
                    auto append = path_link[last];
                    for(auto a: append) {
                        vector<int> newv(v);
                        newv.push_back(a);
                        new_result.push_back(newv);
                    }
                }
                result = new_result;
            }
            return result;
        }

    public:

        vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
            word_list_ = wordList;
            buildTransition();

            vector<vector<string>> result;

            auto found = rev_index_.find(endWord);
            auto end_index = -1;
            if (found == rev_index_.end()) {
                // No end word
                return result;
            } else {
                end_index = found->second;
            }

            int shortest_threshold = wordList.size();
            for (int i = 0; i < wordList.size(); ++i) {
                auto word = wordList[i];
                if (check(beginWord, word)) {
                    auto shortest = shortest_path(i, end_index);
                    if (!shortest.empty()) {
                        if (shortest[0].size() < shortest_threshold) {
                            shortest_threshold = shortest[0].size();
                            result.clear();
                        }
                        if (shortest[0].size() <= shortest_threshold) {
                            auto short_length = shortest[0].size();
                            for (auto v : shortest) {
                                vector<string> path;
                                path.push_back(beginWord);
                                // v is a reverse path
                                for (int ri = short_length - 1; ri >= 0; ri--) {
                                    path.push_back(wordList[v[ri]]);
                                }
                                result.push_back(path);
                            }
                        }
                    }
                }
            }
            clear();
            return result;
        }

    };

    void run() {

    }

}
#endif //LEETCODE_LC126_H
