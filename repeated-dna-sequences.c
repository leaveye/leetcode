// nice solution from https://leetcode.com/discuss/58927/share-my-c-solution-easy-to-understand
#define CODE(a) ('A' == (a) ? 0 : 'C' == (a) ? 1 : 'G' == (a) ? 2 : 3)
#define CHAR(a) (0 == (a) ? 'A' : 1 == (a) ? 'C' : 2 == (a) ? 'G' : 'T')
int comp(const void* p1, const void* p2) {
    int a = *((int*) p1);
    int b = *((int*) p2);
    return a == b ? 0 : a > b ? 1 : -1;
}
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** findRepeatedDnaSequences(char* s, int* returnSize) {
    int len = s && *s ? (int) strlen(s) - 9 : 0, *encode;
    int i, j, code = 0, mask = (1 << 20) - 1;
    char** result;
    if (1 >= len) {
        *returnSize = 0;
        return NULL;
    }
    encode = malloc(sizeof(int) * len);
    for (i = 0, j = 0; s[i]; ++i) {
        code = ((code << 2) | CODE(s[i])) & mask;
        9 <= i ? (encode[j++] = code) : 0;
    }
    result = malloc(sizeof(char*) * len);
    qsort(encode, len, sizeof(int), comp);
    code = 0;
    for (i = 1; i < len; ++i) {
        if (encode[i] == encode[i - 1] && 
            (i == len - 1 || encode[i] != encode[i + 1])) {
            result[code] = malloc(11);
            for (j = 0; j < 10; ++j) {
                result[code][j] = CHAR((encode[i] >> ((9 - j) << 1)) & 3);
            }
            result[code][j] = '\0';
            code++;
        }
    }
    free(encode);
    *returnSize = code;
    return result;
}
