/*
 * Leetcode problem 35. Search Insert Position
 *
 * Given a sorted array and a target value, return the index if the target is
 * found. If not, return the index where it would be if it were inserted in
 * order.
 *
 * You may assume no duplicates in the array.
 *
 * Example 1:
 *
 * Input: [1,3,5,6], 5
 * Output: 2
 *
 * Example 2:
 *
 * Input: [1,3,5,6], 2
 * Output: 1
 *
 * Example 3:
 *
 * Input: [1,3,5,6], 7
 * Output: 4
 *
 * Example 4:
 *
 * Input: [1,3,5,6], 0
 * Output: 0
 */

#include <gtest/gtest.h>

#include <vector>

class Solution {
 public:
  int searchInsert(std::vector<int>& nums, int target) {
    int hi = nums.size() - 1;
    int lo = 0;
    int mid = (hi + lo) / 2;
    while (hi > lo) {
      const int mid_val = nums[mid];
      if (target < mid_val) {
        hi = mid - 1;
      } else if (target > mid_val) {
        lo = mid + 1;
      } else {
        return mid;
      }
      mid = (hi + lo) / 2;
    }
    return mid + (target > nums[mid]);
  }
};

TEST(Leetcode, Solution) {
  Solution solution{};
  std::vector<int> input = {1, 3, 5, 6};
  EXPECT_EQ(solution.searchInsert(input, 5), 2);
  EXPECT_EQ(solution.searchInsert(input, 2), 1);
  EXPECT_EQ(solution.searchInsert(input, 7), 4);
  EXPECT_EQ(solution.searchInsert(input, 0), 0);
  input = {1, 3};
  EXPECT_EQ(solution.searchInsert(input, 2), 1);
}
