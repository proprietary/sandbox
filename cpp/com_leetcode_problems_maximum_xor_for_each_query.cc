#include <gtest/gtest.h>

#include <functional>
#include <numeric>
#include <vector>

namespace {
class Solution {
  public:
  std::vector<int> getMaximumXor(std::vector<int>& nums, int maximum_bit) {
    std::vector<int> ans;
    ans.reserve(nums.size());
    int xor_sum = std::accumulate(nums.begin() + 1, nums.end(), *nums.begin(),
                                  std::bit_xor<>{});
    const uint32_t mask = (1 << maximum_bit) - 1;
    for (auto it = nums.rbegin(); it != nums.rend(); ++it) {
      uint32_t k_max = xor_sum ^ mask;
      ans.push_back(static_cast<int>(k_max));
      xor_sum ^= *it;
    }
    return ans;
  }
};

struct TV {
  std::vector<int> nums;
  int maximum_bit;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().getMaximumXor(tv.nums, tv.maximum_bit);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{0, 1, 1, 3}, 2, {0, 3, 2, 3}},
    TV{{2, 3, 4, 7}, 3, {5, 2, 6, 5}},
    TV{{0, 1, 2, 2, 5, 7}, 3, {4, 3, 6, 4, 6, 7}},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
