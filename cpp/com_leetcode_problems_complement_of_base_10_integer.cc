#include <gtest/gtest.h>
#include <iostream>

class Solution {
public:
    int bitwiseComplement(int n) {
		if (n == 0) {
			return 1;
		}
        int n_bits = 0;
        for (int n_ = n; n_ > 0; n_ /= 2) {
            n_bits++;
        }
		std::cout << "n_bits: " << n_bits << std::endl;
        int o = 0;
        for (int m = 0; m < n_bits; m++) {
            o += 1 << m;
        }
		std::cout << "o: " << o << std::endl;
        return n ^ o;
    }
};

TEST(Leetcode, TestExample1) {
	Solution s{};
	EXPECT_EQ(2, s.bitwiseComplement(5));
}
