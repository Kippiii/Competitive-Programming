#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int cnt[n];
        for (int i = 0; i < n; i++)
            scanf("%d", cnt + i);
        
        int ans = distance(cnt, max_element(cnt, cnt + n)) + 1;
        printf("%d\n", ans);
    }
}