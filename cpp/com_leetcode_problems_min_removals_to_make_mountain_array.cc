#include <fmt/format.h>
#include <gtest/gtest.h>

#include <vector>

#include "gtest/gtest.h"

namespace {
class Solution {
  public:
  int minimumMountainRemovals(std::vector<int>& nums) {
    const int n = nums.size();
    std::vector<int> lis(n, 1);
    std::vector<int> lds(n, 1);
    for (int i = 1; i < n; i++) {
      for (int prev = 0; prev < i; prev++) {
        if (nums[prev] < nums[i]) {
          lis[i] = std::max(lis[i], lis[prev] + 1);
        }
      }
    }
    for (int i = n - 1; i >= 0; i--) {
      for (int prev = i + 1; prev < n; prev++) {
        if (nums[prev] < nums[i]) {
          lds[i] = std::max(lds[i], lds[prev] + 1);
        }
      }
    }
    int best = 0;
    for (int i = 1; i < n - 1; i++) {
      if (lis[i] > 1 && lds[i] > 1) {
        best = std::max(best, lis[i] + lds[i]);
      }
    }
    return n - best + 1;
  }
};

struct TV {
  std::vector<int> input;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();
  auto actual = Solution().minimumMountainRemovals(tv.input);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{1, 3, 1}, 0},
    TV{{2, 1, 1, 5, 6, 2, 3, 1}, 3},
    TV{{4, 3, 2, 1, 1, 2, 3, 1}, 4},
    TV{{100, 92, 89, 77, 74, 66, 64, 66, 64}, 6},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
