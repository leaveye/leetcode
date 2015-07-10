void recursiveCalc(char ***outArray, int *outSize, int *state, int n, int index, int cases) {
    if (index == n) {
        //appendOutput(outArray, outSize, state, n);
        int i;
        char *p = (char*) malloc(n * 2 + 1);
        char *pfinal = p + n * 2;
        *outArray = (char**) realloc(*outArray, ++*outSize * sizeof(char*));
        (*outArray)[*outSize - 1] = p;
        p[n * 2] = '\0';
        for (index = 0; index < n; ++index) {
            for (i = 0; i < state[index]; ++i)
                *p++ = ')';
            *p++ = '(';
        }
        while (p < pfinal)
            *p++ = ')';
    } else {
        int i;
        for (i = 0; i < cases; ++i) {
            state[index] = i;
            recursiveCalc(outArray, outSize, state, n, index + 1, cases + 1 - i);
        }
    }
}
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** generateParenthesis(int n, int* returnSize) {
    // "((()))", "(()())", "(())()", "()(())", "()()()"
    // 000, 001, 002, 010, 011
    // placing bracket 0, possible 1:
    //   placed position 0, possible 2.
    // placing bracket 1, possible 2:
    //   placed position 0, possible 3.
    //   placed position 1, possible 2.
    // placing bracket 2, possible 2:
    //   placed position 0, possible 3.
    //   placed position 1, possible 2.
    // placing bracket k, possible t:
    //   placed position i, possible t+1-i.
    int *bracketPositions = (int*) malloc(n * sizeof(int));
    char **result = NULL;
    *returnSize = 0;
    recursiveCalc(&result, returnSize, bracketPositions, n, 0, 1);
    return result;
}
