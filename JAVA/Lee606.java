package JAVA;

class TreeNode {
    int val;
    TreeNode left;
    TreeNode right;
    TreeNode() {}
    TreeNode(int val) { this.val = val; }
    TreeNode(int val, TreeNode left, TreeNode right) {
        this.val = val;
        this.left = left;
        this.right = right;
    }
}

public class Lee606 {
    void traverse(TreeNode root, StringBuilder result) {
        if (root == null) {
            return;
        }
        result.append(root.val);
        if (root.left == null && root.right == null) {
            return;
        }
        result.append('(');
        traverse(root.left, result);
        result.append(")(");
        traverse(root.right, result);
        result.append(')');
        if (result.substring(result.length() - 2, result.length()).equals("()")) {
            result.delete(result.length() - 2, result.length());
        }
    }

    public String tree2str(TreeNode root) {
        StringBuilder result = new StringBuilder();
        traverse(root, result);
        return result.toString();
    }
}
