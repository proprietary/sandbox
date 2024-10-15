#include <gtest/gtest.h>

#include <ranges>
#include <string>

class Solution {
  public:
  long long minimumSteps(std::string s) {
    long long ans = 0;
    int zeros = 0;
    for (const char n : std::views::reverse(s)) {
      if (n == '0') {
        zeros++;
      } else {
        ans += zeros;
      }
    }
    return ans;
  }
};

struct TestVec {
  std::string s;
  long long expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Example) {
  auto tv = GetParam();

  EXPECT_EQ(tv.expected, Solution().minimumSteps(tv.s));
}

static auto cases = {TestVec{.s = "101", .expected = 1},
                     TestVec{.s = "100", .expected = 2},
                     TestVec{.s = "0111", .expected = 0}};
INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, ::testing::ValuesIn(cases));
