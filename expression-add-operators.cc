class Solution {
public:
    void cpsCall(vector<string> &out, const char *num, int target, string expr, long long last, int factor) {
        long long result = last * factor;
        if (*num == '\0') {
            if (result == target)
                out.push_back(expr);
        } else {
            char c = *num++; int cur = c - '0';
            if (last != 0)
                cpsCall(out, num, target, expr + c, last * 10 + cur, factor);
            cpsCall(out, num, target, expr + '*' + c, cur, result);
            target -= result;
            cpsCall(out, num, target, expr + '+' + c, cur, 1);
            cpsCall(out, num, target, expr + '-' + c, cur, -1);
        }
    }

    vector<string> addOperators(string num, int target) {
        vector<string> ret;
        if (num.length() > 0)
            cpsCall(ret, num.c_str() + 1, target, num.substr(0, 1), num[0] - '0', 1);
        return ret;
    }
};
