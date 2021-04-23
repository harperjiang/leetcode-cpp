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
        unordered_map<string, uint32_t> rev_index_;
        uint8_t *transition_;

        vector<vector<int>> back_trace_;

        void buildTransition(vector<string> &wordList) {
            rev_index_.clear();

            int length = wordList.size();
            transition_ = (uint8_t *) malloc(length * length);
            memset(transition_, 0, length * length);
            for (int i = 0; i < wordList.size(); ++i) {
                rev_index_[wordList[i]] = i;
                for (int j = i + 1; j < wordList.size(); ++j) {
                    if (check(wordList[i], wordList[j])) {
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

        uint32_t shortest_path(int from, int to) {
            auto length = rev_index_.size();

            uint32_t shortest[length];
            memset(shortest, 0xff, length * sizeof(uint32_t));
            shortest[from] = 0;

            back_trace_.clear();
            back_trace_.resize(length);

            vector<int> frontier;
            frontier.push_back(from);
            int frontier_pointer = 0;

            while (frontier_pointer < frontier.size()) {
                int current = frontier[frontier_pointer];
                frontier_pointer++;
                for (auto i = 0; i < length; ++i) {
                    if (transition_[current * length + i]) {
                        if (shortest[i] > shortest[current] + 1) {
                            shortest[i] = shortest[current] + 1;
                            back_trace_[i].clear();
                            back_trace_[i].push_back(current);
                            frontier.push_back(i);
                        } else if (shortest[i] == shortest[current] + 1) {
                            back_trace_[i].push_back(current);
                        }
                    }
                }
            }

            return shortest[to];
        }

        vector<vector<int>> trace_to_path(int end_index, int length) {
            vector<vector<int>> result;
            for (auto i: back_trace_[end_index]) {
                result.push_back(vector<int>{i});
            }
            for (int i = 0; i < length - 1; ++i) {
                int round = result.size();
                for (int j = 0; j < round; ++j) {
                    auto base = result[j];
                    auto &append = back_trace_[base[base.size() - 1]];

                    for (int k = 1; k < append.size(); ++k) {
                        auto newpath = vector<int>(base);
                        newpath.push_back(append[k]);
                        result.push_back(newpath);
                    }
                    result[j].push_back(append[0]);
                }

            }
            return result;
        }

    public:
        vector<vector<string>> findLadders(string beginWord, string endWord, vector<string> &wordList) {
            buildTransition(wordList);

            auto end_found = rev_index_.find(endWord);
            auto end_index = -1;
            if (end_found == rev_index_.end()) {
                // No end word
                return vector<vector<string>>();
            } else {
                end_index = end_found->second;
            }

            int shortest_threshold = wordList.size();
            // Recorded shortest paths
            vector<vector<int>> paths;


            auto begin_found = rev_index_.find(beginWord);
            bool contain_header = begin_found != rev_index_.end();
            if (!contain_header) {
                for (int i = 0; i < wordList.size(); ++i) {
                    auto word = wordList[i];
                    if (check(beginWord, word)) {
                        int shortest = shortest_path(i, end_index);
                        if (shortest < INT32_MAX) {
                            if (shortest < shortest_threshold) {
                                // clear longer paths
                                paths.clear();
                            }
                            if (shortest <= shortest_threshold) {
                                auto new_path = trace_to_path(end_index, shortest);
                                for (auto &p:new_path) {
                                    paths.push_back(p);
                                }
                                shortest_threshold = shortest;
                            }
                        }
                    }
                }
            } else {
                int shortest = shortest_path(begin_found->second, end_index);
                if (shortest < INT32_MAX) {
                    auto new_path = trace_to_path(end_index, shortest);
                    for (auto &p:new_path) {
                        paths.push_back(p);
                    }
                }
                shortest_threshold = shortest;
            }
            clear();

            vector<vector<string>> result;
            for (auto p: paths) {
                vector<string> strp;
                if (!contain_header)
                    strp.push_back(beginWord);
                for (int i = 0; i < shortest_threshold; ++i) {
                    strp.push_back(wordList[p[shortest_threshold - 1 - i]]);
                }
                strp.push_back(endWord);
                result.push_back(strp);
            }
            return result;
        }

    };

    void run() {
        Solution solution;
        {
            auto beginWord = "hit";
            auto endWord = "cog";
            vector<string> wordList{"hot", "dot", "dog", "lot", "log", "cog"};
            auto result = solution.findLadders(beginWord, endWord, wordList);
        }
        {
            auto beginWord = "a";
            auto endWord = "c";
            vector<string> wordList{"a", "b", "c"};
            auto result = solution.findLadders(beginWord, endWord, wordList);
        }
        {
            auto beginWord = "red";
            auto endWord = "tax";
            vector<string> wordList{"ted", "tex", "red", "tax", "tad", "den", "rex", "pee"};

            auto result = solution.findLadders(beginWord, endWord, wordList);
        }
        {
            auto beginWord = "qa";
            auto endWord = "sq";
            vector<string> wordList{"si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye"};

            auto result = solution.findLadders(beginWord, endWord, wordList);
        }
    }

}
#endif //LEETCODE_LC126_H
