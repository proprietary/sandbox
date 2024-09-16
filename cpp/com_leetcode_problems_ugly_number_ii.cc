#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <unordered_map>
#include <vector>

class Solution {
  public:
  Solution() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  }

  int nthUglyNumber(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    int two = 0, three = 0, five = 0;
    std::vector<int> dp(n);
    dp[0] = 1;
    for (int i = 1; i < n; ++i) {
      dp[i] = std::min({dp[two] * 2, dp[three] * 3, dp[five] * 5});
      if (dp[i] == dp[two] * 2) two++;
      if (dp[i] == dp[three] * 3) three++;
      if (dp[i] == dp[five] * 5) five++;
    }
    return dp[n - 1];
  }
};

struct TestVec {
  int n;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, minSteps) {
  const auto &tv = GetParam();

  const int actual = Solution().nthUglyNumber(tv.n);

  EXPECT_EQ(actual, tv.expected);
}

static const auto TEST_CASES = ::testing::Values(
    TestVec{.n = 10, .expected = 12}, TestVec{.n = 1, .expected = 1},
    TestVec{.n = 11, .expected = 15}, TestVec{.n = 103, .expected = 1728},
    TestVec{.n = 371, .expected = 218700},
    TestVec{.n = 376, .expected = 234375});

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
