/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void pathSumInner(struct TreeNode* root, int sum, int** path, int* pathLen, int***outArray, int** columnSizes, int* returnSize) {
    *path = (int*)realloc(*path, ++(*pathLen) * sizeof(int));
    (*path)[*pathLen - 1] = root->val;
    sum -= root->val;
    if (root->left != NULL) pathSumInner(root->left, sum, path, pathLen, outArray, columnSizes, returnSize);
    if (root->right != NULL) pathSumInner(root->right, sum, path, pathLen, outArray, columnSizes, returnSize);
    if (root->left == NULL && root->right == NULL && sum == 0) {
        int off = (*returnSize)++;
        int *column = (int*)malloc(*pathLen * sizeof(int));
        memcpy(column, *path, *pathLen * sizeof(int));
        *columnSizes = (int*)realloc(*columnSizes, *returnSize * sizeof(int));
        (*columnSizes)[off] = *pathLen;
        *outArray = (int**)realloc(*outArray, *returnSize * sizeof(int*));
        (*outArray)[off] = column;
    }
    *path = (int*)realloc(*path, --(*pathLen) * sizeof(int));
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** pathSum(struct TreeNode* root, int sum, int** columnSizes, int* returnSize) {
    int **outArray = NULL, *path = *columnSizes = NULL, pathLen = *returnSize = 0;
    if (root == NULL)
        return NULL;
    pathSumInner(root, sum, &path, &pathLen, &outArray, columnSizes, returnSize);
    return outArray;
}
