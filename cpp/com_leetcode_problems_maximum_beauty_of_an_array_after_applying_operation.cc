#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
class Solution {
  public:
  int maximumBeauty(std::vector<int>& nums, int k) {
    std::sort(nums.begin(), nums.end());
    int ans = 0;
    for (auto it = nums.begin(); it != nums.end(); ++it) {
      const auto end = bs(nums, it, 2 * k + *it);
      ans = std::max(ans, static_cast<int>(end - it));
    }
    return ans;
  }

  private:
  auto bs(const std::vector<int>& nums,
          const std::vector<int>::const_iterator start, const int target)
      -> std::vector<int>::const_iterator {
    auto l = start;
    auto r = nums.end();
    while (l < r) {
      const auto m = l + (r - l) / 2;
      if (*m > target) {
        r = m;
      } else {
        l = m + 1;
      }
    }
    return r;
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

  auto actual = Solution().maximumBeauty(tv.nums, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{4, 6, 1, 2}, 2, 3},
    TV{{1, 1, 1, 1}, 10, 4},
    TV{{27, 55}, 1, 1},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
