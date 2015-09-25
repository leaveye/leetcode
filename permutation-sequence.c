char* getPermutation(int n, int k) {
    if (n < 0 || n >= '\128' - '1')
        n = 0;
    char *result = (char*)malloc((n + 1) * sizeof(char));
    int i, j;
    for (i = 1, --k; i <= n; k /= i++)
        result[n - i] = '1' + k % i;
    for (i = n - 2; i >= 0; --i)
        for (j = i + 1; j < n; ++j)
            if (result[j] >= result[i])
                result[j]++;
    result[n] = '\0';
    return result;
}
