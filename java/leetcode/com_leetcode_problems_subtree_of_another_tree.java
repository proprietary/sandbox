class TreeNode {
    public int val;
    public TreeNode left;
    public TreeNode right;
    public TreeNode() {}
    public TreeNode(int val) { this.val = val; }
    public TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

public class Solution {
	public boolean isSubtree(TreeNode s, TreeNode t) {
		if (s == null || t == null) {
			return false;
		}
		return treeDeepEqual(s, t) || isSubtree(s.left, t) || isSubtree(s.right, t);
	}

	boolean treeDeepEqual(final TreeNode a, final TreeNode b) {
		if (a == null && b == null) {
			return true;
		}
		if (a == null && b != null) {
			return false;
		}
		if (a != null && b == null) {
			return false;
		}
		return a.val == b.val && treeDeepEqual(a.left, b.left) && treeDeepEqual(a.right, b.right);
	}
}
