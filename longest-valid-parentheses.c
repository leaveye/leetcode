int longestValidParentheses(char* s) {
    int length = strlen(s);
    int *stack = (int*)malloc(2 * length * sizeof(int));
    int stackLen = 0, maxLen = 0;
    int i, *validLen = stack + length;
    for (i = 0; i < length; ++i) {
        validLen[i] = 0;
        switch (s[i]) {
            default:
                break;
            case '(':
                stack[stackLen++] = i;
                break;
            case ')':
                if (stackLen > 0) {
                    validLen[i] = i + 1 - stack[--stackLen];
                    if (i >= validLen[i])
                        validLen[i] += validLen[i - validLen[i]];
                    if (maxLen < validLen[i])
                        maxLen = validLen[i];
                }
                break;
        }
    }
    free(stack);
    return maxLen;
}
