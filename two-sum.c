int *realArray = NULL;
int compare(const void *a, const void *b) {
    int ia = *(int*)a, ib = *(int*)b;
    return realArray[ia] - realArray[ib];
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target) {
    int *indices = (int*)malloc(numsSize * sizeof(int));
    int i;
    for (i = 0; i < numsSize; ++i)
        indices[i] = i;
    realArray = nums;
    qsort(indices, numsSize, sizeof(int), compare);
    for (i = 0; i < numsSize - 1; ++i) {
        int a = nums[indices[i]], b = target - a;
        int l = i + 1, r = numsSize - 1;
        while (l <= r) {
            int m = l + (r - l + 1) / 2;
            int mval = nums[indices[m]];
            if (mval == b) { l = r = m; break; }
            else if (mval < b) { l = m + 1; }
            else if (mval > b) { r = m - 1; }
        }
        if (l == r) {
            int *out = (int*)malloc(2 * sizeof(int));
            out[0] = indices[i] + 1, out[1] = indices[l] + 1;
            if (out[0] > out[1])
                { int t = out[0]; out[0] = out[1]; out[1] = t; }
            free(indices);
            return out;
        }
    }
    free(indices);
    return NULL;
}
