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
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) {
			return root;
		}
		invertTree(root->right);
		invertTree(root->left);
		std::swap(root->right, root->left);
		return root;
	}
};
