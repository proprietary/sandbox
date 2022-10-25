#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <assert.h>
#include <iostream>

class Solution {
public:
    void merge2(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
		int ni = 0;
		int mi = 0;
		int first_empty = m;
        for (; ni < n; ++ni) {
			// find next index in `nums1` to insert into
			while (mi < first_empty && nums2[ni] > nums1[mi]) {
				++mi;
			}
			// shift the rest of the elements to the right by one cell
			assert(first_empty < nums1.size());
			assert(nums1[first_empty] == 0);
			for (int j = first_empty; j > mi; --j) {
				nums1[j] = nums1[j - 1];
			}
			++first_empty;
			// insert element from `nums2`
			nums1[mi] = nums2[ni];
		}
    }

	void merge(std::vector<int>& nums1, int m, std::vector<int>& nums2, int n) {
		for (int i = m + n - 1, a = m - 1, b = n - 1; b >= 0; --i) {
			if (a >= 0 && nums1[a] > nums2[b]) {
				nums1[i] = nums1[a--];
			} else {
				nums1[i] = nums2[b--];
			}
		}
	}
};

TEST(Leetcode, Example1) {
	Solution s{};
	std::vector<int> nums1 = {1,2,3,0,0,0};
	std::vector<int> nums2 = {2,5,6};
	s.merge(nums1, 3, nums2, 3);
	ASSERT_THAT(nums1, ::testing::ElementsAre(1, 2, 2, 3, 5, 6));
}

TEST(Leetcode, Example2) {
	Solution s{};
	std::vector<int> nums1 = {1};
	std::vector<int> nums2 = {};
	s.merge(nums1, 1, nums2, 0);
	ASSERT_THAT(nums1, ::testing::ElementsAre(1));
}

TEST(Leetcode, Example3) {
	Solution s{};
	std::vector<int> nums1 = {0};
	std::vector<int> nums2 = {1};
	s.merge(nums1, 0, nums2, 1);
	ASSERT_THAT(nums1, ::testing::ElementsAre(1));
}
