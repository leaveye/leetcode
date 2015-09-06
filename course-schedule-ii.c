/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
// ref: https://en.wikipedia.org/wiki/Topological_sorting#Algorithms
int* findOrder(int numCourses, int** prerequisites, int prerequisitesRowSize, int prerequisitesColSize, int* returnSize) {
    int *L, *S, *I, lenL = 0, lenS = 0, i;
    L = (int*)calloc(3 * numCourses, sizeof(int));
    S = L + numCourses;
    I = S + numCourses;
    for (i = 0; i < prerequisitesRowSize; ++i)
        I[prerequisites[i][0]]++;
    for (i = 0; i < numCourses; ++i)
        if (I[i] == 0)
            S[lenS++] = i;
    while (lenS > 0) {
        int n = L[lenL++] = S[--lenS];
        int **pe = prerequisites + prerequisitesRowSize;
        while (--pe >= prerequisites) {
            int *e = *pe;
            if (e[1] != n)
                continue;
            --prerequisitesRowSize;
            *pe = prerequisites[prerequisitesRowSize];
            prerequisites[prerequisitesRowSize] = e;
            I[e[0]]--;
            if (I[e[0]] == 0)
                S[lenS++] = e[0];
        }
    }
    if (prerequisitesRowSize > 0) {
        free(L);
        L = NULL;
    } else
        *returnSize = numCourses;
    return L;
}
