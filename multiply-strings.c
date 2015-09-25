char *reverse(char *s, int l) {
    char *pl = s, *pr = s + l - 1;
    while (pl < pr) {
        char t = *pl;
        *pl = *pr;
        *pr = t;
        ++pl, --pr;
    }
    return s;
}

char* multiply(char* num1, char* num2) {
    char *num3;
    int len1, len2, len3, len3init;
    int i, j;
    len1 = strlen(num1);
    reverse(num1, len1);
    len2 = strlen(num2);
    reverse(num2, len2);
    len3init = len1 + len2 + 4;
    num3 = (char*)calloc(len3init + 1, sizeof(char));
    len3 = 1;
    for (i = 0; i < len1; ++i) {
        int b = num1[i] - '0', c = 0;
        for (j = 0; j < len2; ++j) {
            int a = num2[j] - '0';
            c += num3[i + j];
            c += a * b;
            num3[i + j] = c % 10;
            c /= 10;
        }
        while (c) {
            num3[i + j] = c % 10;
            c /= 10;
            ++j;
        }
        if (len3 < i + j) {
            len3 = i + j;
        }
    }
    while (len3 > 1 && num3[len3 - 1] == 0)
        --len3;
    for (i = 0; i < len3; ++i)
        num3[i] += '0';
    reverse(num3, len3);
    num3[len3] = '\0';
    return num3;
}
