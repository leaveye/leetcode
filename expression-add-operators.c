/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define newObject(type) ((type*)calloc(1, sizeof(type)))
#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

void cpsCall(char ***out, int *outSize, char *num, int target, char *expr, int exprSize, long long last, int factor) {
    long long term = last * factor;
    if (*num == '\0') {
        if (term == target) {
            *out = resizeArray(*out, char*, *outSize + 1);
            (*out)[*outSize] = strdup(expr);
            ++*outSize;
        }
    } else {
        char c = *num++; int cur = c - '0';
        if (last != 0) {
            expr[exprSize + 1] = '\0';
            expr[exprSize] = c;
            cpsCall(out, outSize, num, target, expr, exprSize + 1, last * 10 + cur, factor);
        }
        expr[exprSize + 2] = '\0';
        expr[exprSize + 1] = c;
        expr[exprSize] = '*';
        cpsCall(out, outSize, num, target, expr, exprSize + 2, cur, term);
        target -= term;
        expr[exprSize] = '+';
        cpsCall(out, outSize, num, target, expr, exprSize + 2, cur, 1);
        expr[exprSize] = '-';
        cpsCall(out, outSize, num, target, expr, exprSize + 2, cur, -1);
    }
}

char** addOperators(char* num, int target, int* returnSize) {
    char **output = NULL;
    *returnSize = 0;
    if (num != NULL && *num != '\0') {
        char *expr = newArray(char, 2 * strlen(num));
        expr[0] = *num, expr[1] = '\0';
        cpsCall(&output, returnSize, num + 1, target, expr, 1, *num - '0', 1);
        free(expr);
    }
    return output;
}
