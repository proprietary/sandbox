#include <gtest/gtest.h>

#include <string>
#include <string_view>
#include <vector>

#include "test_case_helper.hpp"

class Solution {
  public:
  int minSwaps(std::string s) {
    int open_count = 0;
    int close_count = 0;
    int swaps = 0;
    for (const auto c : s) {
      open_count += c == '[' ? 1 : 0;
      close_count += c == ']' ? 1 : 0;
      if (open_count < close_count) {
        swaps++;
        open_count++;
        close_count--;
      }
    }
    return swaps;
  }
};

struct TestVec {
  std::string s;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Example) {
  auto tv = GetParam();

  EXPECT_EQ(tv.expected, Solution().minSwaps(tv.s));
}

auto parse_test_cases() -> std::vector<TestVec> {
  static constexpr std::string_view raw =
      R"(
][][
1
]]][[[
2
[]
0
)";
  std::vector<TestVec> test_cases;
  for (auto c : partition_test_cases(raw, 2)) {
    test_cases.emplace_back(TestVec{.s = c[0], .expected = std::stoi(c[1])});
  }
  return test_cases;
}

static auto cases = parse_test_cases();
INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, ::testing::ValuesIn(cases));
