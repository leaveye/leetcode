int uniquePaths(int m, int n) {
    // C(m+n-2, m-1)
    int s, k, r, i, j;
    --m, --n;
    s = m + n;
    k = m > n ? n : m;
    r = 1;
    for (i = 1, j = s; i <= k; ++i, --j) {
        if (r % i == 0)
            r = r / i * j;
        else if (j % i == 0)
            r = j / i * r;
        else
            r *= j, r /= i;
    }
    return r;
}
