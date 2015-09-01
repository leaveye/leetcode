// full version: http://ideone.com/HDyFSa

#define foreachPos(i, j) for (i = j = 0; i < 9; j == 8 ? j = 0, ++i : ++j)
#define foreachPosIf(i, j, cond) foreachPos(i, j) if (cond)

#define MASK_UNDETERMINED 01000
#define MASK_UNCONFLICTED 02000
#define MASK_ALLVALUES    0777
#define MASK_VALUE(v)     (1 << ((v) - 1))
#define INIT_UNKNOWN      (MASK_UNCONFLICTED | MASK_UNDETERMINED | MASK_ALLVALUES)
#define INIT_VALUE(v)     (MASK_UNCONFLICTED | MASK_VALUE(v))

#define CELL(x, y) memo[x][y]

#define UNIQUE(x, y) (!(((CELL(x,y) & -CELL(x,y)) ^ CELL(x,y)) & 0777))
#define HAS(x, y, mask) (CELL(x,y) & (mask))
#define UNCONFLICTED(x, y) HAS(x,y,MASK_UNCONFLICTED)
#define UNDETERMINED(x, y) HAS(x,y,MASK_UNDETERMINED)
#define erase(x, y, mask) (updated = true, CELL(x,y) &= ~(unsigned)(mask)); if (MASK_ALLVALUES & CELL(x,y)) ; else return false
#define eraseIf(x, y, mask, cond) if (cond) do { erase(x, y, mask); } while(0)

char valueOf(short mask) {
    char value = '0';
    while (mask)
        value++, mask >>= 1;
    return value;
}

bool guessValues(short memo[][9], int *px, int *py, short *pmask) {
    int minPossibles = 10, i, j;
    *px = *py = -1, *pmask = 0;
    foreachPosIf (i, j, UNDETERMINED(i,j)) {
        int mask = CELL(i,j) & MASK_ALLVALUES;
        int possibles = 0;
        while (mask)
            possibles += mask & 1, mask >>= 1;
        if (possibles < minPossibles)
            *px = i, *py = j, minPossibles = possibles;
    }
    i = *px, j = *py;
    if (minPossibles != 10)
        *pmask = CELL(i,j) & -CELL(i,j) & MASK_ALLVALUES;
    return *pmask != 0;
}

bool solveSudokuC(int unknown, short memo[][9], char board[][9]) {
    bool updated = true;
    int memoSave[9][9];
    char boardSave[9][9];
    int i, j, k;
    short mask;
    while (updated && unknown > 0) {
        updated = false;
        // erase confliction
        foreachPosIf (i, j, UNCONFLICTED(i,j) && !UNDETERMINED(i,j)) {
            int ii = i - i % 3, jj = j - j % 3;
            erase(i, j, MASK_UNCONFLICTED);
            for (mask = CELL(i,j) & MASK_ALLVALUES, k = 0; k < 9; ++k) {
                int ik = ii + k / 3, jk = jj + k % 3;
                eraseIf(i, k, mask, k != j && HAS(i, k, mask));
                eraseIf(k, j, mask, k != i && HAS(k, j, mask));
                eraseIf(ik, jk, mask, (ik != i || jk != j) && HAS(ik, jk, mask));
            }
        }
        // determin unique
        foreachPosIf (i, j, UNDETERMINED(i,j) && UNIQUE(i,j)) {
            erase(i, j, MASK_UNDETERMINED);
            board[i][j] = valueOf(CELL(i,j) & MASK_ALLVALUES);
            unknown--;
        }
        // no need to guess
        if (updated) continue;
        if (guessValues(memo, &i, &j, &mask)) {
            int completed;
            // backup memo>>memoSave, board>>boardSave
            memcpy(memoSave, memo, sizeof(memoSave));
            memcpy(boardSave, board, sizeof(boardSave));
            // guess one number
            erase(i, j, (CELL(i,j) ^ mask) & MASK_ALLVALUES);
            completed = solveSudokuC(unknown, memo, board);
            if (completed) return true;
            // revert memo<<memoSave, board<<boardSave
            memcpy(memo, memoSave, sizeof(memoSave));
            memcpy(board, boardSave, sizeof(boardSave));
            erase(i, j, mask);
        }
    }
    return unknown == 0;
}

void solveSudoku(char** board, int boardRowSize, int boardColSize) {
    short memo[9][9];
    char board2[9][9];
    int i, j, unknown = 0;
    foreachPos (i, j) {
        char c = board2[i][j] = board[i][j];
        if (c == '.')
            CELL(i, j) = INIT_UNKNOWN, unknown++;
        else
            CELL(i, j) = INIT_VALUE(c - '0');
    }
    solveSudokuC(unknown, memo, board2);
    foreachPos (i, j)
        board[i][j] = board2[i][j];
}
