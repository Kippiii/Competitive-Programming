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
        
        set<int> vals;
        int best_l = n-1;
        int best_val = -1;
        for (int i = n-1; i >= 0; i--) {
            vals.insert(a[i]);
            int val = (n-1) - i - ((int) vals.size());
            if (val > best_val) {
                best_l = i;
                best_val = val;
            }
        }

        printf("%d %d\n", best_l+1, n);
    }
}