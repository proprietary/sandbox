from typing import List


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Solution:
    def __init__(self):
        self.paths = []

    def dfs(self, node: TreeNode, predecessors: List[int] = []):
        if node is None:
            return None
        elif node.left is None and node.right is None:
            path = predecessors + [node.val]
            self.paths.append(path)
        if node.left is not None:
            self.dfs(node.left, predecessors + [node.val])
        if node.right is not None:
            self.dfs(node.right, predecessors + [node.val])

    def sumNumbers(self, root: TreeNode) -> int:
        if root is None:
            return 0
        self.dfs(root)
        total = 0
        for path in self.paths:
            total += int(''.join(map(str, path)))
        return total


if __name__ == '__main__':
    t = TreeNode(1, left=TreeNode(2), right=TreeNode(3))
    assert Solution().sumNumbers(t) == 25
    t = TreeNode(4, left=TreeNode(9, left=TreeNode(5), right=TreeNode(1)), right=TreeNode(0))
    assert Solution().sumNumbers(t) == 1026
