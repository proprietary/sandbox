#include <string_view>
#include "arena.hpp"

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  static auto parse(Arena& arena, std::string_view input) -> TreeNode*;
};
