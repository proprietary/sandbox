#include <gtest/gtest.h>

#include <string>
#include <vector>

#include "test_case_helper.hpp"

class Solution {
  public:
  std::string convert(std::string s, int numRows) {
    std::vector<std::string> rows(numRows, "");
    size_t idx = 0;
    while (idx < s.length()) {
      for (int i = 0; i < numRows; i++) {
        if (idx < s.length()) {
          rows[i] += s[idx];
          idx++;
        }
      }
      for (int i = numRows - 2; i > 0; i--) {
        if (idx < s.length()) {
          rows[i] += s[idx];
          idx++;
        }
      }
    }
    std::string ans;
    for (const auto& row : rows) {
      ans += row;
    }
    return ans;
  }
};

struct TestVec {
  std::string input;
  int num_rows;
  std::string expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  const auto actual = Solution().convert(tv.input, tv.num_rows);

  EXPECT_EQ(actual, tv.expected);
}

auto parse_test_cases() {
  static constexpr std::string_view input = R"(
PAYPALISHIRING
3
PAHNAPLSIIGYIR
PAYPALISHIRING
4
PINALSIGYAHRPI
A
1
A
)";
  std::vector<TestVec> tvs;
  auto cases = partition_test_cases(input, 3);
  for (auto c : cases) {
    tvs.push_back(
        TestVec{.input = c[0], .num_rows = std::stoi(c[1]), .expected = c[2]});
  }
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
