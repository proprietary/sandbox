#include <bits/stdc++.h>

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
private:
	std::vector<std::string> all_paths;
public:
	void paths(TreeNode* node, std::string path) {
		if (node->left == nullptr && node->right == nullptr) {
			path.append("->");
			path.append(std::to_string(node->val));
			all_paths.emplace_back(path);
		}
		auto new_path = path;
		new_path.append("->");
		new_path.append(std::to_string(node->val));
		if (node->left != nullptr) {
			paths(node->left, new_path);
		}
		if (node->right != nullptr) {
			paths(node->right, new_path);
		}
	}
	std::vector<std::string> binaryTreePaths(TreeNode* root) {
		if (root == nullptr) {
			return {};
		}
		if (root->left == nullptr && root->right == nullptr) {
			return {std::to_string(root->val)};
		}
		std::string path = std::to_string(root->val);
		if (root->left != nullptr) {
			paths(root->left, path);
		}
		if (root->right != nullptr) {
			paths(root->right, path);
		}
		return all_paths;
	}

	// auto binaryTreePaths(TreeNode* root) -> std::vector<std::string> {
	// 	if (root == nullptr) {
	// 		return {};
	// 	}
	// 	if (root->left == nullptr && root->right == nullptr) {
	// 		return {std::to_string(root->val)};
	// 	}
	// 	std::vector<std::string> paths;
	// 	std::deque<TreeNode*> frontier;
	// 	std::deque<TreeNode*> ancestors;
	// 	std::unordered_set<TreeNode*> visited;
	// 	frontier.push_back(root);
	// 	while (!frontier.empty()) {
	// 		auto* node = frontier.back();
	// 		frontier.pop_back();
	// 		if (visited.find(node) == visited.end()) {
	// 			// search children next
	// 			visited.insert(node);
	// 			if (node->right != nullptr) {
	// 				frontier.push_back(node->right);
	// 			}
	// 			if (node->left != nullptr) {
	// 				frontier.push_back(node->left);
	// 			}
	// 			// use this node
	// 			ancestors.push_back(node);
	// 			if (node->left == nullptr && node->right == nullptr) {
	// 				std::ostringstream s;
	// 				auto a = ancestors.begin();
	// 				if (a != ancestors.end()) {
	// 					s << std::to_string((*a)->val);
	// 				}
	// 				std::advance(a, 1);
	// 				for (; a != ancestors.end(); ++a) {
	// 					s << "->" << std::to_string((*a)->val);
	// 				}
	// 				paths.emplace_back(s.str());
	// 				TreeNode* b = ancestors.back();
	// 				while (!ancestors.empty() && visited.find(b) != visited.end()) {
	// 					ancestors.pop_back();
	// 					b = ancestors.back();
	// 				}
	// 			}
	// 		}
	// 	}
	// 	return paths;
	// }
};
