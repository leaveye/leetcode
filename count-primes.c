// 48ms, beats 86.60% c coders

// isPrime[index(x)]
// x[] = 5,7, 11,13, 17,19, 23,25, 29,31, 35,37, ...
// index[] = 0,1...

// indexed: n % 6 == 1 or 5
static inline int indexed(int n) {
    n %= 6; n &= ~4; return n == 1;
}
static inline int toIndex(n) {
    n -= 5; n /= 2; return n - n / 3;
}
static inline int fromIndex(i) {
    i += i >> 1; i <<= 1; return i + 5;
}

int countPrimes(int n) {
    if (n < 6) {
        int total[] = {0,0,0,1,2,2,3};
        return total[n];
    } else {
        int m = --n;
        while (!indexed(m))
            --m;
        int rLength = toIndex(m) + 1;
        int *isPrime = (int*)malloc(sizeof(int) * rLength);
        int total = 2; // count [2, 3]
        int i, j, x, y;
        for (i = 0; i < rLength; ++i)
            isPrime[i] = 1;
        for (x = fromIndex(i = 0); (y = x * x) <= n; x = fromIndex(++i))
            if (isPrime[i])
                for (total++, j = 0; y <= n; ++j, y += x)
                    if (indexed(y))
                        isPrime[toIndex(y)] = 0;
        while (i < rLength)
            if (isPrime[i++])
                total++;
        free(isPrime);
        return total;
    }
}
