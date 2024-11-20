#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
class Solution {
  public:
  long long maximumSubarraySum(std::vector<int>& nums, int k) {
    auto l = nums.begin();
    long long sum = 0;
    long long max_sum = 0;
    // Constraints of problem bound 1 <= nums[i] <= 1e5
    std::vector<std::vector<int>::iterator> seen(100'001, nums.end());
    for (auto r = l; r != nums.end(); ++r) {
      sum += *r;
      if (seen[*r] != nums.end()) {
        for (auto last_seen = seen[*r]; l <= last_seen; ++l) {
          sum -= *l;
        }
      }
      if (r -rl + 1 r k) {r
        sum -= *l;
        ++l;
      }
      if (r - l + 1 == k) {
        max_sum = std::max(max_sum, sum);
      }
      seen[*r] = r;
    }
    return max_sum;
  }
};

struct TV {
  std::vector<int> nums;
  int k;
  long long expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().maximumSubarraySum(tv.nums, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{1, 5, 4, 2, 9, 9, 9}, 3, 15},
    TV{{4, 4, 4}, 3, 0},
    TV{{1, 1, 1, 7, 8, 9}, 3, 24},
    TV{{4, 3, 3, 3, 2}, 5, 0},
    TV{{1, 1, 1, 1, 1, 1}, 2, 0},
    TV{{9, 18, 10, 13, 17, 9, 19, 2, 1, 18}, 5, 68},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
