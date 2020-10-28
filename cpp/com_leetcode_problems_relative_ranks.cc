// Given scores of N athletes, find their relative ranks and the
// people with the top three highest scores, who will be awarded
// medals: "Gold Medal", "Silver Medal" and "Bronze Medal".

// Example 1:
// Input: [5, 4, 3, 2, 1]
// Output: ["Gold Medal", "Silver Medal", "Bronze Medal", "4", "5"]
// Explanation: The first three athletes got the top three highest scores, so
// they got "Gold Medal", "Silver Medal" and "Bronze Medal". For the left two
// athletes, you just need to output their relative ranks according to their
// scores. Note: N is a positive integer and won't exceed 10,000. All the scores
// of athletes are guaranteed to be unique.

#include <gmock/gmock-matchers.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

static std::string const GOLD_MEDAL{"Gold Medal"};
static std::string const SILVER_MEDAL{"Silver Medal"};
static std::string const BRONZE_MEDAL{"Bronze Medal"};

struct Rank {
	int index;
	int score;
	int rank;
};

class Solution {
    public:
	std::vector<std::string> findRelativeRanks(std::vector<int>& nums) {
		auto const N = nums.size();
		// Create Rank objects in two steps:
		std::vector<Rank> ranks{N};
		// (1) Track the original index of the score in the nums array
		for (int idx = 0; idx < N; ++idx) {
			ranks[idx].index = idx;
			ranks[idx].score = nums[idx];
		}
		// Sort Rank objects by score
		std::sort(ranks.begin(), ranks.end(),
			  [](auto const& a, auto const& b) -> bool {
				  return b.score < a.score;
			  });
		// (2) Add the rank
		// Its rank is its index after sorting by score
		for (int idx = 0; idx < N; ++idx) {
			ranks[idx].rank = idx;
		}
		// Reconstruct in the order of the original
		std::vector<std::string> out{N};
		for (auto&& rank : ranks) {
			switch (rank.rank) {
				case 0:
					out[rank.index] = GOLD_MEDAL;
					break;
				case 1:
					out[rank.index] = SILVER_MEDAL;
					break;
				case 2:
					out[rank.index] = BRONZE_MEDAL;
					break;
				default:
					// the rankings for this problem are
					// counted from 1
					out[rank.index] =
					    std::to_string(rank.rank + 1);
			}
		}
		return out;
	}
};

TEST(T, T) {
	Solution s;
	std::vector<int> input = {10, 3, 8, 9, 4};
	auto res = s.findRelativeRanks(input);
	for (auto x : res) {
		std::cout << x << ',';
	}
	std::cout << std::endl;
	ASSERT_THAT(res, testing::ElementsAre("Gold Medal", "5", "Bronze Medal",
					      "Silver Medal", "4"));
}
