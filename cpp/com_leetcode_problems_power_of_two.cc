#include <iostream>

class Solution {
public:
	bool isPowerOfTwo(int n) {
		if (n <= 0) {
			return false;
		}
		unsigned int m = static_cast<unsigned int>(n);
		int c = 0;
		while (m > 0) {
			if ((m & 1) != 0) {
				c += 1;
			}
			if (c > 1) {
				return false;
			}
			m /= 2;
		}
		std::cout << c << std::endl;
		return c == 1;
	}
};

#include <gtest/gtest.h>

TEST(Test, Test) {
	ASSERT_EQ(false, Solution().isPowerOfTwo(-16));
	ASSERT_EQ(false, Solution().isPowerOfTwo(-2147483648));
	ASSERT_EQ(true, Solution().isPowerOfTwo(1024));
	ASSERT_EQ(false, Solution().isPowerOfTwo(0));
}
