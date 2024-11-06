#include <gtest/gtest.h>

#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_set>

namespace {
class Solution {
  int max_splits(std::unordered_set<std::string_view>& q, std::string_view s,
                 size_t idx) {
    if (idx == s.length()) {
      return 0;
    }
    int res = 0;
    for (size_t jdx = idx + 1; jdx <= s.length(); jdx++) {
      auto ss = s.substr(idx, jdx - idx);
      if (!q.contains(ss)) {
        q.insert(ss);
        res = std::max(res, 1 + max_splits(q, s, jdx));
        q.erase(ss);
      }
    }
    return res;
  }

  public:
  int maxUniqueSplit(std::string s) {
    std::unordered_set<std::string_view> q;
    return max_splits(q, s, 0);
  }
};

struct TV {
  std::string input;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().maxUniqueSplit(tv.input);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{"ababccc", 5},
    TV{"aba", 2},
    TV{"aa", 1},
    TV{"wwwzfvedwfvhsww", 11},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
