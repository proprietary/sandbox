#include <bits/stdc++.h>

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right)
	    : val(x), left(left), right(right) {}
};

class Solution {
    public:
	auto pathSum(TreeNode* root, int sum) -> std::vector<std::vector<int>> {
		if (root == nullptr) {
			return {};
		}
		std::vector<std::vector<int>> paths;
		std::deque<TreeNode*> frontier;
		std::deque<TreeNode*> ancestors;
		std::unordered_set<TreeNode*> visited;
		frontier.push_back(root);
		while (!frontier.empty()) {
			auto* node = frontier.back();
			frontier.pop_back();
			if (visited.find(node) == visited.end()) {
				// mark as visited
				visited.insert(node);
				// use this node
				if (node->left == nullptr &&
				    node->right == nullptr) {
					std::vector<int> path;
					path.resize(ancestors.size() + 1);
					std::transform(std::begin(ancestors),
						       std::end(ancestors),
						       std::begin(path)++,
						       [](auto const* a) {
							       return a->val;
						       });
					path.back() = node->val;
					if (sum == std::accumulate(
						       std::begin(path),
						       std::end(path), 0)) {
						paths.push_back(path);
					}
					while (!ancestors.empty()) {
						auto* b = ancestors.back();
						if ((b->left != nullptr &&
						     visited.find(b->left) ==
							 visited.end()) ||
						    (b->right != nullptr &&
						     visited.find(b->right) ==
							 visited.end())) {
							break;
						}
						ancestors.pop_back();
					}
				} else {
					ancestors.push_back(node);
				}
				// search children next
				if (node->right != nullptr) {
					frontier.push_back(node->right);
				}
				if (node->left != nullptr) {
					frontier.push_back(node->left);
				}
			}
		}
		return paths;
	}
};
