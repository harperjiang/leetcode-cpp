//
// Created by Harper on 4/28/21.
//

#ifndef LEETCODE_239_H
#define LEETCODE_239_H

#include <vector>
#include <cassert>
#include <deque>

using namespace std;

namespace lc239 {
    class Solution {
    private:
        void swap(vector<int> heap, deque<int> seq_to_heap, int a, int b) {

        }

        void heapify(vector<int> heap, deque<int> seq_to_heap) {
            int length = heap.size();
            for (int j = length - 1; j > 0; j--) {
                heap_adjust(heap, seq_to_heap, j);
            }
        }

        void heap_adjust(vector<int> heap, deque<int> seq_to_heap, int index) {
            int p = index;
            while (p > 0) {
                if (heap[p / 2] < heap[p]) {
                    swap(heap, seq_to_heap, p, p / 2);
                    p /= 2;
                }
            }
        }

    public:
        vector<int> maxSlidingWindow(vector<int> &nums, int k) {

            vector<int> result;

            if (nums.size() <= k) {
                int max_value = INT32_MIN;
                for (auto a: nums) {
                    max_value = std::max(max_value, a);
                }
                result.push_back(max_value);
                return result;
            }

            // max_heap[i] is the position of element in the heap
            deque<int> seq_to_heap;
            vector<int> heap;
            heap.resize(k);

            int i;
            for (i = 0; i < k; ++i) {
                heap[i] = nums[i];
            }
            heapify(heap, seq_to_heap);

            result.push_back(heap[0]);

            int num_length = nums.size();
            for (; i < num_length; ++i) {
                heap[seq_to_heap[0]] = i;
                heap_adjust(heap, seq_to_heap, seq_to_heap[0]);
                result.push_back(heap[0]);
            }
            return result;
        }
    };

    void run() {
        Solution solution;

        {
            vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};
            vector<int> expected{3, 3, 5, 5, 6, 7};
            assert(expected == solution.maxSlidingWindow(nums, 3));
        }
        {
            vector<int> nums{1};
            vector<int> expected{1};
            assert(expected == solution.maxSlidingWindow(nums, 1));
        }
        {
            vector<int> nums{1, -1};
            vector<int> expected{1, -1};
            assert(expected == solution.maxSlidingWindow(nums, 1));
        }

        {
            vector<int> nums{9, 11};
            vector<int> expected{11};
            assert(expected == solution.maxSlidingWindow(nums, 2));
        }
        {
            vector<int> nums{4, -2};
            vector<int> expected{4};
            assert(expected == solution.maxSlidingWindow(nums, 2));
        }
    }
}
#endif //LEETCODE_239_H
