#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int k, n;
        scanf("%d%d", &k, &n);

        int ans[k];
        ans[0] = 1;
        for (int i = 1; i < k; i++) {
            ans[i] = ans[i-1] + i;
        }
        
        for (int i = 0; i < k; i++) {
            if (ans[k - i - 1] > n - i)
                ans[k - i - 1] = n - i;
            else
                break;
        }

        for (int i = 0; i < k; i++)
            printf("%d ", ans[i]);
        printf("\n");
    }
}