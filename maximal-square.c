int maximalSquare(char** matrix, int matrixRowSize, int matrixColSize) {
    int *cache[2], row, col, maxLen = 0;
    if (matrixRowSize == 0 || matrixColSize == 0)
        return 0;
    cache[0] = (int*)malloc(2 * matrixColSize * sizeof(int));
    cache[1] = cache[0] + matrixColSize;
    for (col = 0; col < matrixColSize; ++col)
        maxLen |= cache[0][col] = matrix[0][col] != '0';
    for (row = 1; row < matrixRowSize; ++row) {
        int *currRow = cache[row & 1];
        int *lastRow = cache[~row & 1];
        currRow[0] = matrix[row][0] != '0';
        if (maxLen < currRow[0])
            maxLen = currRow[0];
        int leftMin = currRow[0] ? lastRow[0] : 0;
        for (col = 1; col < matrixColSize; ++col) {
            if (matrix[row][col] == '0')
                leftMin = currRow[col] = 0;
            else {
                int len = leftMin;
                if (len > lastRow[col - 1])
                    len = lastRow[col - 1];
                if (len >= lastRow[col])
                    len = 1 + (leftMin = lastRow[col]);
                else
                    leftMin = ++len;
                currRow[col] = len;
                if (maxLen < currRow[col])
                    maxLen = currRow[col];
            }
        }
    }
    free(cache[0]);
    return maxLen * maxLen;
}
