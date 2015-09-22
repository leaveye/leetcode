int minSubArrayLen(int s, int* nums, int numsSize) {
    int *sums, len, i;
    sums = (int*)malloc((numsSize + 1) * sizeof(int));
    for (sums[len = i = 0] = 0; i < numsSize; ++i) {
        sums[i + 1] = sums[i] + nums[i];
        if (len == 0 && sums[i + 1] >= s)
            len = i + 1;
    }
    if (len == 0)
        return 0;
    for (i = len; i <= numsSize; ++i)
        while (len > 1 && sums[i] - sums[i + 1 - len] >= s)
            --len;
    free(sums);
    return len;
}
