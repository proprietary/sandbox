// Leetcode #1652

#include <gtest/gtest.h>

#include <vector>

namespace {
class Solution {
  public:
  std::vector<int> decrypt(std::vector<int>& code, int k) {
    const int n = code.size();
    std::vector<int> ans(n, 0);
    if (k > 0) {
      for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < k; ++j) {
          sum += code[(i + 1 + j) % n];
        }
        ans[i] = sum;
      }
    } else if (k < 0) {
      for (int i = 0; i < n; ++i) {
        int sum = 0;
        for (int j = 0; j < -k; ++j) {
          sum += code[(i - 1 - j + n) % n];
        }
        ans[i] = sum;
      }
    }
    return ans;
  }
};

struct TV {
  std::vector<int> code;
  int k;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().decrypt(tv.code, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{5, 7, 1, 4}, 3, {12, 10, 16, 13}},
    TV{{1, 2, 3, 4}, 0, {0, 0, 0, 0}},
    TV{{2, 4, 9, 3}, -2, {12, 5, 6, 13}},
    TV{{10, 5, 7, 7, 3, 2, 10, 3, 6, 9, 1, 6},
       -4,
       {22, 26, 22, 28, 29, 22, 19, 22, 18, 21, 28, 19}},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
