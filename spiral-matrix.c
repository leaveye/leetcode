/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize) {
    int top, left, bottom, right;
    int total = matrixRowSize * matrixColSize;
    int *result = (int*)malloc(total * sizeof(int));
    int count = 0;
#define pushBack(val) result[count++] = val
    top = 0, bottom = matrixRowSize - 1;
    left = 0, right = matrixColSize - 1;
    while (count < total) {
        int r = top, c = left;
        while (c < right)
            pushBack(matrix[r][c++]);
        while (r < bottom)
            pushBack(matrix[r++][c]);
        if (right == left || bottom == top) {
            pushBack(matrix[r][c]);
            break;
        }
        while (left < c)
            pushBack(matrix[r][c--]);
        while (top < r)
            pushBack(matrix[r--][c]);
        left++, top++, right--, bottom--;
    }
#undef pushBack
    return result;
}
