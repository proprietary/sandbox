#include <gtest/gtest.h>

#include <vector>

namespace {
class Solution {
  public:
  std::vector<int> resultsArray(std::vector<int>& nums, int k) {
    const auto n = nums.size();
    std::vector<int> streaks(n);
    streaks[0] = 1;
    for (size_t i = 1; i < n; ++i) {
      const bool is_consecutive = nums[i - 1] + 1 == nums[i];
      if (is_consecutive) {
        streaks[i] = streaks[i - 1] + 1;
      } else {
        streaks[i] = 1;
      }
    }
    std::vector<int> results;
    results.reserve(n - k + 1);
    for (size_t i = k - 1; i < n; ++i) {
      if (streaks[i] >= k) {
        results.push_back(nums[i]);
      } else {
        results.push_back(-1);
      }
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
