#include <bits/stdc++.h>

using namespace std;

int sr[100005];

int bin_search(int x, int low, int high) {
    if (low == high) {
        if (sr[low] <= x)
            return sr[low];
        return -1;
    }
    int mid = ceil((high + low) / 2.0);
    if (sr[mid] == x)
        return x;
    if (sr[mid] < x)
        return bin_search(x, mid, high);
    return bin_search(x, low, mid-1);
}

int main() {
    int t;
    scanf("%d", &t);
    for (int case_num = 1; case_num <= t; case_num++) {
        int n;
        scanf("%d", &n);
        int r[n];
        for (int i = 0; i < n; i++)
            scanf("%d", r + i);
        
        int instances[1000005];
        for (int i = 0; i < 1000005; i++)
            instances[i] = 0;

        for (int i = 0; i < n; i++) {
            sr[i] = r[i];
            instances[r[i]]++;
        }
        sort(sr, sr+n);
        
        printf("Case #%d:", case_num);
        for (int i = 0; i < n; i++) {
            int sol = bin_search(2*r[i], 0, n-1);
            if (sol == r[i] && instances[r[i]] < 2)
                sol = bin_search(r[i]-1, 0, n-1);
            printf(" %d", sol);
        }
        printf("\n");
    }
}