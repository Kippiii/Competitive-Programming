#include <bits/stdc++.h>

using namespace std;

int main() {
    int n;
    scanf("%d", &n);
    int s[n];
    for (int i = 0; i < n; i++)
        scanf("%d", s+i);
    
    sort(s, s+n);
    
    long long sums[n];
    sums[0] = s[0];
    for (int i = 1; i < n; i++)
        sums[i] = sums[i-1] + s[i];
    
    bool will_kill[n];
    int attack = n-1;
    will_kill[n-1] = false;
    for (int i = n-2; i >= 0; i--) {
        long long attack_sum = sums[n-1] - sums[attack-1];
        long long defense_sum = sums[attack-1] - (i > 0 ? sums[i-1] : 0);
        if (attack_sum > defense_sum) {
            will_kill[i] = true;
        } else {
            will_kill[i] = false;
            attack = i;
        }
    }

    int first_no_kill = -1;
    for (int i = 0; i < n; i++)
        if (!will_kill[i]) {
            first_no_kill = i;
            break;
        }
    int ans = n - first_no_kill;
    printf("%d\n", ans);
}