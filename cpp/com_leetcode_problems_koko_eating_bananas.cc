#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
class Solution {
  public:
  int minEatingSpeed(std::vector<int>& piles, int h) {
    auto can_eat_bananas = [&piles, &h](const int speed) -> bool {
      int hours_taken = 0;
      for (const int pile : piles) {
        hours_taken += (pile + speed - 1) / speed;
      }
      return hours_taken <= h;
    };
    int l = 1;
    int r = *std::ranges::max_element(piles);
    while (l < r) {
      const int m = l + (r - l) / 2;
      if (can_eat_bananas(m)) {
        r = m;
      } else {
        l = m + 1;
      }
    }
    return l;
  }
};

struct TV {
  std::vector<int> piles;
  int h;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().minEatingSpeed(tv.piles, tv.h);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{3, 6, 7, 11}, 8, 4},
    TV{{30, 11, 23, 4, 20}, 5, 30},
    TV{{30, 11, 23, 4, 20}, 6, 23},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
