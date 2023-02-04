#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>

int main() {
    int n, s, k;
    scanf("%d%d%d", &n, &s, &k);
    s*=2;
    k*=2;
    int x[n];
    for (int i = 0; i < n; i++)
        scanf("%d", x+i);
    for (int i = 0; i < n; i++)
        x[i]*=2;
    
    sort(x, x+n);
    ii plats[n];
    for (int i = 0; i < n; i++)
        plats[i] = ii(x[i], s);
    
    bool impossible = false;
    for (int i = 0; i < n-1; i++) {
        if ((plats[i+1].first - plats[i].first) < (plats[i+1].second + plats[i].second)/2) {
            impossible = true;
            break;
        }
    }

    if (impossible) {
        printf("-1\n");
    } else {
        for (int i = 0; i < n-1; i++) {
            int free_space = (plats[i+1].first - plats[i].first) - (plats[i+1].second + plats[i].second)/2;
            if (i > 0)
                free_space = min(free_space, (plats[i].first - plats[i-1].first) - (plats[i].second + plats[i-1].second)/2);
            plats[i].second = min(k, 2*free_space + plats[i].second);
        }
        int free_space = n > 1 ? (plats[n-1].first - plats[n-2].first) - (plats[n-1].second + plats[n-2].second)/2 : 999999999;
        plats[n-1].second = min(k, 2*free_space + plats[n-1].second);

        int ans = 0;
        for (int i = 0; i < n; i++)
            ans += plats[i].second;
        printf("%d\n", ans/2);
    }
}