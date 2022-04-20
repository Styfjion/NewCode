//
// Created by yangf on 2022/3/19.
//
#include <string>

using namespace std;

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

    void traverse(TreeNode* node, string& result) {
        if (node == nullptr) {
            return;
        }
        result += to_string(node->val);
        if (node->left == nullptr && node->right == nullptr) {
            return;
        }
        result += '(';
        traverse(node->left, result);
        result += ")(";
        traverse(node->right, result);
        result += ')';
        if (result.substr(result.length() - 2, 2) == "()") {
            result.erase(result.length() - 2);
        }
    }

    string tree2str(TreeNode* root) {
        string result;
        traverse(root, result);
        return result;
    }
};