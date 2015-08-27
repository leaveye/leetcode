static int cmpint(const void *p1, const void *p2) {
    const int *x = (const int *)p1;
    const int *y = (const int *)p2;
    return *x - *y;
}

int partition(int *xs, int size, int pivotIndex) {
    int pivot = xs[pivotIndex], i;
    if (pivotIndex)
        xs[pivotIndex] = xs[0], pivotIndex = 0;
    for (i = 1; i < size; ++i)
        if (xs[i] < pivot) {
            xs[pivotIndex] = xs[i];
            xs[i] = xs[++pivotIndex];
        }
    xs[pivotIndex] = pivot;
    return pivotIndex;
}

int findKthLargest(int* nums, int numsSize, int k) {
    while (numsSize > 5) {
        int step = (numsSize - 1 + 5) / 5;
        int slotCount = (numsSize - 1 + step) / step;
        int pivotIndex = slotCount / 2 * step;
        int rank;
        //qsort(nums, slotCount, sizeof(*nums) * step, cmpint);
        pivotIndex = partition(nums, numsSize, pivotIndex);
        rank = numsSize - pivotIndex;
        if (rank == k)
            return nums[pivotIndex];
        else if (rank < k)
            numsSize = pivotIndex, k -= rank;
            //return findKthLargest(nums, pivotIndex, k - rank);
        else
            ++pivotIndex, nums += pivotIndex, numsSize -= pivotIndex;
            //return findKthLargest(nums + pivotIndex + 1, numsSize - pivotIndex - 1, k);
    }
    qsort(nums, numsSize, sizeof(*nums), cmpint);
    return nums[numsSize - k];
}
