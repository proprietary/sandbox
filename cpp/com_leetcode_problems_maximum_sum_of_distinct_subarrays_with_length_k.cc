#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_map>
#include <vector>

namespace {
class Solution {
  public:
  long long maximumSubarraySum(std::vector<int>& nums, int k) {
    auto l = nums.begin();
    auto r = l + k - 1;
    long long sum = 0;
    long long max_sum = 0;
    std::unordered_map<int, int> counts;
    for (auto it = l; it != r + 1; ++it) {
      ++counts[*it];
      sum += *it;
    }
    if (counts.size() == k) {
      max_sum = sum;
    }
    while (r != nums.end()) {
      sum -= *l;
      --counts[*l];
      if (counts[*l] == 0) {
        counts.erase(*l);
      }
      ++l;
      ++r;
      if (r == nums.end()) {
        break;
      }
      sum += *r;
      counts[*r]++;
      if (counts.size() == k) {
        max_sum = std::max(max_sum, sum);
      }
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
    TV{{1, 5, 4, 2, 9, 9, 9}, 3, 15}, TV{{4, 4, 4}, 3, 0},
    TV{{1, 1, 1, 7, 8, 9}, 3, 24},    TV{{4, 3, 3, 3, 2}, 5, 0},
    TV{{1, 1, 1, 1, 1, 1}, 2, 0},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
