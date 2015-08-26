#define newObject(type) ((type*)calloc(1, sizeof(type)))
#define newArray(type, size) ((type*)calloc(size, sizeof(type)))
#define renewObject(ptr, type, size) ((type*)realloc(ptr, (size) * sizeof(type)))

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 * };
 */
int merge(struct Interval *output, struct Interval *array1, int size1, struct Interval *array2, int size2) {
    struct Interval *end1 = array1 + size1, *end2 = array2 + size2;
    struct Interval *dst = output, *src1 = array1, *src2 = array2;
    if (size1 == 0) {
        *dst++ = *src2++;
    } else {
        struct Interval *cur;
        if (src1->start < src2->start)
            *dst = *src1++;
        else
            *dst = *src2++;
        while (src1 < end1 || src2 < end2) {
            if (src1 >= end1)
                cur = src2++;
            else if (src2 >= end2 || src1->start < src2->start)
                cur = src1++;
            else
                cur = src2++;
            if (dst->end < cur->start)
                *++dst = *cur;
            else if (dst->end < cur->end)
                dst->end = cur->end;
        }
        ++dst;
    }
    return dst - output;
}
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
struct Interval* insert(struct Interval* intervals, int intervalsSize, struct Interval newInterval, int* returnSize) {
    struct Interval *results = newArray(struct Interval, intervalsSize + 1);
    *returnSize = merge(results, intervals, intervalsSize, &newInterval, 1);
    return results;
}
