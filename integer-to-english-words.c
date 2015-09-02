char *numberToWords(int num) {
    static const char *bases3[] = { "Hundred", "Thousand", "Million", "Billion" };
    static const char *bases2[] = { "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety" };
    static const char *nums1[20] = {
        "Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
        "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
        "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
    };
    char cacheBase[0x100] = {};
    char *cache = cacheBase, *cacheEnd = cacheBase + sizeof(cacheBase);
#define cacheAppend(str) (cache += snprintf(cache, cacheEnd - cache, " %s", str))
    int base = 1, baseIndex = 0;
    while (num / base >= 1000)
        base *= 1000, baseIndex++;
    if (num == 0)
        return strdup("Zero");
    while (num) {
        int part = num / base;
        int posSave = cache - cacheBase;
        if (part >= 100) {
            cacheAppend(nums1[part / 100]);
            cacheAppend(bases3[0]);
            part %= 100;
        }
        if (part >= 20) {
            cacheAppend(bases2[(part - 20) / 10]);
            part %= 10;
        }
        if (part >= 1) {
            cacheAppend(nums1[part]);
        }
        if (baseIndex > 0 && cache - cacheBase > posSave) {
            cacheAppend(bases3[baseIndex]);
        }
        num %= base, base /= 1000, baseIndex--;
    }
    return strdup(cacheBase + 1);
#undef cacheAppend
}
