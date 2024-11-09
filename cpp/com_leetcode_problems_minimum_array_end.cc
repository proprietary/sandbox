#include <gtest/gtest.h>

namespace {
class Solution {
  public:
  long long minEnd(int n, int x) {
    uint64_t c = x;
    uint64_t bit_x = 1;
    uint64_t bit_n = 1;
    while (bit_n < n) {
      if ((bit_x & x) == 0) {
        if (bit_n & (n - 1)) {
          c |= bit_x;
        }
        bit_n <<= 1;
      }
      bit_x <<= 1;
    }
    return c;
  }
};

struct TV {
  int n;
  int x;
  long long expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().minEnd(tv.n, tv.x);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{3, 4, 6},
    TV{2, 7, 15},
    TV{6715154, 7193485, 55012476815},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
