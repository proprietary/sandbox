#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <vector>

#include "test_case_helper.hpp"

class Solution {
  public:
  int minimumDeletions(std::string s) {
    int cur = 0;
    int bs = 0;
    for (int i = 0; i < s.length(); i++) {
      if (s[i] == 'a') {
        cur = std::min(cur + 1, bs);
      } else {
        bs++;
      }
    }
    return cur;
  }
};

struct TestVec {
  std::string input;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  const auto actual = Solution().minimumDeletions(tv.input);

  EXPECT_EQ(actual, tv.expected);
}

auto parse_test_cases() {
  static constexpr std::string_view input = R"(
aababbab
2
bbaaaaabb
2
baababbaabbaaabaabbabbbabaaaaaabaabababaaababbb
18
)";
  std::vector<TestVec> tvs;
  auto cases = partition_test_cases(input, 2);
  for (auto c : cases) {
    tvs.push_back(TestVec{.input = c[0], .expected = std::stoi(c[1])});
  }
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
