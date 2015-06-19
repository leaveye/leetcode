int compare(const void *a, const void *b) {
    int x = *(const int *)a, y = *(const int *)b;
    return x - y;
}
int threeSumClosest(int* nums, int numsSize, int target) {
    int *pe = nums + numsSize, diff, result;
    int *pa, *pb, *pl, *pc, *pr, c;
    if (numsSize < 3) return 0;
    if (numsSize == 3) return nums[0] + nums[1] + nums[2];
    qsort(nums, numsSize, sizeof(int), compare);
    result = nums[0] + nums[1] + nums[2];
    diff = result < target ? target - result : result - target;
    for (pa = nums; diff && pa < pe - 2; ++pa) {
        for (pb = pa + 1; diff && pb < pe - 1; ++pb) {
            int c = target - *pa - *pb;
            pl = pb + 1, pr = pe - 1;
            while (pr > pl) {
                if (pl + 1 >= pr) {
                    pl = pr = (c + c <= *pl + *pr) ? pl : pr;
                    break;
                }
                pc = pl + (pr - pl) / 2;
                if (*pc > c) { pr = pc; }
                else { pl = pc; }
            }
            if (*pl == c)
                return target;
            else if (c - diff < *pl && *pl < c)
                diff = c - *pl, result = target - diff;
            else if (c < *pl && *pl < c + diff)
                diff = *pl - c, result = target + diff;
        }
    }
    return result;
}
