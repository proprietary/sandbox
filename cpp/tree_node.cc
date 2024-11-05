#include "tree_node.hpp"

#include <cctype>
#include <queue>
#include <sstream>
#include <string>

namespace {
auto trim_left(std::string_view src) -> std::string_view {
  if (src.empty()) return src;
  size_t begin = 0;
  while (begin < src.length() &&
         std::isspace(static_cast<unsigned char>(src[begin]))) {
    begin++;
  }
  return src.substr(begin);
}

auto trim_right(std::string_view src) -> std::string_view {
  if (src.empty()) return src;
  size_t end = src.length() - 1;
  while (end != static_cast<size_t>(-1) &&
         std::isspace(static_cast<unsigned char>(src[end]))) {
    end--;
  }
  return src.substr(0, end + 1);
}

auto trim(std::string_view src) -> std::string_view {
  return trim_right(trim_left(src));
}
}  // namespace

auto TreeNode::parse(Arena& arena, std::string_view input) -> TreeNode* {
  std::pmr::polymorphic_allocator<TreeNode> alloc(&arena);

  input = trim(input);
  if (input.front() != '[' || input.back() != ']') {
    throw std::runtime_error{"Binary tree must be delimited by []"};
  }
  auto trimmed_input = input.substr(1, input.size() - 2);

  // Split the string by commas
  std::vector<std::optional<int>> values;
  std::stringstream ss(std::string{trimmed_input});
  std::string item;
  while (std::getline(ss, item, ',')) {
    // Trim whitespace from each item
    size_t start = item.find_first_not_of(' ');
    size_t end = item.find_last_not_of(' ');
    std::string token = item.substr(start, end - start + 1);

    if (token == "null") {
      values.push_back(std::nullopt);
    } else {
      values.push_back(std::stoi(token));
    }
  }

  if (values.empty() || !values[0]) {
    return nullptr;
  }

  TreeNode* root = alloc.allocate(1);
  alloc.construct(root, values[0].value());
  std::queue<TreeNode*> node_queue;
  node_queue.push(root);

  int index = 1;
  while (!node_queue.empty() && index < values.size()) {
    auto node = node_queue.front();
    node_queue.pop();

    // Left child
    if (index < values.size() && values[index]) {
      node->left = alloc.allocate(1);
      alloc.construct(node->left, values[index].value());
      node_queue.push(node->left);
    }
    index++;

    // Right child
    if (index < values.size() && values[index]) {
      node->right = alloc.allocate(1);
      alloc.construct(node->right, values[index].value());
      node_queue.push(node->right);
    }
    index++;
  }

  return root;
}
