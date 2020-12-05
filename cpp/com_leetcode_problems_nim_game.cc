#include <bits/stdc++.h>

class Solution {
public:
	bool canWinNim(int n) {
		return (n % 4) != 0;
	}
};


#include <gtest/gtest.h>

TEST(Test, Test1) {
	EXPECT_EQ(false, Solution().canWinNim(4));
	EXPECT_EQ(true, Solution().canWinNim(1));
	EXPECT_EQ(true, Solution().canWinNim(2));
	EXPECT_EQ(false, Solution().canWinNim(8));
}
