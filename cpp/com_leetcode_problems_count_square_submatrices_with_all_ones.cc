#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

class Solution {
  public:
  int countSquares(std::vector<std::vector<int>>& matrix) {
    int ans = 0;
    const int m = matrix.size();
    const int n = matrix[0].size();
    std::vector<std::vector<int>> dp(m, std::vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
      dp[0][i] = matrix[0][i];
      ans += dp[0][i];
    }
    for (int i = 1; i < m; i++) {
      dp[i][0] = matrix[i][0];
      ans += dp[i][0];
    }
    for (int i = 1; i < m; i++) {
      for (int j = 1; j < n; j++) {
        if (matrix[i][j] == 0) {
          dp[i][j] = 0;
        } else {
          dp[i][j] =
              1 + std::min({dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1]});
        }
        ans += dp[i][j];
      }
    }
    return ans;
  }
};

struct TestVec {
  std::vector<std::vector<int>> matrix;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Example) {
  auto tv = GetParam();

  EXPECT_EQ(tv.expected, Solution().countSquares(tv.matrix));
}

static auto cases = {
    TestVec{.matrix = {{0, 1, 1, 1}, {1, 1, 1, 1}, {0, 1, 1, 1}},
            .expected = 15},
    TestVec{.matrix = {{1, 0, 1}, {1, 1, 0}, {1, 1, 0}}, .expected = 7}};
INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, ::testing::ValuesIn(cases));
