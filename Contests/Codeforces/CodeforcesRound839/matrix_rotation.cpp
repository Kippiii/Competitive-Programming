#include <bits/stdc++.h>

using namespace std;

bool can_be_beautiful(int m[2][2]) {
    if (m[0][0] < m[0][1] && m[0][0] < m[1][0] && m[1][1] > m[0][1] && m[1][1] > m[1][0])
        return true;
    if (m[0][0] > m[0][1] && m[0][0] > m[1][0] && m[1][1] < m[0][1] && m[1][1] < m[1][0])
        return true;
    if (m[0][1] < m[0][0] && m[0][1] < m[1][1] && m[1][0] > m[0][0] && m[1][0] > m[1][1])
        return true;
    if (m[0][1] > m[0][0] && m[0][1] > m[1][1] && m[1][0] < m[0][0] && m[1][0] < m[1][1])
        return true;
    return false;
}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int m[2][2];
        scanf("%d%d%d%d", &m[0][0], &m[0][1], &m[1][0], &m[1][1]);
        if (can_be_beautiful(m))
            printf("YES\n");
        else
            printf("NO\n");
    }
}