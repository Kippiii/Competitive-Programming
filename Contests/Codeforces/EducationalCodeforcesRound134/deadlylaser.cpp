#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n, m, sx, sy, d;
        scanf("%d%d%d%d%d", &n, &m, &sx, &sy, &d);

        bool top = sy - d <= 1;
        bool bot = sy + d >= m;
        bool left = sx - d <= 1;
        bool right = sx + d >= n;

        if ((!top && !right) || (!bot && !left))
            printf("%d\n", n + m - 2);
        else
            printf("-1\n");
    }
}