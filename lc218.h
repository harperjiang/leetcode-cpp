//
// Created by harper on 4/27/21.
//

#ifndef LEETCODE_LC218_H
#define LEETCODE_LC218_H

#include <vector>
#include <array>
#include <set>
#include <list>
#include <cassert>

using namespace std;

namespace lc218 {
    class Solution {

    public:
        bool overlap(vector<int> &a, vector<int> &b) {
            return a[0] < b[1] && b[0] < a[1];
        }

        vector<vector<int>> getSkyline(vector<vector<int>> &buildings) {
            list <vector<int>> segments;
            vector<int> all{0, INT32_MAX, 0};
            segments.push_back(all);
            auto seg_pointer = segments.begin();

            for (auto &building: buildings) {
                // Find the first segment contains this building
                while (seg_pointer != segments.end() && !overlap(*seg_pointer, building)) {
                    seg_pointer++;
                }

                if (seg_pointer == segments.end()) {
                    // Add new segment
                    segments.push_back(building);
                } else {
                    // Overlap
                    auto oseg_pointer = seg_pointer;
                    while (oseg_pointer != segments.end() && overlap(*oseg_pointer, building)) {
                        auto &seg = *oseg_pointer;
                        if (seg[2] < building[2]) {
                            if (building[0] <= seg[0]) {
                                if (building[1] >= seg[1]) {
                                    seg[2] = building[2];
                                } else {
                                    vector<int> newseg{building[1], seg[1], seg[2]};
                                    seg[1] = building[1];
                                    seg[2] = building[2];
                                    oseg_pointer++;
                                    segments.insert(oseg_pointer, newseg);
                                }
                            } else {
                                vector<int> before{seg[0], building[0], seg[2]};
                                auto before_pos = oseg_pointer;
                                if (building[1] >= seg[1]) {
                                    seg[0] = building[0];
                                    seg[2] = building[2];
                                } else {
                                    vector<int> after{building[1], seg[1], seg[2]};
                                    seg[0] = building[0];
                                    seg[2] = building[2];
                                    seg[1] = building[1];
                                    oseg_pointer++;
                                    segments.insert(oseg_pointer, after);
                                }
                                segments.insert(before_pos, before);
                            }
                        }
                        oseg_pointer++;
                    }
                }
            }
            vector<vector<int>> pivots;

            int height = 0;
            int prev_end = 0;
            for (auto &segment: segments) {
                if (segment[0] == 0 && segment[2] == 0) {
                    // Skip the first zero
                    continue;
                }
                if (segment[2] != height) {
                    height = segment[2];
                    vector<int> pivot{segment[0], segment[2]};
                    prev_end = segment[1];
                    pivots.push_back(pivot);
                } else {
                    prev_end = segment[1];
                }
            }
            if (height != 0) {
                // Manually insert an end note for the corner case that the last building equals INT32_MAX
                pivots.push_back(vector<int>{prev_end, 0});
            }

            return pivots;
        }
    };

    void run() {
        Solution solution;

        {
            vector<vector<int>> buildings{{0, 2, 3},
                                          {2, 5, 3}};
            vector<vector<int>> expect{{0, 3},
                                       {5, 0}};
            assert(expect == solution.getSkyline(buildings));
        }
        {
            vector<vector<int>> building{{2,  9,  10},
                                         {3,  7,  15},
                                         {5,  12, 12},
                                         {15, 20, 10},
                                         {19, 24, 8}};
            vector<vector<int>> expect{{2,  10},
                                       {3,  15},
                                       {7,  12},
                                       {12, 0},
                                       {15, 10},
                                       {20, 8},
                                       {24, 0}};
            assert(expect == solution.getSkyline(building));
        }
        {
            vector<vector<int>> building{{0, 2147483647, 2147483647}};
            vector<vector<int>> expect{{0,          2147483647},
                                       {2147483647, 0}};
            assert(expect == solution.getSkyline(building));
        }
        {
            vector<vector<int>> building{{1,          2,          1},
                                         {2147483646, 2147483647, 2147483647}};
            vector<vector<int>> expect{{1,          1},
                                       {2,          0},
                                       {2147483646, 2147483647},
                                       {2147483647, 0}};
            assert(expect == solution.getSkyline(building));
        }
        {
            vector<vector<int>>building{{2,13,10},{10,17,25},{12,20,14}};
            vector<vector<int>>expect{{2,10},{10,25},{17,14},{20,0}};
            assert(expect==solution.getSkyline(building));
        }
    }
}

#endif //LEETCODE_LC218_H
