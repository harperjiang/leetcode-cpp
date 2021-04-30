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
        void swap(vector<int> &heap, deque<int> &seq_to_heap, deque<int> &value_to_idx, int a, int b) {
            int temp = heap[a];
            heap[a] = heap[b];
            heap[b] = temp;
            temp = value_to_idx[a];
            value_to_idx[a] = value_to_idx[b];
            value_to_idx[b] = temp;
            int seqa = value_to_idx[a];
            int seqb = value_to_idx[b];
            temp = seq_to_heap[seqa];
            seq_to_heap[seqa] = seq_to_heap[seqb];
            seq_to_heap[seqb] = temp;
        }

        void rotate(deque<int>& seq_to_heap, deque<int>&value_to_idx) {
            int poped = seq_to_heap.front();
            seq_to_heap.pop_front();
            seq_to_heap.push_back(poped);
            poped = value_to_idx.back();
            value_to_idx.pop_back();
            value_to_idx.push_front(poped);
        }

        void heapify(vector<int> &heap, deque<int> &seq_to_heap, deque<int> &value_to_idx) {
            int length = heap.size();
            for (int j = length - 1; j > 0; j--) {
                heap_adjust(heap, seq_to_heap, value_to_idx, j);
            }
        }

        void heap_adjust(vector<int> &heap, deque<int> &seq_to_heap, deque<int> &value_to_idx, int index) {
            int p = index;
            while (p > 0 && heap[(p - 1) / 2] < heap[p]) {
                swap(heap, seq_to_heap, value_to_idx, p, (p - 1) / 2);
                p = (p - 1) / 2;
            }
        }

        void heapdown_adjust(vector<int> &heap, deque<int> &seq_to_heap, deque<int> &value_to_idx, int index) {
            int length = heap.size();
            int p = index;
            while (true) {
                int left = p * 2 + 1 < length ? heap[p * 2 + 1] : INT32_MIN;
                int right = p * 2 + 2 < length ? heap[p * 2 + 2] : INT32_MIN;
                int max = std::max(left, right);
                if (heap[p] < max) {
                    if (left == max) {
                        swap(heap, seq_to_heap, value_to_idx, p, p * 2 + 1);
                        p = p * 2 + 1;
                    } else {
                        swap(heap, seq_to_heap, value_to_idx, p, p * 2 + 2);
                        p = p * 2 + 2;
                    }
                } else {
                    break;
                }
            }
        }

        void replace_adjust(vector<int> &heap, deque<int> &seq_to_heap, deque<int> &value_to_idx, int index) {
            int length = heap.size();
            if (index > 0 && heap[index] > heap[(index - 1) / 2]) {
                // Adjust up
                heap_adjust(heap, seq_to_heap, value_to_idx, index);
            } else {
                heapdown_adjust(heap, seq_to_heap, value_to_idx, index);
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
            deque<int> value_to_idx;
            vector<int> heap;
            heap.resize(k);
            value_to_idx.resize(k);

            int i;
            for (i = 0; i < k; ++i) {
                heap[i] = nums[i];
                seq_to_heap.push_back(i);
                value_to_idx[i] = i;
            }
            heapify(heap, seq_to_heap, value_to_idx);

            result.push_back(heap[0]);

            int num_length = nums.size();
            for (; i < num_length; ++i) {
                int to_adjust = seq_to_heap[0];
                heap[to_adjust] = nums[i];
                rotate(seq_to_heap,value_to_idx);
                replace_adjust(heap, seq_to_heap, value_to_idx, to_adjust);
                result.push_back(heap[0]);
            }
            return result;
        }
    };

    void run() {
        Solution solution;

//        {
//            vector<int> nums{1, 3, -1, -3, 5, 3, 6, 7};
//            vector<int> expected{3, 3, 5, 5, 6, 7};
//            assert(expected == solution.maxSlidingWindow(nums, 3));
//        }
//        {
//            vector<int> nums{1};
//            vector<int> expected{1};
//            assert(expected == solution.maxSlidingWindow(nums, 1));
//        }
//        {
//            vector<int> nums{1, -1};
//            vector<int> expected{1, -1};
//            assert(expected == solution.maxSlidingWindow(nums, 1));
//        }
//
//        {
//            vector<int> nums{9, 11};
//            vector<int> expected{11};
//            assert(expected == solution.maxSlidingWindow(nums, 2));
//        }
//        {
//            vector<int> nums{4, -2};
//            vector<int> expected{4};
//            assert(expected == solution.maxSlidingWindow(nums, 2));
//        }
//        {
//            vector<int> nums{1, 3, 1, 2, 0, 5};
//            vector<int> expected{3, 3, 2, 5};
//            assert(expected == solution.maxSlidingWindow(nums, 3));
//        }
        {
            vector<int> nums{9, 10, 9, -7, -4, -8, 2, -6};
            vector<int> expected{10, 10, 9, 2};
            assert(expected == solution.maxSlidingWindow(nums, 5));
        }
    }
}
#endif //LEETCODE_239_H
