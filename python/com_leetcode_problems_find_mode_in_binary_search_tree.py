# Definition for a binary tree node.
# class TreeNode:
#     def __init__(self, val=0, left=None, right=None):
#         self.val = val
#         self.left = left
#         self.right = right

from typing import List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def __init__(self):
        self.stats = {}

    def getStats(self, root: TreeNode):
        if root is None:
            return
        self.stats[root.val] = self.stats.get(root.val, 0) + 1
        if root.left is not None:
            self.getStats(root.left)
        if root.right is not None:
            self.getStats(root.right)

    def findMode(self, root: TreeNode) -> List[int]:
        self.getStats(root)
        print(self.stats)
        if len(self.stats) == 0:
            return []
        ks = self.stats.keys()
        mode = max(ks, key=self.stats.__getitem__)
        mode_freq = self.stats[mode]
        modes = [k for k, v in self.stats.items() if v == mode_freq]
        return modes
