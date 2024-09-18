/**
 * Leetcode 66. Plus One
 *
 * Given a non-empty array of digits representing a non-negative integer, plus
 one to the integer.

 * The digits are stored such that the most significant digit is at the head of
 the list, and each element in the array contain a single digit.
 *
 * You may assume the integer does not contain any leading zero, except the
 number 0 itself.
 *
 * Example 1:
 *
 * Input: [1,2,3]
 * Output: [1,2,4]
 * Explanation: The array represents the integer 123.
 *
 * Example 2:
 *
 * Input: [4,3,2,1]
 * Output: [4,3,2,2]
 * Explanation: The array represents the integer 4321.
 */

#include <gtest/gtest.h>

#include <vector>

class Solution {
  public:
  std::vector<int> plusOne(std::vector<int>& digits) {
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
      *it = (*it + 1) % 10;
      if (*it > 0) {
        return digits;
      }
    }
    digits.emplace(digits.begin(), 1);
    return digits;
  }
};

TEST(Leetcode, TestSolution) {
  Solution solution{};
  std::vector<int> input = {{1, 2, 3}};
  std::vector<int> expected = {{1, 2, 4}};
  auto result = solution.plusOne(input);
  ASSERT_EQ(expected.size(), result.size());
  EXPECT_TRUE(expected == result);
  input.clear();
  input = {{4, 3, 2, 1}};
  expected = {{4, 3, 2, 2}};
  EXPECT_TRUE(expected == solution.plusOne(input));
  input.clear();
  input = {{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}};
  expected = {{9, 8, 7, 6, 5, 4, 3, 2, 1, 1}};
  EXPECT_TRUE(expected == solution.plusOne(input));
  input.clear();
  input.push_back(9);
  expected = {{1, 0}};
  EXPECT_TRUE(expected == solution.plusOne(input));
  input = {{9, 9}};
  expected = {{1, 0, 0}};
  EXPECT_TRUE(expected == solution.plusOne(input));
  input = {{8, 9, 9, 9}};
  expected = {{9, 0, 0, 0}};
  EXPECT_TRUE(expected == solution.plusOne(input));
}
