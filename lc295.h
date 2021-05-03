//
// Created by Harper on 5/2/21.
//

#ifndef LEETCODE_LC295_H
#define LEETCODE_LC295_H

#include <vector>
#include <array>

using namespace std;

namespace lc295 {
    class MedianFinder {
    private:
        array<vector<int>, 200> buckets_;
        int counter_ = 0;
        int median_bucket_ = -1;
        int before_median_counter_ = 0;

        pair<int, int> locate_bucket(int index) {
            int bucket_len = buckets_.size();
            int remain = index;
            before_median_counter_ = 0;
            for (int i = 0; i < bucket_len; ++i) {
                auto &bucket = buckets_[i];
                remain -= bucket.size();
                before_median_counter_ += bucket.size();
                if (remain < 0) {
                    before_median_counter_ -= bucket.size();
                    return pair<int, int>{i, remain + bucket.size()};
                }
            }
            return {-1, -1};
        }

        int find(vector<int> &bucket, int index) {
            sort(bucket.begin(), bucket.end());
            return bucket[index];
        }

        double find2(vector<int> &bucket, int index) {
            sort(bucket.begin(), bucket.end());
            return ((double) bucket[index] + bucket[index + 1]) / 2;
        }

    public:
        /** initialize your data structure here. */
        MedianFinder() {

        }

        void addNum(int num) {
            int bucket_index = num / 1024 + 100;
            buckets_[bucket_index].push_back(num);
            counter_++;
            if (median_bucket_ == -1) {
                median_bucket_ = bucket_index;
            } else if (bucket_index < median_bucket_) {
                before_median_counter_++;
            }
            int median_index = (counter_ - 1) / 2;
            if (before_median_counter_ > median_index ||
                before_median_counter_ + buckets_[median_bucket_].size() <= median_index) {
                // rebalance
                auto located = locate_bucket(median_index);
                median_bucket_ = located.first;
            }
        }

        double findMedian() {
            int median_index = (counter_ - 1) / 2;
            int bucket_index = median_bucket_;
            int offset = median_index - before_median_counter_;
            auto &bucket = buckets_[bucket_index];
            if (counter_ % 2 == 1) { // Odd
                return find(bucket, offset);
            } else {
                if (bucket.size() > offset+ 1) {
                    // Not on border
                    return find2(bucket, offset);
                } else {
                    // On border, find the largest from first and smallest from second
                    auto maxval = *std::max_element(bucket.begin(), bucket.end());
                    int p = bucket_index + 1;
                    while (buckets_[p].empty()) p++;
                    auto &next_bucket = buckets_[p];
                    auto minval = *std::min_element(next_bucket.begin(), next_bucket.end());
                    return ((double) maxval + minval) / 2;
                }
            }
        }
    };

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

    void run() {
//        {
//            MedianFinder *finder = new MedianFinder();
//            finder->addNum(1);
//            finder->addNum(2);
//            assert(1.5 == finder->findMedian());
//            finder->addNum(3);
//            assert(2 == finder->findMedian());
//        }
        {
            MedianFinder *finder = new MedianFinder();
            finder->addNum(1052);
            finder->addNum(60);
            assert(556.0 == finder->findMedian());
        }
    }
}

#endif //LEETCODE_LC295_H
