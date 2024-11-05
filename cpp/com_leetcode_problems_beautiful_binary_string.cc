#include <gtest/gtest.h>

#include <string>

namespace {
class Solution {
  public:
  int minChanges(std::string s) {
    int differences = 0;
    for (size_t i = 0; i < s.length(); i += 2) {
      differences += s[i] != s[i + 1];
    }
    return differences;
  }
};

struct TV {
  std::string input;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().minChanges(tv.input);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{"1001", 2},
    TV{"10", 1},
    TV{"0000", 0},
    TV{"11000111", 1},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
