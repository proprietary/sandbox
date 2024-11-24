#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>
#include <fmt/ranges.h>
#include <fmt/std.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
enum Item : char {
  Stone = '#',
  Obstacle = '*',
  Empty = '.',
};

class Solution {
  public:
  std::vector<std::vector<char>> rotateTheBox(
      std::vector<std::vector<char>>& box) {
    const int m = box.size();
    const int n = box[0].size();
    std::vector<std::vector<char>> ans(n, std::vector<char>(m));
    for (size_t i = 0; i < m; ++i) {
      for (size_t j = 0; j < n; ++j) {
        ans[j][i] = box[i][j];
      }
    }
    for (size_t i = 0; i < n; ++i) {
      std::reverse(ans[i].begin(), ans[i].end());
    }
    for (int col = 0; col < m; ++col) {
      int empty = n - 1;
      for (int row = n - 1; row >= 0; --row) {
        if (ans[row][col] == Item::Obstacle) {
          empty = row - 1;
        } else if (ans[row][col] == Item::Stone) {
          ans[row][col] = Item::Empty;
          ans[empty][col] = Item::Stone;
          --empty;
        }
      }
    }
    return ans;
  }
};

struct TV {
  std::vector<std::vector<char>> box;
  std::vector<std::vector<char>> expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().rotateTheBox(tv.box);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{{'#', '.', '#'}}, {{'.'}, {'#'}, {'#'}}},
    TV{{{'#', '.', '*', '.'}, {'#', '#', '*', '.'}},
       {{'#', '.'}, {'#', '#'}, {'*', '*'}, {'.', '.'}}},
    TV{{{'#', '#', '*', '.', '*', '.'},
        {'#', '#', '#', '*', '.', '.'},
        {'#', '#', '#', '.', '#', '.'}},
       {{'.', '#', '#'},
        {'.', '#', '#'},
        {'#', '#', '*'},
        {'#', '*', '.'},
        {'#', '.', '*'},
        {'#', '.', '.'}}},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
