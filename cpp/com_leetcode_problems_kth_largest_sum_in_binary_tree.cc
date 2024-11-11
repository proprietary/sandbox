#include <fmt/format.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <deque>
#include <functional>
#include <vector>

#include "gtest/gtest.h"
#include "tree_node.hpp"

namespace {
class Solution {
  public:
  long long kthLargestLevelSum(TreeNode* root, int k) {
    std::vector<long long> sums;
    std::deque<TreeNode*> q;
    q.push_back(root);
    while (!q.empty()) {
      long long level_sum = 0LL;
      for (TreeNode* it : q) {
        level_sum += it->val;
      }

      const auto size = q.size();
      for (int i = 0; i < size; i++) {
        TreeNode* node = q.front();
        q.pop_front();
        if (node->left) q.push_back(node->left);
        if (node->right) q.push_back(node->right);
      }

      sums.push_back(level_sum);
    }
    std::sort(sums.begin(), sums.end(), std::greater<>{});
    return sums.size() >= k ? sums[k - 1] : -1;
  }
};

struct TV {
  std::string_view input;
  int k;
  long long expected;
};

class ParamTest : public ::testing::TestWithParam<TV> {};

TEST_P(ParamTest, Examples) {
  auto tv = GetParam();

  Arena arena{2 * 1024 * 1024};
  TreeNode* parsed = TreeNode::parse(arena, tv.input);
  auto actual = Solution().kthLargestLevelSum(parsed, tv.k);
  EXPECT_EQ(tv.expected, actual);
}

static auto TEST_CASES = {TV{"[5,8,9,2,1,3,7,4,6]", 2, 13},
                          TV{"[1,2,null,3]", 1, 3}};

INSTANTIATE_TEST_SUITE_P(Suite, ParamTest, ::testing::ValuesIn(TEST_CASES));
}  // namespace
