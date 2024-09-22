#include <gtest/gtest.h>

#include <vector>

#include "test_case_helper.hpp"

class Solution {
  public:
  std::vector<int> countSmaller(std::vector<int>& nums) {
    std::vector<int> counts(nums.size(), 0);
    std::vector<int> sorted;
    sorted.reserve(nums.size());
    for (int i = nums.size() - 1; i >= 0; i--) {
      int m = 0, l = 0, r = sorted.size();
      while (l < r) {
        m = (r + l) / 2;
        if (sorted[m] < nums[i]) {
          l = m + 1;
        } else {
          r = m;
        }
      }
      int next_idx = l;
      r = sorted.size();
      while (next_idx < r) {
        m = (next_idx + r) / 2;
        if (sorted[m] > nums[i]) {
          r = m;
        } else {
          next_idx = m + 1;
        }
      }

      counts[i] = l;
      sorted.insert(sorted.begin() + next_idx, nums[i]);
    }
    return counts;
  }
};

struct TestVec {
  std::vector<int> input;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  const auto actual = Solution().countSmaller(tv.input);

  EXPECT_EQ(actual, tv.expected);
}

auto parse_test_cases() {
  static constexpr std::string_view input = R"(
[5,2,6,1]
[2,1,1,0]
[-1]
[0]
[-1,-1]
[0,0]
[26,78,27,100,33,67,90,23,66,5,38,7,35,23,52,22,83,51,98,69,81,32,78,28,94,13,2,97,3,76,99,51,9,21,84,66,65,36,100,41]
[10,27,10,35,12,22,28,8,19,2,12,2,9,6,12,5,17,9,19,12,14,6,12,5,12,3,0,10,0,7,8,4,0,0,4,3,2,0,1,0]
)";
  std::vector<TestVec> tvs;
  auto cases = partition_test_cases(input, 2);
  for (auto c : cases) {
    tvs.push_back(TestVec{.input = IntVecParser(c[0]).parse(),
                          .expected = IntVecParser(c[1]).parse()});
  }
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
