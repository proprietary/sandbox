/*
 * Leetcode 58. Length of Last Word
 */
#include <gtest/gtest.h>

#include <string>

class Solution {
  public:
  int lengthOfLastWord(std::string s) {
    int length = 0;
    auto it = s.rbegin();
    while (it != s.rend() && *it == ' ') {
      ++it;
    }
    for (; it != s.rend() && *it != ' '; ++it) {
      ++length;
    }
    return length;
  }
};

TEST(Leetcode, Solution) {
  Solution solution{};
  EXPECT_EQ(5, solution.lengthOfLastWord("Hello World"));
  EXPECT_EQ(1, solution.lengthOfLastWord("a "));
}
