static int cmpint(const void *p1, const void *p2) {
    const int *x = (const int *)p1;
    const int *y = (const int *)p2;
    return *x - *y;
}

#define newObject(type) ((type*)calloc(1, sizeof(type)))
#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define renewObject(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** subsetsWithDup(int* nums, int numsSize, int** columnSizes, int* returnSize) {
    int **results;
    int *ns, *ws, *cs;
    int len = 0, caseIndex, count;
    int s, i, j;
    qsort(nums, numsSize, sizeof(*nums), cmpint);
    ns = newArray(int, numsSize * 3);
    ws = ns + numsSize;
    cs = ws + numsSize;
    for (i = 0; i < numsSize; ++i) {
        if (len == 0 || nums[i] != ns[len - 1])
            ns[len] = nums[i], ws[len] = 2, ++len;
        else
            ws[len - 1]++;
    }
    for (*returnSize = 1, i = 0; i < len; ++i)
        *returnSize *= ws[i];
    results = newArray(int*, *returnSize);
    *columnSizes = newArray(int, *returnSize);
    for (caseIndex = 0; caseIndex < *returnSize; ++caseIndex) {
        results[caseIndex] = NULL, (*columnSizes)[caseIndex] = 0;
        for (s = caseIndex, count = i = 0; i < len && s; s /= ws[i++]) {
            count = s % ws[i];
            results[caseIndex] = renewObject(results[caseIndex], int, count + (*columnSizes)[caseIndex]);
            for (j = 0; j < count; ++j)
                results[caseIndex][(*columnSizes)[caseIndex]++] = ns[i];
        }
    }
    return results;
}
