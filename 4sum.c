int compare(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return x - y;
}
void appendResult(int ***result, int *resultSize, int a, int b, int c, int d) {
    int index = (*resultSize)++, i = 0;
    *result = (int**)realloc(*result, *resultSize * sizeof(int*));
    (*result)[index] = (int*)malloc(4 * sizeof(int));
    (*result)[index][i++] = a;
    (*result)[index][i++] = b;
    (*result)[index][i++] = c;
    (*result)[index][i++] = d;
}
/**
 * Return an array of arrays of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** fourSum(int* nums, int numsSize, int target, int* returnSize) {
    int **results = NULL, i, j, k;
    *returnSize = 0;
    if (numsSize < 4 || (numsSize == 4 && nums[0] + nums[1] + nums[2] + nums[3] != target))
        return NULL;
    qsort(nums, numsSize, sizeof(int), compare);
    for (i = 0; i < numsSize - 3; ++i) {
        for (j = i + 1; j < numsSize - 2; ++j) {
            for (k = j + 1; k < numsSize - 1; ++k) {
                int a = nums[i], b = nums[j], c = nums[k], d = target - a - b - c;
                int occured = 0, index = *returnSize;
                while (!occured && index-- > 0 && results[index][0] == a)
                    occured = results[index][1] == b && results[index][2] == c;
                if (occured)
                    continue;
                if (bsearch(&d, nums + k + 1, numsSize - (k + 1), sizeof(int), compare) == NULL)
                    continue;
                appendResult(&results, returnSize, a, b, c, d);
            }
        }
    }
    return results;
}
