#include <bits/stdc++.h>

using namespace std;

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        int n;
        scanf("%d", &n);

        int arr[n*n];
        for (int i = 0; i < (n*n)/2; i++) {
            arr[2*i] = i+1;
            arr[2*i+1] = n*n - i;
        }
        if (n % 2 == 1)
            arr[n*n-1] = n*n/2 + 1;

        int matrix[n][n];
        pair<int, int> index(0, 0);
        bool forward = true;
        for (int i = 0; i < n*n; i++) {
            matrix[index.first][index.second] = arr[i];
            if (forward) {
                if (index.second == n-1) {
                    index.first++;
                    forward = false;
                } else {
                    index.second++;
                }
            } else {
                if (index.second == 0) {
                    index.first++;
                    forward = true;
                } else {
                    index.second--;
                }
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++)
                printf("%d ", matrix[i][j]);
            printf("\n");
        }
    }
}