static int cmpint(const void *p1, const void *p2) {
    const int *x = (const int *)p1;
    const int *y = (const int *)p2;
    return *x - *y;
}

static int _popCount[] = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
#define popCount(v) (\
    _popCount[(v) & 0xF] + _popCount[((v) >> 004) & 0xF] +\
    _popCount[((v) >> 010) & 0xF] + _popCount[((v) >> 014) & 0xF] +\
    _popCount[((v) >> 020) & 0xF] + _popCount[((v) >> 024) & 0xF] +\
    _popCount[((v) >> 030) & 0xF] + _popCount[((v) >> 034) & 0xF])

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsets(int* nums, int numsSize, int** columnSizes, int* returnSize) {
    unsigned int caseIndex, index, mask;
    int **result = (int**)malloc((1UL << numsSize) * sizeof(int*));
    *columnSizes = (int*)malloc((1UL << numsSize) * sizeof(int));
    qsort(nums, numsSize, sizeof(*nums), cmpint);
    for (caseIndex = *returnSize = 0; (caseIndex >> numsSize) == 0; ++caseIndex) {
        int caseSize = popCount(caseIndex), caseLength = 0;
        int *caseArray = (int*)malloc(caseSize * sizeof(int));
        for (index = 0, mask = caseIndex; mask; ++index, mask >>= 1)
            if (mask & 1)
                caseArray[caseLength++] = nums[index];
        (*columnSizes)[caseIndex] = caseSize;
        result[caseIndex] = caseArray;
        ++*returnSize;
    }
    return result;
}
