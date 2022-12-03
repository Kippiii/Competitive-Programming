#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int a[n];
        for (int i = 0; i < n; i++)
            scanf("%d", a+i);

        set<int> s(a, a+n);
        if ((int) s.size() == 1) {
            printf("%d\n", n/2);
            continue;
        }
        
        sort(a, a+n);
        long long ans = 1;
        for (int i = 0; i < n-1; i++) {
            if (a[i] == a[i+1])
                continue;
            long long tmp = ((long long) (i+1))*(n-i-1);
            ans = max(ans, tmp);
        }

        printf("%lld\n", ans);
    }
}