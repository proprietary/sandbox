#include <bits/stdc++.h>

#include <algorithm>

class Solution {
  public:
  // void moveZeroes(std::vector<int>& nums) {
  // 	int n_zeros = 0;
  // 	for (int n : nums) {
  // 		if (n == 0) {
  // 			n_zeros += 1;
  // 		}
  // 	}
  // 	for (size_t i = 0; i < nums.size() - n_zeros; ) {
  // 		if (nums[i] == 0) {
  // 			for (size_t k = i; k < nums.size() - 1; ++k) {
  // 				std::swap(nums[k], nums[k+1]);
  // 			}
  // 		}
  // 		if (nums[i] != 0) {
  // 			i += 1;
  // 		}
  // 	}
  // }

  // void moveZeroes(std::vector<int>& nums) {
  // 	size_t zero_idx = 0;
  // 	size_t nonzero_idx = 0;
  // 	while (true) {
  // 		while (zero_idx < nums.size() && nums[zero_idx] != 0) {
  // 			zero_idx += 1;
  // 		}
  // 		nonzero_idx = zero_idx + 1;
  // 		while (nonzero_idx < nums.size() && nums[nonzero_idx] == 0) {
  // 			nonzero_idx += 1;
  // 		}
  // 		if (zero_idx > nonzero_idx || nonzero_idx >= nums.size() ||
  // zero_idx >= nums.size()) { 			break;
  // 		}
  // 		if (zero_idx < nums.size() && nonzero_idx < nums.size()) {
  // 			std::swap(nums[zero_idx], nums[nonzero_idx]);
  // 		}
  // 	}
  // }

  // void moveZeroes(std::vector<int>& nums) {
  // 	size_t j = 0;
  // 	for (size_t i = 0; i < nums.size(); ++i) {
  // 		if (nums[i] != 0) {
  // 			nums[j++] = nums[i];
  // 		}
  // 	}
  // 	for (; j < nums.size(); ++j) {
  // 		nums[j] = 0;
  // 	}
  // }

  void moveZeroes(std::vector<int>& nums) {
    std::stable_partition(nums.begin(), nums.end(),
                          [](int n) -> bool { return n != 0; });
  }
};

#include <gtest/gtest.h>

TEST(Test, Test1) {
  std::vector<int> nums = {0, 1, 0, 3, 12};
  std::vector<int> expected = {1, 3, 12, 0, 0};
  Solution().moveZeroes(nums);
  ASSERT_TRUE(nums == expected);
}

TEST(Test, Test2) {
  std::vector<int> nums = {0, 0, 1};
  std::vector<int> expected = {1, 0, 0};
  Solution().moveZeroes(nums);
  for (auto n : nums) {
    std::cout << n << ',';
  }
  std::cout << std::endl;
  ASSERT_TRUE(nums == expected);
}

TEST(Test, Test3) {
  std::vector<int> nums = {1, 0};
  std::vector<int> expected = {1, 0};
  Solution().moveZeroes(nums);
  for (auto n : nums) {
    std::cout << n << ',';
  }
  std::cout << std::endl;
  ASSERT_TRUE(nums == expected);
}

TEST(Test, Test4) {
  std::vector<int> nums = {1, 0, 0};
  std::vector<int> expected = {1, 0, 0};
  Solution().moveZeroes(nums);
  for (auto n : nums) {
    std::cout << n << ',';
  }
  std::cout << std::endl;
  ASSERT_TRUE(nums == expected);
}

TEST(Test, Test5) {
  std::vector<int> nums = {1, 0, 1};
  std::vector<int> expected = {1, 1, 0};
  Solution().moveZeroes(nums);
  for (auto n : nums) {
    std::cout << n << ',';
  }
  std::cout << std::endl;
  ASSERT_TRUE(nums == expected);
}
