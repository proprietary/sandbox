#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <stack>
#include <unordered_map>
#include <vector>

namespace {
class Solution {
  using Graph = std::unordered_map<int, std::deque<int>>;

  public:
  std::vector<std::vector<int>> validArrangement(
      std::vector<std::vector<int>>& pairs) {
    const int n = pairs.size();
    Graph graph;
    std::unordered_map<int, int> in_degree;
    std::unordered_map<int, int> out_degree;
    for (const auto& pair : pairs) {
      graph[pair[0]].push_back(pair[1]);
      out_degree[pair[0]]++;
      in_degree[pair[1]]++;
    }
    int cur = pairs[0][0];
    for (const auto& pair : pairs) {
      if (out_degree[pair[0]] == in_degree[pair[0]] + 1) {
        cur = pair[0];
        break;
      }
    }
    std::vector<int> cycle;
    cycle.reserve(n / 2);
    std::stack<int> tour;
    tour.push(cur);
    while (!tour.empty()) {
      const int node = tour.top();
      if (!graph[node].empty()) {
        const int next_node = graph[node].front();
        graph[node].pop_front();
        tour.push(next_node);
      } else {
        cycle.push_back(node);
        tour.pop();
      }
    }
    std::reverse(cycle.begin(), cycle.end());
    std::vector<std::vector<int>> ans;
    ans.reserve(n);
    for (auto it = cycle.begin() + 1; it != cycle.end(); it++) {
      ans.emplace_back(std::vector<int>{*std::prev(it), *it});
    }
    return ans;
  }
};

struct TV {
  std::vector<std::vector<int>> pairs;
  std::vector<std::vector<int>> expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  auto actual = Solution().validArrangement(tv.pairs);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {
    TV{{{5, 1}, {4, 5}, {11, 9}, {9, 4}}, {{11, 9}, {9, 4}, {4, 5}, {5, 1}}},
    TV{{{1, 3}, {3, 2}, {2, 1}}, {{1, 3}, {3, 2}, {2, 1}}},
    TV{{{1, 2}, {1, 3}, {2, 1}}, {{1, 2}, {2, 1}, {1, 3}}},
};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));

}  // namespace

int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
