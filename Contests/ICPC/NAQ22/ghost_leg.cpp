#include <bits/stdc++.h>

using namespace std;

int n, m;
int rungs[1005];

int get_pos(int x) {
    int cur_spot = x;
    for (int i = 0; i < m; i++) {
        if (cur_spot == rungs[i])
            cur_spot += 1;
        else if (cur_spot == rungs[i]+1)
            cur_spot -= 1;
    }
    return cur_spot;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++)
        scanf("%d", rungs + i);
    
    int ans[n+1];
    for (int i = 0; i < n; i++)
        ans[get_pos(i+1)] = i+1;

    for (int i = 1; i <= n; i++)
        printf("%d\n", ans[i]);
}