#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

namespace {
std::string to_string(const std::vector<int>& row) {
  std::string res;
  for (auto it = row.begin(); it != row.end(); ++it) {
    res.push_back(*it == 0 ? '0' : '1');
  }
  return res;
}
class Solution {
  public:
  int maxEqualRowsAfterFlips(std::vector<std::vector<int>>& matrix) {
    std::unordered_map<std::string, int> m;
    for (auto& row : matrix) {
      if (row[0] > 0) {
        for (auto it = row.begin(); it != row.end(); ++it) {
          *it = *it == 1 ? 0 : 1;
        }
      }
      m[to_string(row)]++;
    }
    int best = 0;
    for (const auto& [_, count] : m) {
      best = std::max(best, count);
    }
    return best;
  }
};

struct TV {
  std::vector<std::vector<int>> matrix;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().maxEqualRowsAfterFlips(tv.matrix);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{{0, 1}, {1, 1}}, 1},
    TV{{{0, 1}, {1, 0}}, 2},
    TV{{{0, 0, 0}, {0, 0, 1}, {1, 1, 0}}, 2},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
