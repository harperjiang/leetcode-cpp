//
// Created by Harper on 4/24/21.
//

#ifndef LEETCODE_LC174_H
#define LEETCODE_LC174_H

#include <vector>
#include <assert.h>

using namespace std;

namespace lc174 {
    class Solution {
    public:
        int calculateMinimumHP(vector<vector<int>> &dungeon) {
            int width = dungeon.size();
            int height = dungeon[0].size();

            int min_hp[width][height];
            for (int i = 0; i < width; ++i) {
                for (int j = 0; j < height; ++j) {
                    min_hp[i][j] = INT32_MAX;
                }
            }
            int last_damage = dungeon[width - 1][height - 1];
            min_hp[width - 1][height - 1] = (last_damage < 0) ? (1 - last_damage) : 1;

            for (int i = width - 1; i >= 0; i--) {
                for (int j = height - 1; j >= 0; j--) {
                    if (i == width - 1 && j == height - 1) {
                        continue;
                    }
                    int damage = dungeon[i][j];
                    int right_minhp = (i < width - 1) ? min_hp[i + 1][j] : INT32_MAX;
                    int down_minhp = (j < height - 1) ? min_hp[i][j + 1] : INT32_MAX;

                    int min_need = min(right_minhp, down_minhp);
                    min_need -= damage;
                    if (min_need <= 0) {
                        min_need = 1;
                    }
                    min_hp[i][j] = min_need;
                }
            }
            return min_hp[0][0];
        }
    };

    void run() {
        Solution solution;

        vector<vector<int>> dungeon{{-2, -3,  3},
                                    {-5, -10, 1},
                                    {10, 30,  -5}};
        assert(7 == solution.calculateMinimumHP(dungeon));
    }
}
#endif //LEETCODE_LC174_H
