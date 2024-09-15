#include <gtest/gtest.h>

#include <algorithm>
#include <limits>
#include <vector>

class Solution {
  public:
  Solution() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
  }

  // Recursive solution
  double findMinSteps(int n, int count, int steps, int copy_buffer) {
    if (count > n) {
      return std::numeric_limits<double>::infinity();
    }
    if (n == 1 || n == count) {
      return steps;
    }
    if (count + copy_buffer == n) {
      return steps + 1;
    }
    auto paste_result =
        copy_buffer > 0
            ? findMinSteps(n, count + copy_buffer, steps + 1, copy_buffer)
            : std::numeric_limits<double>::infinity();
    auto copy_result = count != copy_buffer
                           ? findMinSteps(n, count, steps + 1, count)
                           : std::numeric_limits<double>::infinity();
    return std::min(paste_result, copy_result);
  }

  int minSteps(int n) {
    // return findMinSteps(n, 1, 0, 0); // Recursive solution
    std::vector<int> dp(n + 1, 0);
    for (int i = 2; i <= n; i++) {
      dp[i] = i;
      for (int j = (i - 1) / 2; j > 1; j--) {
        if (i % j == 0) {
          dp[i] = dp[j] + i / j;
          break;
        }
      }
    }
    return dp[n];
  }
};

struct TestVec {
  int n;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, minSteps) {
  const auto &tv = GetParam();

  const int actual = Solution().minSteps(tv.n);

  EXPECT_EQ(actual, tv.expected);
}

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest,
                         ::testing::Values(TestVec{3, 3}, TestVec{1, 0},
                                           TestVec{4, 4}, TestVec{12, 7}));
