#include <algorithm>
#include <vector>

class Solution {
    private:
	static constexpr int EMPTY = -1;

    public:
	int rob_starting_from(std::vector<int>& memo, std::vector<int>& nums,
			      size_t start_index) {
		if (memo[start_index] != EMPTY) {
			return memo[start_index];
		}
		int a = 0;
		int b = 0;
		if (start_index + 1 < nums.size()) {
			a = rob_starting_from(memo, nums, start_index + 1);
		} else {
			a = nums[start_index];
		}
		if (start_index + 2 < nums.size()) {
			b = rob_starting_from(memo, nums, start_index + 2) +
			    nums[start_index];
		} else {
			b = nums[start_index];
		}
		memo[start_index] = std::max(a, b);
		return memo[start_index];
	}

	int rob(std::vector<int>& nums) {
		auto const len = nums.size();
		std::vector<int> memo(len, EMPTY);
		int res = 0;
		if (nums.size() > 0) {
			res = rob_starting_from(memo, nums, 0);
		}
		return res;
	}
};

#include <gtest/gtest.h>

TEST(Test, TestRobbing) {
	std::vector<int> a = {1, 2, 3, 1};
	ASSERT_EQ(4, Solution().rob(a));
	a = {2, 1, 1, 2};
	ASSERT_EQ(4, Solution().rob(a));
	a = {2, 3, 2};
	ASSERT_EQ(4, Solution().rob(a));
}
