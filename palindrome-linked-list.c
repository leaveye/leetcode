/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool isPalindrome(struct ListNode* head) {
    struct ListNode *left, *right, *pl, *pr, *p;
    bool result;
    if (head == NULL || head->next == NULL)
        return true;
    right = head->next, pr = right->next;
    left = head, pl = left->next, left->next = NULL;
    while (pr) {
        pr = pr->next;
        right = right->next;
        if (!pr)
            break;
        pr = pr->next;
        p = pl, pl = pl->next, p->next = left, left = p;
    }
    result = true;
    while (left) {
        if (result)
            result = left->val == right->val;
        p = left;
        left = left->next, right = right->next;
        p->next = pl, pl = p;
    }
    return result;
}

bool isPalindrome_bruteforce(struct ListNode* head) {
    struct ListNode* tail = NULL;
    while (head != tail && head->next != tail) {
        struct ListNode* last = head;
        while (last->next != tail)
            last = last->next;
        if (head->val != last->val)
            return false;
        head = head->next, tail = last;
    }
    return true;
}
