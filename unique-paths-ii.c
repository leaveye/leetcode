#define newObject(type) ((type*)calloc(1, sizeof(type)))
#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define renewObject(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize, int obstacleGridColSize) {
    int *rowState = newArray(int, obstacleGridColSize);
    int result, x, y;
    for (y = 0; y < obstacleGridRowSize; ++y) {
        for (x = 0; x < obstacleGridColSize; ++x) {
            if (obstacleGrid[y][x])
                rowState[x] = 0;
            else if (y == 0)
                rowState[x] = x > 0 ? rowState[x - 1] : 1;
            else
                rowState[x] += x > 0 ? rowState[x - 1] : 0;
        }
    }
    result = rowState[obstacleGridColSize - 1];
    free(rowState);
    return result;
}
