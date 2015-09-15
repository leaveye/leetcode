// R[r][c]
// | r+1 < rows && c+1 < cols = max(1, min(R[r+1][c], R[r][c+1]) - input[r][c])
// | r+1 < rows               = max(1, R[r+1][c] - input[r][c])
// | c+1 < cols               = max(1, R[r][c+1] - input[r][c])
// | otherwise                = 1

static const int hpLBound = 1;

static inline int hpRequired(int hpAfter, int dungeon) {
    int hp = hpAfter - dungeon;
    if (hp < hpLBound)
        hp = hpLBound;
    return hp;
}

int calculateMinimumHP(int** dungeon, int dungeonRowSize, int dungeonColSize) {
    if (dungeonRowSize <= 0 || dungeonColSize <= 0 || dungeon == NULL)
        return 0;
    int result, row, col, hpAfter;
    int *hp = (int*)malloc(dungeonColSize * sizeof(int));
    row = dungeonRowSize, col = dungeonColSize, hpAfter = hpLBound;
    row--;
    while (col-- > 0)
        hpAfter = hp[col] = hpRequired(hpAfter, dungeon[row][col]);
    while (row-- > 0) {
        col = dungeonColSize;
        while (col-- > 0) {
            hpAfter = hp[col];
            if (col + 1 < dungeonColSize && hp[col + 1] < hpAfter)
                hpAfter = hp[col + 1];
            hp[col] = hpRequired(hpAfter, dungeon[row][col]);
        }
    }
    result = hp[0];
    free(hp);
    return result;
}
