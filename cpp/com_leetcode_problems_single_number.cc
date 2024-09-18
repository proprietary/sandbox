/**
 * 136. Single Number
 * Given a non-empty array of integers, every element appears twice except for
 * one. Find that single one.
 *
 * Note:
 *
 * Your algorithm should have a linear runtime complexity. Could you implement
 * it without using extra memory?
 *
 * Example 1:
 *
 * Input: [2,2,1]
 * Output: 1
 *
 * Example 2:
 *
 * Input: [4,1,2,1,2]
 * Output: 4
 *
 */

#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <random>
#include <utility>
#include <vector>

class Solution {
  public:
  // First attempt:
  // Sort then find the first discrepancy while iterating with a stride of 2
  // 	int singleNumber(std::vector<int>& nums) {
  // 		if (nums.size() == 1) {
  // 			return nums[0];
  // 		}
  // 		if (nums.size() == 2) {
  // 			return nums[0];
  // 		}
  // 		std::sort(nums.begin(), nums.end());
  // 		for (int i = 1; i < nums.size() - 1; i += 2) {
  // 			if (nums[i] != nums[i-1]) {
  // 				return nums[i-1];
  // 			}
  // 		}
  // 		const auto sz = nums.size();
  // 		if (nums[sz - 1] != nums[sz - 2]) {
  // 			return nums[sz - 1];
  // 		}
  // 		return -1;
  // 	}

  // Second attempt: Much more elegant, but not much faster than above method
  // (x ^ x ^ y) = y
  int singleNumber(std::vector<int>& nums) {
    return std::accumulate(nums.begin(), nums.end(), 0, std::bit_xor{});
  }

  int singleNumber(std::vector<int>&& nums) {
    auto m = nums;
    return singleNumber(m);
  }
};

TEST(Leetcode, TestGivenExamples) {
  Solution s{};
  EXPECT_EQ(1, s.singleNumber({{2, 2, 1}}));
  EXPECT_EQ(4, s.singleNumber({{4, 1, 2, 1, 2}}));
}

TEST(Leetcode, TestRandom) {
  Solution s{};
  std::random_device rd{};
  std::mt19937 gen{rd()};
  std::uniform_int_distribution<int> smaller{1, 100};
  std::uniform_int_distribution<int> larger{0, 1'000'000};
  constexpr auto num_rounds = 1'000'000;
  for (int i = 0; i < num_rounds; ++i) {
    // construct list with 2 of every kind except one
    std::vector<int> a{};
    const auto len = smaller(gen);
    a.reserve(len * 2 + 1);
    for (int j = 0; j < len; ++j) {
      auto n = larger(gen);
      a.push_back(n);
      a.push_back(n);
    }
    // insert the wild number at a random position
    std::uniform_int_distribution<int> insertion_point{0, len};
    int wildcard = 0;
    do {
      wildcard = larger(gen);
    } while (std::find(a.begin(), a.end(), wildcard) != a.end());
    a.insert(a.begin() + insertion_point(gen), wildcard);
    // test solution
    auto res = s.singleNumber(a);
    if (res == -1) {
      std::cout << "Failed to find the single number in this array: "
                << std::endl;
      for (auto x : a) std::cout << x << ' ';
      std::cout << std::endl;
    }
    ASSERT_GE(res, 0);
    ASSERT_EQ(wildcard, s.singleNumber(a));
  }
}
