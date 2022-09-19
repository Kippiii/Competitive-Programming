#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>

int main() {
    int t;
    scanf("%d", &t);
    for (int case_num = 1; case_num <= t; case_num++) {
        int n, q;
        scanf("%d%d", &n, &q);
        vi adj[n];
        for (int i = 0; i < n-1; i++) {
            int v1, v2;
            scanf("%d%d", &v1, &v2);
            adj[v1-1].push_back(v2-1);
            adj[v2-1].push_back(v1-1);
        }
        int burner;
        for (int i = 0; i < q; i++)
            scanf("%d", &burner);
        
        int levels[n];
        for (int i = 0; i < n; i++)
            levels[i] = -1;
        levels[0] = 0;
        queue<int> qe;
        qe.push(0);
        while (!qe.empty()) {
            int cur = qe.front();
            qe.pop();
            for (int i : adj[cur]) {
                if (levels[i] == -1) {
                    levels[i] = levels[cur] + 1;
                    qe.push(i);
                }
            }
        }

        int per_level[n];
        for (int i = 0; i < n; i++)
            per_level[i] = 0;
        for (int i = 0; i < n; i++)
            per_level[levels[i]]++;
        
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (per_level[i] <= q) {
                ans += per_level[i];
                q -= per_level[i];
            } else {
                break;
            }
        }

        printf("Case #%d: %d\n", case_num, ans);
    }
}