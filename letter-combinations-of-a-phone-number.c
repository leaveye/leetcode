static char * const validDigits = "023456789";
static int const digitWeights[] = {1,3,3,3,3,3,4,3,4};
static char * const digitBases = " adgjmptw";
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** letterCombinations(char* digits, int* returnSize) {
    int digitsLen = strlen(digits);
    int *weights = (int*)malloc(digitsLen * sizeof(int));
    char *bases = (char*)malloc(digitsLen * sizeof(char));
    char **outArray = NULL;
    int i, j, cases = 1, outStrLen = 0;
    for (i = 0; i < digitsLen; ++i) {
        char *occur = strchr(validDigits, digits[i]);
        if (occur == NULL)
            continue;
        bases[outStrLen] = digitBases[occur - validDigits];
        cases *= weights[outStrLen] = digitWeights[occur - validDigits];
        outStrLen++;
    }
    if (outStrLen == 0) {
        free(weights);
        free(bases);
        *returnSize = 0;
        return NULL;
    }
    outArray = (char**)malloc(cases * sizeof(char*));
    for (i = 0; i < cases; ++i) {
        int n = i;
        char *out = (char*)malloc((outStrLen + 1) * sizeof(char));
        out[outStrLen] = '\0';
        for (j = outStrLen - 1; j >= 0; --j) {
            out[j] = bases[j] + n % weights[j];
            n /= weights[j];
        }
        outArray[i] = out;
    }
    free(weights);
    free(bases);
    *returnSize = cases;
    return outArray;
}
