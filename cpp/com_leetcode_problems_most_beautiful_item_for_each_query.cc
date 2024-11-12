#include <gtest/gtest.h>

#include <algorithm>
#include <numeric>
#include <vector>

namespace {
class Solution {
  public:
  std::vector<int> maximumBeauty(std::vector<std::vector<int>>& items,
                                 std::vector<int>& queries) {
    const size_t N = items.size();
    std::vector<int> ans(queries.size(), 0);

    std::sort(items.begin(), items.end());

    std::vector<int> max_beauty(N, 0);
    std::vector<int> prices(N, 0);
    max_beauty[0] = items[0][1];
    prices[0] = items[0][0];
    for (size_t i = 1; i < N; ++i) {
      max_beauty[i] = std::max(max_beauty[i - 1], items[i][1]);
      prices[i] = items[i][0];
    }

    std::vector<size_t> queries_order(queries.size());
    std::iota(queries_order.begin(), queries_order.end(), 0);
    std::sort(queries_order.begin(), queries_order.end(),
              [&queries](const size_t a, const size_t b) {
                return queries[a] < queries[b];
              });

    size_t l = 0;
    for (const size_t queries_idx : queries_order) {
      size_t r = prices.size();
      while (l < r) {
        const size_t mid = l + (r - l) / 2;
        if (prices[mid] > queries[queries_idx]) {
          r = mid;
        } else {
          ++l;
        }
      }
      ans[queries_idx] = (r - 1) >= N ? 0 : max_beauty[r - 1];
    }
    return ans;
  }
};

struct TV {
  std::vector<std::vector<int>> items;
  std::vector<int> queries;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().maximumBeauty(tv.items, tv.queries);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{{1, 2}, {3, 2}, {2, 4}, {5, 6}, {3, 5}},
       {1, 2, 3, 4, 5, 6},
       {2, 4, 5, 5, 6, 6}},
    TV{{{1, 2}, {1, 2}, {1, 3}, {1, 4}}, {1}, {4}},
    TV{{{10, 1000}}, {5}, {0}},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
