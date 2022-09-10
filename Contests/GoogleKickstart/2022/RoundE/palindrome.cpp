#include <bits/stdc++.h>

using namespace std;

char s[100005];

bool is_palindrome(int low, int high) {
    if (high <= low)
        return true;
    if (s[low] != s[high])
        return false;
    return is_palindrome(low + 1, high - 1);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int case_num = 1; case_num <= t; case_num++) {
        int n;
        scanf("%d", &n);
        scanf("%s", s);
        for (int i = 1; i <= n; i++) {
            if (n % i)
                continue;
            if (is_palindrome(0, i - 1) && is_palindrome(i, n-1)) {
                s[i] = 0;
                printf("Case #%d: %s\n", case_num, s);
                break;
            }
        }
    }
}