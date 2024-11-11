#include <gtest/gtest.h>

#include <algorithm>

#include "gtest/gtest.h"

namespace {
class Solution {
  public:
  int maximumSwap(int num) {
    std::string n = std::to_string(num);
    int best = num;
    for (auto it = n.begin(); it != n.end(); ++it) {
      for (auto jt = it + 1; jt != n.end(); ++jt) {
        std::iter_swap(it, jt);
        const int swapped = std::stoi(n);
        best = std::max(best, swapped);
        std::iter_swap(it, jt);
      }
    }
    return best;
  }
};

struct TV {
  int num;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().maximumSwap(tv.num);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{2736, 7236},
    TV{9973, 9973},
    TV{1, 1},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
