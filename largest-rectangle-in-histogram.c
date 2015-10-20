// explained: http://www.cnblogs.com/lichen782/p/leetcode_Largest_Rectangle_in_Histogram.html
int largestRectangleArea(int* height, int heightSize) {
    int *stack = (int*)malloc(heightSize * sizeof(int));
    int *stackEnd = stack + heightSize, *stackTop = stackEnd;
    int i = 0, result = 0;
    while (i <= heightSize) {
        if (stackTop == stackEnd || (i < heightSize && height[*stackTop] <= height[i])) {
            *--stackTop = i++;
        } else {
            int h = height[*stackTop++];
            int w = stackTop == stackEnd ? i : i - *stackTop - 1;
            int area = w * h;
            if (result < area)
                result = area;
        }
    }
    free(stack);
    return result;
}
