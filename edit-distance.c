// D(0,0) = 0
// D(0,k) = D(k,0) = k
// D(i,j) = min(D(i-1,j)+1,
//              D(i,j-1)+1,
//              D(i,j)+(Ai==Bj?0:1))
int minDistance(char* word1, char* word2) {
    int len1 = strlen(word1), len2 = strlen(word2);
    if (!(len1 && len2))
        return len1 + len2;
    int *cache = (int*)malloc((len1 + 1) * sizeof(int));
    int result, i;
    for (i = 0; i <= len1; ++i)
        cache[i] = i;
    while (*word2 != '\0') {
        for (result = cache[0] + 1, i = 1; i <= len1; ++i) {
            int curr = cache[i - 1] + !(*word2 == word1[i - 1]);
            if (curr > result + 1)
                curr = result + 1;
            if (curr > cache[i] + 1)
                curr = cache[i] + 1;
            cache[i - 1] = result, result = curr;
        }
        cache[len1] = result, ++word2;
    }
    result = cache[len1];
    free(cache);
    return result;
}
