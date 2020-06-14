#!/usr/bin/env python3
""""
Leetcode 103. Binary Tree Zigzag Level Order Traversal

Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).

For example:
Given binary tree [3,9,20,null,null,15,7],

    3
   / \
  9  20
    /  \
   15   7

return its zigzag level order traversal as:

[
  [3],
  [20,9],
  [15,7]
]
"""

from collections import deque
from typing import List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right
class Solution:
    def zigzagLevelOrder(self, root: TreeNode) -> List[List[int]]:
        if root is None or root.val is None:
            return []
        get_vals = lambda x: x.val if x is not None else None
        out = []
        a = deque([root])
        while a:
            new_list = list(map(get_vals, a))
            if len(out) % 2 > 0:
                new_list = new_list[::-1]  # reverse
            out.append(new_list)
            for _ in range(len(a)):
                node = a.popleft()
                if node is not None and node.left is not None:
                    a.append(node.left)
                if node is not None and node.right is not None:
                    a.append(node.right)
        return out


if __name__ == '__main__':
    expected = [[3], [20, 9], [15, 7]]
    s = Solution()
    res = s.zigzagLevelOrder(
        TreeNode(val=3,
                 left=TreeNode(9),
                 right=TreeNode(20, left=TreeNode(15), right=TreeNode(7))))
    print(res)
    print(s.zigzagLevelOrder(TreeNode(None)))
