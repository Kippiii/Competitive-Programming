#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);
        int k[n];
        vector<int> p[n];
        vector<int> all_b;
        for (int i = 0; i < n; i++) {
            scanf("%d", k+i);
            for (int j = 0; j < k[i]; j++) {
                int val;
                scanf("%d", &val);
                p[i].push_back(val);
                all_b.push_back(val);
            }
        }

        int bit_counts[200005];
        for (int b : all_b)
            bit_counts[b] = 0;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < k[i]; j++)
                bit_counts[p[i][j]] += 1;

        bool ans = false;
        for (int i = 0; i < n; i++) {
            bool has_unique = false;
            for (int j = 0; j < k[i]; j++)
                if (bit_counts[p[i][j]] == 1)
                    has_unique = true;
            if (!has_unique)
                ans = true;
        }
        
        printf("%s\n", ans ? "Yes" : "No");
    }
}