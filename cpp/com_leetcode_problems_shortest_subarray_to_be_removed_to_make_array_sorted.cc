#include <gtest/gtest.h>

#include <algorithm>
#include <iterator>
#include <vector>

namespace {
class Solution {
  public:
  int findLengthOfShortestSubarray(std::vector<int>& A) {
    auto l = A.begin();
    // Find longest sorted prefix
    while (std::next(l) != A.end() && *l <= *std::next(l)) {
      l++;
    }
    if (std::next(l) == A.end()) {
      // Already sorted
      return 0;
    }
    // Find longest sorted suffix
    auto r = std::prev(A.end());
    while (r != l && *std::prev(r) <= *r) {
      r--;
    }
    int removal_count = std::min(r - A.begin(), A.end() - l - 1);
    // Merge prefix and suffix
    for (auto i = A.begin(), j = r; j != A.end() && i != l + 1;) {
      if (*i <= *j) {
        removal_count = std::min(removal_count, static_cast<int>(j - i - 1));
        ++i;
      } else {
        ++j;
      }
    }
    return removal_count;
  }
};

struct TV {
  std::vector<int> arr;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().findLengthOfShortestSubarray(tv.arr);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{1, 2, 3, 10, 4, 2, 3, 5}, 3},
    TV{{5, 4, 3, 2, 1}, 4},
    TV{{1, 2, 3}, 0},
    TV{{1, 2, 3, 10, 0, 7, 8, 9}, 2},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
