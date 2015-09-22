// learn from: http://articles.leetcode.com/2011/11/longest-palindromic-substring-part-ii.html
// implement the algorithm and reduce T[] to T().

#define T(index) ((index)<0?'^':!((index)&1)?'#':s[(index)>>1])

char* longestPalindrome(char* s) {
    if (s == NULL)
        return NULL;
    int *P, maxP = 0;
    int C = 0, R = 0;
    int length = strlen(s) * 2, i;
    P = (int*)malloc(length * sizeof(int));
    P[0] = 0;
    for (i = 1; i < length; ++i) {
        int i_mirror = C * 2 - i; // C - (i - C)
        if (R <= i)
            P[i] = 0;
        else if (R - i > P[i_mirror])
            P[i] = P[i_mirror];
        else
            P[i] = R - i;
        while (T(i + 1 + P[i]) == T(i - 1 - P[i]))
            P[i]++;
        if (R < i + P[i])
            R = i + P[i], C = i;
        if (P[maxP] <= P[i])
            maxP = i;
    }
    s += (maxP - P[maxP]) / 2;
    maxP = P[maxP];
    free(P);
    return strndup(s, maxP);
}
