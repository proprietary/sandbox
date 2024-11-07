#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
class Solution {
  public:
  int largestCombination(std::vector<int>& candidates) {
    std::vector<int> l(24, 0);
    for (int i = 0; i < l.size(); i++) {
      l[i] = std::count_if(candidates.begin(), candidates.end(),
                           [&i](const int n) { return n & (1 << i); });
    }
    return *std::max_element(l.begin(), l.end());
  }
};

struct TV {
  std::vector<int> input;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().largestCombination(tv.input);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{16, 17, 71, 62, 12, 24, 14}, 4},
    TV{{8, 8}, 2},
    TV{{33, 93, 31,  99, 74, 37, 3,  4,  2,  94, 77, 10, 75, 54, 24,
        95, 65, 100, 41, 82, 35, 65, 38, 49, 85, 72, 67, 21, 20, 31},
       18},
    TV{{84, 40, 66, 44, 91, 90, 1,  14, 73, 51, 47, 35, 18, 46, 18,
        65, 55, 18, 16, 45, 43, 58, 90, 92, 91, 43, 44, 76, 85, 72,
        24, 89, 60, 94, 81, 90, 86, 79, 84, 41, 41, 28, 44},
       28},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
