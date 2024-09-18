#include <bits/stdc++.h>

class Solution {
  struct Pair {
    int num;
    size_t index;
  };

  public:
  bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
    // Transform input array into (number, index) tuples
    std::vector<Pair> m;
    m.reserve(nums.size());
    for (size_t i = 0; i < nums.size(); ++i) {
      m.emplace_back(Pair{nums[i], i});
    }
    // Partition the array by number so that only equal numbers'
    // indices are compared
    std::sort(
        std::begin(m), std::end(m),
        [](auto const& a, auto const& b) -> bool { return a.num < b.num; });
    // Compare the difference between adjacent indices in each
    // partition
    for (auto it = std::begin(m); it != std::end(m);) {
      auto partition_it = it;
      auto prev = partition_it;
      ++partition_it;
      for (; partition_it != std::end(m) && partition_it->num == it->num;
           ++partition_it) {
        size_t diff = std::labs(prev->index - partition_it->index);
        if (diff <= static_cast<size_t>(k)) {
          return true;
        }
        prev = partition_it;
      }
      it = partition_it;
    }
    return false;
  }
};

#include <gtest/gtest.h>

TEST(Test, Test1) {
  std::vector<int> nums = {1, 2, 3, 1, 2, 3};
  ASSERT_EQ(false, Solution().containsNearbyDuplicate(nums, 2));
}

TEST(Test, Test2) {
  std::vector<int> nums = {1, 0, 1, 1};
  ASSERT_EQ(true, Solution().containsNearbyDuplicate(nums, 1));
}
