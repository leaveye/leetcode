#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define resizeArray(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

int maxSegLength(char *s) {
    if (!isdigit(*s))
        return 0;
    switch (*s - '0') {
        case 0:
            return 1;
        case 1:
            if (!isdigit(s[1])) return 1;
            if (!isdigit(s[2])) return 2;
            return 3;
        case 2:
            if (!isdigit(s[1])) return 1;
            if (!isdigit(s[2])) return 2;
            if (s[1] > '5') return 2;
            if (s[1] < '5') return 3;
            if (s[2] <= '5') return 3;
            return 2;
        default:
            if (!isdigit(s[1])) return 1;
            return 2;
    }
}

void splitByDot(char ***out, int *outSize, char *input, int inputSize,
                char *pBase, char *pCurr, int leftSeg) {
    int maxLen = maxSegLength(input);
    if (maxLen == 0) {
    } else if (leftSeg == 1) {
        if (maxLen == inputSize) {
            strncpy(pCurr, input, maxLen);
            // pushResult
            *out = resizeArray(*out, char*, 1 + *outSize);
            (*out)[*outSize] = strdup(pBase);
            ++*outSize;
        }
    } else {
        int l;
        for (l = 1; l <= maxLen; ++l) {
            strncpy(pCurr, input, l), pCurr[l] = '.';
            splitByDot(out, outSize, input + l, inputSize - l, pBase, pCurr + l + 1, leftSeg - 1);
        }
    }
}

/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** restoreIpAddresses(char* s, int* returnSize) {
    char **result = NULL;
    *returnSize = 0;
    if (s != NULL && *s != '\0') {
        char *cache;
        int length = 0;
        while (isdigit(s[length]))
            ++length;
        cache = newArray(char, length + 4);
        splitByDot(&result, returnSize, s, length, cache, cache, 4);
        free(cache);
    }
    return result;
}
