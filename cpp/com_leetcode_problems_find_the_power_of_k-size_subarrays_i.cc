#include <gtest/gtest.h>

#include <vector>

namespace {
class Solution {
  public:
  std::vector<int> resultsArray(std::vector<int>& nums, int k) {
    const auto n = nums.size();
    std::vector<int> results(n - k + 1);
    for (int i = 0; i < n - k + 1; ++i) {
      for (int j = i + 1; j < i + k; ++j) {
        if (nums[j - 1] + 1 != nums[j]) {
          goto neg;
        }
      }
      goto pos;
    neg:
      results[i] = -1;
      continue;
    pos:
      results[i] = nums[i + k - 1];
    }
    return results;
  }
};

struct TV {
  std::vector<int> nums;
  int k;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().resultsArray(tv.nums, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{1, 2, 3, 4, 3, 2, 5}, 3, {3, 4, -1, -1, -1}},
    TV{{2, 2, 2, 2, 2}, 4, {-1, -1}},
    TV{{3, 2, 3, 2, 3, 2}, 2, {-1, 3, -1, 3, -1}},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
