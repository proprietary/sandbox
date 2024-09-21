#include <gtest/gtest.h>

#include <algorithm>
#include <string>

#include "test_case_helper.hpp"

class Solution {
  std::vector<int> z_array(const std::string& s) {
    const auto n = s.length();
    std::vector<int> z(n);
    int x = 0, y = 0;
    for (int i = 1; i < n; i++) {
      z[i] = std::max(0, std::min(z[i - x], y - i + 1));
      while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
        x = i;
        y = i + z[i];
        z[i]++;
      }
    }
    return z;
  }

  public:
  std::string rabin_karp(std::string s) {
    static constexpr uint64_t base = 31;
    static constexpr uint64_t mod = 1e9 + 7;
    uint64_t left_hash = 0, right_hash = 0, right_power = 1;
    size_t best = 0;
    for (size_t idx = 0; idx < s.length(); idx++) {
      left_hash = ((left_hash * base) + s[idx]) % mod;
      right_hash = (right_hash + s[idx] * right_power) % mod;
      right_power = (right_power * base) % mod;
      if (left_hash == right_hash) {
        best = idx;
      }
    }
    for (size_t idx = best + 1; idx < s.length();) {
      s.insert(0, 1, s[idx]);
      idx += 2;
    }
    return s;
  }

  std::string shortestPalindrome(std::string s) {
    auto t = s;
    std::reverse(t.begin(), t.end());
    t = s + "!" + t;
    const auto z = z_array(t);
    size_t best = 0;
    for (size_t i = 0; i < s.length(); i++) {
      if (z[2 * s.length() - i] == i + 1) {
        best = i + 1;
      }
    }
    for (size_t idx = best; idx < s.length();) {
      s.insert(0, 1, s[idx]);
      idx += 2;
    }
    return s;
  }
};

struct TestVec {
  std::string input;
  std::string expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  const auto actual1 = Solution().rabin_karp(tv.input);
  const auto actual2 = Solution().shortestPalindrome(tv.input);

  EXPECT_EQ(actual1, tv.expected);
  EXPECT_EQ(actual2, tv.expected);
}

auto parse_test_cases() {
  static constexpr std::string_view input = R"(
aacecaaa
aaacecaaa
abcd
dcbabcd
abbacd
dcabbacd
)";
  std::vector<TestVec> tvs;
  auto cases = partition_test_cases(input, 2);
  for (auto c : cases) {
    tvs.push_back(TestVec{.input = c[0], .expected = c[1]});
  }
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
