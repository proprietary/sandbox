#include <gtest/gtest.h>
#include <vector>
#include <queue>
#include <unordered_set>
#include <stack>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

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
    int findBottomLeftValue(TreeNode* root) {
		std::queue<TreeNode*> q;
		q.push(root);
		while (!q.empty()) {
			root = q.front();
			q.pop();
			if (root->right != nullptr) {
				q.push(root->right);
			}
			if (root->left != nullptr) {
				q.push(root->left);
			}
		}
		return root->val;
    }
};

void BottomRow(std::stack<TreeNode*>& out, TreeNode* root) {
	std::queue<TreeNode*> q;
	std::unordered_set<TreeNode*> discovered;
	q.push(root);
	while (!q.empty()) {
		auto* v = q.front();
		q.pop();
		if (v->left == nullptr && v->right == nullptr) {
			out.push(v);
		}
		if (v->right != nullptr && discovered.find(v->right) == discovered.end()) {
			discovered.insert(v->right);
			q.push(v->right);
		}
		if (v->left != nullptr && discovered.find(v->left) == discovered.end()) {
			discovered.insert(v->left);
			q.push(v->left);
		}
	}
}

// sample tree
TreeNode b {4};
TreeNode c {2, &b, nullptr};
TreeNode a {7};
TreeNode d {5, &a, nullptr};
TreeNode e {6};
TreeNode f {3, &d, &e};
TreeNode root {1, &c, &f};

TEST(TestLeetcode, TestBottomRow) {
	std::stack<TreeNode*> bottomRow;
	BottomRow(bottomRow, &root);
	ASSERT_EQ(bottomRow.top()->val, 7);
	while (!bottomRow.empty()) {
		std::cout << bottomRow.top()->val << ' ';
		bottomRow.pop();
	}
	std::cout << std::endl;
}

TEST(TestLeetcode, TestSampleTree) {
	ASSERT_EQ(Solution{}.findBottomLeftValue(&root), 7);
}
