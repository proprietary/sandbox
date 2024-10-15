#include <fmt/format.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <stack>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

#include "test_case_helper.hpp"

class Solution {
  public:
  int maxWidthRamp(std::vector<int>& nums) {
    std::stack<int> s;
    s.push(0);
    for (int i = 0; i < nums.size(); i++) {
      if (nums[i] < nums[s.top()]) {
        s.push(i);
      }
    }
    int best = 0;
    for (int i = nums.size() - 1; i >= 0; i--) {
      while (!s.empty() && nums[s.top()] <= nums[i]) {
        best = std::max(best, i - s.top());
        s.pop();
      }
    }
    return best;
  }
};

struct TestVec {
  std::vector<int> nums;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Example) {
  auto tv = GetParam();

  EXPECT_EQ(tv.expected, Solution().maxWidthRamp(tv.nums));
}

auto parse_test_cases() -> std::vector<TestVec> {
  static constexpr std::string_view raw =
      R"(
[6,0,8,2,1,5]
4
[9,8,1,0,1,9,4,0,4,1]
7
[2,2,1]
1
[1,0]
0
[2,3,4,1]
2
[24,27,16,25,15,27,25,6,25,27,0,21,27,15,13,8,6,15,9,17,17,2,20,4,8,25,4,27,14,18]
27
[29,28,27,27,22,22,20,16,16,13,13,12,10,8,8,8,8,6,5,4,4,3,3,2,2,2,1,1,1,0]
3
)";
  std::vector<TestVec> test_cases;
  for (auto c : partition_test_cases(raw, 2)) {
    test_cases.emplace_back(TestVec{.nums = IntVecParser(c[0]).parse(),
                                    .expected = std::stoi(c[1])});
  }
  return test_cases;
}

static auto cases = parse_test_cases();
INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, ::testing::ValuesIn(cases));
