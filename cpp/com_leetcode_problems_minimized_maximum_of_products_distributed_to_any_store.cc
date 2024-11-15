#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

namespace {
class Solution {
  public:
  int minimizedMaximum(int n, std::vector<int>& quantities) {
    if (quantities.size() == 1) {
      return quantities.front();
    }
    auto can_distribute = [&quantities, &n](const int k) -> bool {
      int stores = 0;
      for (const auto quantity : quantities) {
        stores += (quantity + k - 1) / k;
      }
      return stores > n;
    };
    int l = 1;
    int r = *std::max_element(quantities.begin(), quantities.end());
    while (l < r) {
      int mid = l + (r - l) / 2;
      if (can_distribute(mid)) {
        l = mid + 1;
      } else {
        r = mid;
      }
    }
    return l;
  }
};

struct TV {
  int n;
  std::vector<int> quantities;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().minimizedMaximum(tv.n, tv.quantities);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{6, {11, 6}, 3},
    TV{7, {15, 10, 10}, 5},
    TV{1, {100000}, 100000},
    TV{1, {1}, 1},
    TV{2, {5, 7}, 7},
    TV{100000,
       {4, 4, 4, 2, 4, 2, 4, 1, 5, 4, 5, 4, 1,
        1, 2, 2, 4, 1, 1, 4, 5, 3, 3, 4, 1, 2},
       1},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
