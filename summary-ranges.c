/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** summaryRanges(int* nums, int numsSize, int* returnSize) {
    char cache[0x20], **results;
    int l, r;
    results = (char**) malloc(numsSize * sizeof(char*));
    *returnSize = 0;
    for (l = 0; l < numsSize; l = r) {
        int max = nums[l];
        r = l + 1;
        while (r < numsSize && max + 1 == nums[r])
            ++r, ++max;
        if (nums[l] == max)
            sprintf(cache, "%d", nums[l]);
        else
            sprintf(cache, "%d->%d", nums[l], max);
        results[(*returnSize)++] = strdup(cache);
    }
    return results;
}
