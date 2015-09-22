/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 * };
 */
int cmpInterval(const void *a, const void *b) {
    const struct Interval *x, *y;
    x = (const struct Interval *)a;
    y = (const struct Interval *)b;
    if (x->start != y->start)
        return x->start - y->start;
    return x->end - y->end;
}
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct Interval* merge(struct Interval* intervals, int intervalsSize, int* returnSize) {
    struct Interval *pi, *po, *pe;
    if (intervals == NULL || intervalsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    pi = (struct Interval*)malloc(intervalsSize * sizeof(struct Interval));
    memcpy(pi, intervals, intervalsSize * sizeof(struct Interval));
    qsort(intervals = pi, intervalsSize, sizeof(struct Interval), cmpInterval);
    pi = po = intervals, pe = intervals + intervalsSize;
    while (++pi < pe) {
        if (po->end < pi->start)
            *++po = *pi;
        else if (po->end < pi->end)
            po->end = pi->end;
    }
    *returnSize = ++po - intervals;
    return intervals;
}
