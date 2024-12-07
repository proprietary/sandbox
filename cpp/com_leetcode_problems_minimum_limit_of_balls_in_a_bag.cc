#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
class Solution {
  private:
  bool split(const std::vector<int>& nums, const int max_operations,
             const int max_balls) {
    int total = 0;
    for (const int bag : nums) {
      total += ((bag + max_balls - 1) / max_balls) - 1;
      if (total > max_operations) {
        return false;
      }
    }
    return true;
  }

  public:
  int minimumSize(std::vector<int>& nums, int max_operations) {
    int lo = 1, hi = 1e9;
    while (lo < hi) {
      const int mid = lo + (hi - lo) / 2;
      if (split(nums, max_operations, mid)) {
        hi = mid;
      } else {
        lo = mid + 1;
      }
    }
    return lo;
  }
};

struct TV {
  std::vector<int> nums;
  int max_operations;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().minimumSize(tv.nums, tv.max_operations);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{9}, 2, 3},
    TV{{2, 4, 8, 2}, 4, 2},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
