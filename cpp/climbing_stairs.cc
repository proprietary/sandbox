#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

class Solution1 {
  public:
  std::unordered_map<int, int> memo_table;

  int climbStairs(int n) {
    if (n <= 1) {
      return 1;
    }
    if (memo_table.find(n) != memo_table.end()) {
      return memo_table[n];
    }
    int ways = climbStairs(n - 1) + climbStairs(n - 2);
    memo_table[n] = ways;
    return ways;
  }
};

class Solution2 {
  public:
  int climbStairs(int n) {
    std::vector<int> xs{};
    xs.resize(n + 1);
    std::fill(xs.begin(), xs.end(), 0);
    xs[0] = 0;
    xs[1] = 1;
    xs[2] = 2;
    for (int i = 3; i <= n; ++i) {
      xs[i] = xs[i - 1] + xs[i - 2];
    }
    return xs[n];
  }
};

TEST(Leetcode, TestKnownCases) {
  Solution1 solution{};
  EXPECT_EQ(2, solution.climbStairs(2));
  EXPECT_EQ(3, solution.climbStairs(3));
}

TEST(Leetcode, TestDPSolution) {
  Solution1 memoized{};
  Solution2 dp{};
  for (int i = 1; i < 45; ++i) {
    auto from_memoized = memoized.climbStairs(i);
    auto from_dp = dp.climbStairs(i);
    if (from_memoized != from_dp) {
      std::cerr << "failed on " << i << std::endl;
    }
    ASSERT_EQ(from_memoized, from_dp);
  }
}
