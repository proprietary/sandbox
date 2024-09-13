#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "utils.hpp"

template <typename T, size_t N>
constexpr size_t sizeof_array(T (&arr)[N]) {
  return N;
}

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
  ListNode* head = newList(input);
  Solution s;
  auto ans = s.spiralMatrix(m, n, head);
  std::vector<std::vector<int>> expected = {
      {3, 0, 2, 6, 8}, {5, 0, -1, -1, 1}, {5, 2, 4, 9, 7}};
  EXPECT_EQ(ans, expected);
}
