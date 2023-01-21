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

        sort(a, a+n);

        int ans = a[0] == 0 ? 0 : 1;
        int index = 0;
        while (index < n && a[index] == 0)
            index++;
        while (index < n) {
            if (index > 0 && a[index-1]+1 <= index && a[index] > index)
                ans++;
            index++;
        }
        ans++;

        printf("%d\n", ans);
    }
}