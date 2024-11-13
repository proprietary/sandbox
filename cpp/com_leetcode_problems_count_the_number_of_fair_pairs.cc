#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <vector>

namespace {
class Solution {
  using It = std::vector<int>::iterator;

  auto bs(It first, It last, const int target) -> It {
    std::iterator_traits<It>::difference_type count = last - first;
    while (count > 0) {
      auto step = count / 2;
      It mid = first + step;
      if (*mid < target) {
        first = ++mid;
        count -= step + 1;
      } else {
        count = step;
      }
    }
    return first;
  }

  public:
  long long countFairPairs(std::vector<int>& nums, int lower, int upper) {
    std::sort(nums.begin(), nums.end());
    long long ans = 0;
    for (auto it = nums.begin(); it != nums.end(); ++it) {
      const auto lo = bs(it + 1, nums.end(), lower - *it);
      const auto hi = bs(it + 1, nums.end(), upper - *it + 1);
      ans += static_cast<long long>(std::distance(lo, hi));
    }
    return ans;
  }
};

struct TV {
  std::vector<int> nums;
  int lower;
  int upper;
  long long expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().countFairPairs(tv.nums, tv.lower, tv.upper);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{0, 1, 7, 4, 4, 5}, 3, 6, 6},
    TV{{1, 7, 9, 2, 5}, 11, 11, 1},
    TV{{0, 0, 0, 0, 0, 0}, 0, 0, 15},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
