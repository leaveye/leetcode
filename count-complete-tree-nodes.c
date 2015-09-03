/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

// 112ms. not quite well
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

// 108ms. slightly better
int countNodesC(struct TreeNode *root, int leftDepth, int rightDepth) {
    struct TreeNode *node;
    if (root == NULL)
        return 0;
    if (leftDepth < 0)
        for (node = root, leftDepth = 0; node != NULL; node = node->left)
            ++leftDepth;
    if (rightDepth < 0)
        for (node = root, rightDepth = 0; node != NULL; node = node->right)
            ++rightDepth;
    if (leftDepth == rightDepth)
        return (1L << leftDepth) - 1;
    return 1 + countNodesC(root->left, leftDepth - 1, -1) + countNodesC(root->right, -1, rightDepth - 1);
}
int countNodes(struct TreeNode* root) {
    return countNodesC(root, -1, -1);
}

// 128ms. rewrited but worse
void getBidepth(struct TreeNode *root, int *leftDepth, int *rightDepth) {
    struct TreeNode *node;
    int *depth;
    if (*(depth = leftDepth) < 0)
        for (node = root, *depth = 0; node != NULL; ++*depth)
            node = node->left;
    if (*(depth = rightDepth) < 0)
        for (node = root, *depth = 0; node != NULL; ++*depth)
            node = node->right;
}
int countNodes(struct TreeNode* root) {
    int sum = 0;
    if (root != NULL) {
        int lDepth = -1, rDepth = -1;
        getBidepth(root, &lDepth, &rDepth);
        sum += (1 << rDepth) - 1;
        while (lDepth != rDepth) {
            int lrDepth = -1, rlDepth = -1;
            --lDepth, --rDepth;
            getBidepth(root->left, &lDepth, &lrDepth);
            getBidepth(root->right, &rlDepth, &rDepth);
            if (lDepth == lrDepth) {
                sum += 1 << (lDepth - 1);
                root = root->right, lDepth = rlDepth;
            } else if (rDepth == rlDepth) {
                root = root->left, rDepth = lrDepth;
            }
        }
    }
    return sum;
}
