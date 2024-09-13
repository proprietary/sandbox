#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "utils.hpp"

class Solution {
  static constexpr int EMPTY = -1;
  static constexpr int8_t DIRECTIONS[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

  public:
  Solution() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin.tie(nullptr);
  }
  std::vector<std::vector<int>> spiralMatrix(int m, int n, ListNode* head) {
    std::vector<std::vector<int>> ans(m, std::vector<int>(n, EMPTY));
    int8_t current_direction = 0;
    int row = 0, col = 0;
    for (ListNode* p = head; p != nullptr; p = p->next) {
      ans[row][col] = p->val;

      int new_row = row + DIRECTIONS[current_direction][0];
      int new_col = col + DIRECTIONS[current_direction][1];
      if (new_row < 0 || new_col < 0 || new_row >= m || new_col >= n ||
          ans[new_row][new_col] != EMPTY) {
        current_direction = (current_direction + 1) % sizeof_array(DIRECTIONS);
      }
      row += DIRECTIONS[current_direction][0];
      col += DIRECTIONS[current_direction][1];
    }
    return ans;
  }
};

TEST(Test, Example1) {
  int m = 3, n = 5;
  std::vector<int> input = {3, 0, 2, 6, 8, 1, 7, 9, 4, 2, 5, 5, 0};
  auto ans = Solution().spiralMatrix(m, n, newList(input));
  std::vector<std::vector<int>> expected = {
      {3, 0, 2, 6, 8}, {5, 0, -1, -1, 1}, {5, 2, 4, 9, 7}};
  EXPECT_EQ(ans, expected);
}

TEST(Test, Example2) {
  int m = 4, n = 5;
  std::vector<int> input = {515, 942, 528, 483, 20,  159, 868, 999, 474,
                            320, 734, 956, 12,  124, 224, 252, 909, 732};
  auto actual = Solution().spiralMatrix(m, n, newList(input));
  std::vector<std::vector<int>> expected = {{515, 942, 528, 483, 20},
                                            {124, 224, 252, 909, 159},
                                            {12, -1, -1, 732, 868},
                                            {956, 734, 320, 474, 999}};
  EXPECT_EQ(actual, expected);
}
