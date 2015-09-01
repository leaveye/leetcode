int nthUglyNumber(int n) {
    if (n <= 1)
        return 1;
    else {
        int *o = (int*)malloc(n * sizeof(int));
        int f[3] = {2,3,5}, i[3] = {}, m[3];
        int j, k, r;
        o[0] = 1;
        for (k = 1; k < n; ++k) {
            o[k] = m[0] = o[i[0]] * f[0];
            for (j = 1; j < 3; ++j)
                if ((m[j] = o[i[j]] * f[j]) < o[k])
                    o[k] = m[j];
            for (j = 0; j < 3; ++j)
                if (o[k] == m[j])
                    i[j]++;
        }
        r = o[n - 1];
        free(o);
        return r;
    }
}
