#include <gtest/gtest.h>

#include <iostream>

class Solution {
  public:
  int bitwiseComplement(int n) {
    if (n == 0) {
      return 1;
    }
    int m = 0;
    int o = n;
    for (; o > 0; o /= 2) {
      m = m << 1 | 1;
    }
    // std::cout << "o: " << o << std::endl << "m: " << m << std::endl;
    return n ^ m;
  }
};

TEST(Leetcode, TestExample1) {
  Solution s{};
  EXPECT_EQ(2, s.bitwiseComplement(5));
  EXPECT_EQ(0, s.bitwiseComplement(7));
  EXPECT_EQ(5, s.bitwiseComplement(10));
  EXPECT_EQ(1, s.bitwiseComplement(0));
}
