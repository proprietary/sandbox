#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
enum class Cell {
  Wall,
  Guard,
  Blocked,
  Empty,
};

class Solution {
  public:
  int countUnguarded(int m, int n, std::vector<std::vector<int>>& guards,
                     std::vector<std::vector<int>>& walls) {
    std::vector<std::vector<Cell>> grid(m, std::vector<Cell>(n, Cell::Empty));
    for (const auto& c : walls) {
      grid[c[0]][c[1]] = Cell::Wall;
    }
    for (const auto& c : guards) {
      grid[c[0]][c[1]] = Cell::Guard;
    }
    for (const auto& c : guards) {
      const auto& row = c[0];
      const auto& col = c[1];
      // east
      for (int col_ = col + 1; col_ < n && (grid[row][col_] != Cell::Wall &&
                                            grid[row][col_] != Cell::Guard);
           ++col_) {
        grid[row][col_] = Cell::Blocked;
      }
      // west
      for (int col_ = col - 1; col_ >= 0 && (grid[row][col_] != Cell::Wall &&
                                             grid[row][col_] != Cell::Guard);
           --col_) {
        grid[row][col_] = Cell::Blocked;
      }
      // north
      for (int row_ = row + 1; row_ < m && (grid[row_][col] != Cell::Wall &&
                                            grid[row_][col] != Cell::Guard);
           ++row_) {
        grid[row_][col] = Cell::Blocked;
      }
      // south
      for (int row_ = row - 1; row_ >= 0 && (grid[row_][col] != Cell::Wall &&
                                             grid[row_][col] != Cell::Guard);
           --row_) {
        grid[row_][col] = Cell::Blocked;
      }
    }
    int ans = 0;
    for (const auto& r : grid) {
      ans += std::count_if(r.begin(), r.end(),
                           [](const auto& x) { return x == Cell::Empty; });
    }
    return ans;
  }
};

struct TV {
  int m;
  int n;
  std::vector<std::vector<int>> guards;
  std::vector<std::vector<int>> walls;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().countUnguarded(tv.m, tv.n, tv.guards, tv.walls);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{4, 6, {{0, 0}, {1, 1}, {2, 3}}, {{0, 1}, {2, 2}, {1, 4}}, 7},
    TV{3, 3, {{1, 1}}, {{0, 1}, {1, 0}, {2, 1}, {1, 2}}, 4},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
