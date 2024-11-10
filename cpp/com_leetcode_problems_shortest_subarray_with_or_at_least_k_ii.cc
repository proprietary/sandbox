#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <limits>
#include <vector>

namespace {
auto to_num(const std::array<int, 32>& bits) -> int {
  int n = 0;
  for (size_t i = 0; i < 32; ++i) {
    if (bits[i] > 0) {
      n |= 1 << i;
    }
  }
  return n;
}
class Solution {
  public:
  int minimumSubarrayLength(std::vector<int>& nums, int k) {
    if (k == 0) return 1;
    const size_t N = nums.size();
    int res = std::numeric_limits<int>::max();
    std::array<int, 32> window;
    std::fill(window.begin(), window.end(), 0);

    for (size_t l = 0, r = 0; r < N; ++r) {
      for (size_t i = 0; i < 32; ++i)
        if (nums[r] & (1 << i)) ++window[i];
      while (l <= r && to_num(window) >= k) {
        res = std::min(res, int(r - l + 1));
        for (size_t i = 0; i < 32; ++i) {
          if (nums[l] & (1 << i)) {
            --window[i];
          }
        }
        ++l;
      }
    }

    return res == std::numeric_limits<int>::max() ? -1 : res;
  }
};

struct TV {
  std::vector<int> nums;
  int k;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().minimumSubarrayLength(tv.nums, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{1, 2, 3}, 2, 1},
    TV{{2, 1, 8}, 10, 3},
    TV{{1, 2}, 0, 1},
    TV{{1, 2, 32, 21}, 55, 3},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
