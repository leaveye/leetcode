/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    else {
        struct TreeNode *nodeLeft = root->left, *nodeRight = root->right;
        int depth = 1;
        while (nodeLeft != NULL && nodeRight != NULL)
            depth++, nodeLeft = nodeLeft->left, nodeRight = nodeRight->right;
        if (nodeLeft == NULL && nodeRight == NULL)
            return (1L << depth) - 1;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
}
