#include <gtest/gtest.h>

#include <algorithm>
#include <bitset>
#include <string>

namespace {
class Solution {
  public:
  int countPalindromicSubsequence(std::string s) {
    std::bitset<26> S;
    int ans = 0;
    for (char c = 'a'; c <= 'z'; ++c) {
      auto l = std::find(s.begin(), s.end(), c);
      auto r = std::find_end(l, s.end(), l, l + 1);
      if (r != s.end() && std::distance(l, r) > 1) {
        for (auto it = l + 1; it < r; ++it) {
          S.set(*it - 'a');
        }
        ans += S.count();
        S.reset();
      }
    }
    return ans;
  }
};

struct TV {
  std::string s;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().countPalindromicSubsequence(tv.s);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{"aabca", 3},
    TV{"adc", 0},
    TV{"bbcbaba", 4},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
