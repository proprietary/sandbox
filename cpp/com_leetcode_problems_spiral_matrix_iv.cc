#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <vector>

#include "utils.hpp"

enum class Direction { RIGHT, DOWN, LEFT, UP };

class Solution {
  public:
  Solution() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cin.tie(nullptr);
  }
  std::vector<std::vector<int>> spiralMatrix(int m, int n, ListNode* head) {
    std::vector<std::vector<int>> ans(m, std::vector<int>(n, -1));
    int row = 0, col = 0;
    Direction last_direction = Direction::RIGHT;
    for (ListNode* p = head; p != nullptr; p = p->next) {
      ans[row][col] = p->val;
      // print_2d_array(ans.begin(), ans.end());
      bool right = col < n - 1 && ans[row][col + 1] == -1;
      bool down = row < m - 1 && ans[row + 1][col] == -1;
      bool left = col > 0 && ans[row][col - 1] == -1;
      bool up = row > 0 && ans[row - 1][col] == -1;
      switch (last_direction) {
        case Direction::RIGHT:
          if (right) {
            col++;
            goto skip;
          }
          break;
        case Direction::DOWN:
          if (down) {
            row++;
            goto skip;
          }
          break;
        case Direction::LEFT:
          if (left) {
            col--;
            goto skip;
          }
          break;
        case Direction::UP:
          if (up) {
            row--;
            goto skip;
          }
          break;
      }
      if (right) {
        col++;
        last_direction = Direction::RIGHT;
      } else if (down) {
        row++;
        last_direction = Direction::DOWN;
      } else if (left) {
        col--;
        last_direction = Direction::LEFT;
      } else if (up) {
        row--;
        last_direction = Direction::UP;
      }
    skip:
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
