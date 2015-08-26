/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

#define newObject(type) ((type*)calloc(1, sizeof(type)))
#define renewObject(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

struct TreeNode *newNode(int val) {
    struct TreeNode *p = newObject(struct TreeNode);
    p->val = val;
    return p;
}

void freeTree(struct TreeNode *root) {
    if (!root)
        return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

struct TreeNode *duplicateTree(struct TreeNode *root) {
    struct TreeNode *newRoot = NULL;
    if (root) {
        newRoot = newNode(root->val);
        newRoot->left = duplicateTree(root->left);
        newRoot->right = duplicateTree(root->right);
    }
    return newRoot;
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct TreeNode** generateTrees(int n, int* returnSize) {
    *returnSize = 0;
    if (n < 1) {
        struct TreeNode**results = newObject(struct TreeNode*);
        results[(*returnSize)++] = NULL;
        return results;
    } else {
        int prevIndex, rightChild, r;
        int prevSize;
        struct TreeNode**prevs = generateTrees(n - 1, &prevSize);
        struct TreeNode**results = NULL;
        for (prevIndex = 0; prevIndex < prevSize; ++prevIndex) {
            struct TreeNode*rootPrev = prevs[prevIndex];
            struct TreeNode*childRoot = rootPrev;
            rightChild = 0;
            while (1) {
                struct TreeNode *root = duplicateTree(rootPrev);
                struct TreeNode *node = newNode(n);
                struct TreeNode **insertPos = &root;
                for (r = 0; r < rightChild; ++r)
                    insertPos = &(*insertPos)->right;
                node->left = *insertPos;
                *insertPos = node;
                results = renewObject(results, struct TreeNode*, *returnSize + 1);
                results[(*returnSize)++] = root;
                if (childRoot == NULL)
                    break;
                childRoot = childRoot->right;
                ++rightChild;
            }
            freeTree(rootPrev);
        }
        free(prevs);
        return results;
    }
}
