#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <limits>
#include <queue>
#include <vector>

namespace {
class Solution {
  static constexpr size_t kCities = 500;
  using Graph = std::array<std::vector<int>, kCities + 1>;

  public:
  std::vector<int> shortestDistanceAfterQueries(
      int n, std::vector<std::vector<int>>& queries) {
    Graph graph{};
    for (size_t city = 0; city < kCities - 1; ++city) {
      graph[city].push_back(city + 1);
    }
    auto shortest_path = [&]() -> int {
      constexpr int from = 0;
      const int to = n - 1;
      std::array<int, kCities + 1> distances{};
      std::ranges::fill(distances, std::numeric_limits<int>::max());
      distances[0] = 0;
      std::queue<int> frontier;
      frontier.push(from);
      while (!frontier.empty()) {
        const int current = frontier.front();
        frontier.pop();
        for (const int neighbor : graph[current]) {
          if (distances[neighbor] == std::numeric_limits<int>::max()) {
            distances[neighbor] = distances[current] + 1;
            frontier.push(neighbor);
          }
        }
      }
      return distances[to];
    };
    std::vector<int> ans(queries.size(), 0);
    for (size_t i = 0; i < queries.size(); ++i) {
      const int u = queries[i][0], v = queries[i][1];
      graph[u].push_back(v);
      ans[i] = shortest_path();
    }
    return ans;
  }
};

struct TV {
  int n;
  std::vector<std::vector<int>> queries;
  std::vector<int> expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().shortestDistanceAfterQueries(tv.n, tv.queries);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{5, {{2, 4}, {0, 2}, {0, 4}}, {3, 2, 1}},
    TV{4, {{0, 3}, {0, 2}}, {1, 1}},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
