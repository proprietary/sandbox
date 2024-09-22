#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <concepts>
#include <deque>
#include <iterator>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "test_case_helper.hpp"

class Solution {
  int64_t calc_steps(int64_t n, int64_t c, int64_t s) {
    int64_t steps = 0;
    while (c <= n) {
      steps +=
	  std::min(n + 1, s) - c;
      c *= 10;
      s *= 10;
    }
    return steps;
  }

  public:
  int findKthNumber(int n, int k) {
    int cur = 1;
    k--;
    while (k > 0) {
      int64_t steps = calc_steps(n, cur, cur + 1);
      if (steps <= k) {
	cur += 1;
	k -= steps;
      } else {
	cur *= 10;
	k -= 1;
      }
    }
    return cur;
  }

  int findKthNumber2(int n, int k) {
    int count = 1;
    uint64_t num = 1;
    for (; count < k; count++) {
      if (num * 10 <= n) {
	num *= 10;
      } else {
	while (num % 10 == 9 || num == n) {
	  num /= 10;
	}
	num++;
      }
    }
    return num;
  }
};

struct TestVec {
  int n;
  int k;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TestVec> {};

TEST_P(ParamTest, LogTime) {
  auto tv = GetParam();

  const auto actual = Solution().findKthNumber(tv.n, tv.k);

  EXPECT_EQ(actual, tv.expected);
}

TEST_P(ParamTest, LinearTime) {
  auto tv = GetParam();

  EXPECT_EQ(Solution().findKthNumber2(tv.n, tv.k), tv.expected);
}

auto parse_test_cases() {
  static constexpr std::string_view input = R"(
13
2
10
1
1
1
2
2
2
10
3
2
681692778
351251360
416126219
719885387
209989719
288990744
)";
  std::vector<TestVec> tvs;
  auto cases = partition_test_cases(input, 3);
  for (auto c : cases) {
    tvs.push_back(TestVec{.n = std::stoi(c[0]),
			  .k = std::stoi(c[1]),
			  .expected = std::stoi(c[2])});
  }
  return ::testing::ValuesIn(tvs);
}

static const auto TEST_CASES = parse_test_cases();

INSTANTIATE_TEST_SUITE_P(ParamTestSuite, ParamTest, TEST_CASES);
