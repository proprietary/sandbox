#include <gtest/gtest.h>

#include <iterator>
#include <vector>

namespace {
class Solution {
  public:
  std::vector<int> resultsArray(std::vector<int>& nums, int k) {
    const auto n = nums.size();
    std::vector<int> results;
    results.reserve(n - k + 1);
    auto l = nums.begin();
    auto r = nums.begin();
    int c = 1;
    for (; r != nums.end(); ++r) {
      if (r != nums.begin() && *std::prev(r) + 1 == *r) {
        ++c;
      }
      if (r - l + 1 > k) {
        if (*l + 1 == *std::next(l)) {
          --c;
        }
        ++l;
      }
      if (r - l + 1 == k) {
        results.push_back(c == k ? *r : -1);
      }
    }
    return results;
  }
};

struct TV {
  std::vector<int> nums;
  int k;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().resultsArray(tv.nums, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{1, 2, 3, 4, 3, 2, 5}, 3, {3, 4, -1, -1, -1}},
    TV{{2, 2, 2, 2, 2}, 4, {-1, -1}},
    TV{{3, 2, 3, 2, 3, 2}, 2, {-1, 3, -1, 3, -1}},
    TV{{1}, 1, {1}},
    TV{{1, 4}, 1, {1, 4}},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
