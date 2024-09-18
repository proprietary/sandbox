#include <gtest/gtest.h>

bool isBadVersion(int version);

class Solution {
  public:
  int firstBadVersion(int n) {
    int hi = n;
    int lo = 1;
    while (hi > lo) {
      int mid = lo + (hi - lo) / 2;
      bool res = isBadVersion(mid);
      if (res == true) {
        hi = mid;
      } else if (res == false) {
        lo = mid + 1;
      }
    }
    return lo;
  }
};

static int TEST_BAD_VERSION = 4;

TEST(Leetcode, Solution) {
  Solution solution{};
  TEST_BAD_VERSION = 4;
  EXPECT_EQ(4, solution.firstBadVersion(5));
  TEST_BAD_VERSION = 1;
  EXPECT_EQ(1, solution.firstBadVersion(1));
  TEST_BAD_VERSION = 2;
  EXPECT_EQ(2, solution.firstBadVersion(3));
  TEST_BAD_VERSION = 1;
  EXPECT_EQ(1, solution.firstBadVersion(2));
  TEST_BAD_VERSION = 1702766719;
  EXPECT_EQ(1702766719, solution.firstBadVersion(2126753390));
}

bool isBadVersion(int version) { return version >= TEST_BAD_VERSION; }
