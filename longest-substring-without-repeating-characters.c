int lengthOfLongestSubstring(char* s) {
    if (s == NULL || *s == '\0') {
        return 0;
    } else {
        char *cur, *base = s - 1;
        int occur[256] = {};
        int len = 0, max_len = 0;
        for (cur = s; *cur != '\0'; ++cur) {
            char *prev = base + occur[*cur];
            if (prev == base || prev < cur - len) {
                len++;
            } else {
                if (max_len < len)
                    max_len = len;
                len = cur - prev;
            }
        }
        if (max_len < len)
            max_len = len;
        return max_len;
    }
}
