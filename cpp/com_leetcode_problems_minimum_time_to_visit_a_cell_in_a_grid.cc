#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <functional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

namespace {
class Solution {
  static constexpr std::array<std::array<int, 2>, 4> available_moves{
      std::array<int, 2>{1, 0},
      std::array<int, 2>{-1, 0},
      std::array<int, 2>{0, 1},
      std::array<int, 2>{0, -1},
  };

  public:
  int minimumTime(std::vector<std::vector<int>>& grid) {
    if (grid[0][1] > 1 && grid[1][0] > 1) {
      return -1;
    }
    const size_t m = grid.size();
    const size_t n = grid[0].size();
    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    std::priority_queue<std::tuple<int, int, int>,
                        std::vector<std::tuple<int, int, int>>, std::greater<>>
        q;
    q.push({grid[0][0], 0, 0});
    std::vector<std::pair<int, int>> adj;
    adj.reserve(8);
    while (!q.empty()) {
      const auto [cur_time, row, col] = q.top();
      q.pop();
      if (row == m - 1 && col == n - 1) {
        return cur_time;
      }
      if (visited[row][col]) {
        continue;
      }
      visited[row][col] = true;
      for (const auto& [d_row, d_col] : available_moves) {
        const int neighbor_row = row + d_row;
        const int neighbor_col = col + d_col;
        if (neighbor_row >= 0 && neighbor_row < m && neighbor_col >= 0 &&
            neighbor_col < n && !visited[neighbor_row][neighbor_col]) {
          const int wait_time =
              (grid[neighbor_row][neighbor_col] - cur_time) % 2 == 0 ? 1 : 0;
          const int new_time = std::max(
              grid[neighbor_row][neighbor_col] + wait_time, cur_time + 1);
          q.push({new_time, neighbor_row, neighbor_col});
        }
      }
      adj.clear();
    }
    return -1;
  }
};

struct TV {
  std::vector<std::vector<int>> grid;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().minimumTime(tv.grid);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{{0, 1, 3, 2}, {5, 1, 2, 5}, {4, 3, 8, 6}}, 7},
    TV{{{0, 2, 4}, {3, 2, 1}, {1, 0, 4}}, -1},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
