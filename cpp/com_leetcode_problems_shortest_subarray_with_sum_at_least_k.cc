#include <gtest/gtest.h>

#include <algorithm>
#include <functional>
#include <limits>
#include <utility>
#include <vector>

namespace {
class Solution {
  public:
  int shortestSubarray(std::vector<int>& nums, int k) {
    const size_t n = nums.size();
    size_t best = std::numeric_limits<size_t>::max();
    std::vector<std::pair<int64_t, size_t>> heap;
    heap.reserve(n);
    int64_t sum = 0;
    for (size_t i = 0; i < n; ++i) {
      sum += nums[i];
      if (sum >= k) {
        best = std::min(best, i + 1);
      }
      while (!heap.empty() && sum - heap[0].first >= k) {
        std::pop_heap(heap.begin(), heap.end(), std::greater<>{});
        const auto& [prefix, j] = heap.back();
        best = std::min(best, i - j);
        heap.pop_back();
      }
      heap.emplace_back(sum, i);
      std::push_heap(heap.begin(), heap.end(), std::greater<>{});
    }
    return best == std::numeric_limits<size_t>::max() ? -1 : best;
  }
};

struct TV {
  std::vector<int> nums;
  int k;
  int expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().shortestSubarray(tv.nums, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{1}, 1, 1},
    TV{{1, 2}, 4, -1},
    TV{{2, -1, 2}, 3, 3},
    TV{{17, 85, 93, -45, -21}, 150, 2},
    TV{{84, -37, 32, 40, 95}, 167, 3},
    TV{{-28, 81, -20, 28, -29}, 89, 3},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
