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
        
        int greatest_factor = a[0];
        for (int i = 1; i < n; i++)
            greatest_factor = gcd(greatest_factor, a[i]);
        
        printf("%d\n", a[n-1]/greatest_factor);
    }
}