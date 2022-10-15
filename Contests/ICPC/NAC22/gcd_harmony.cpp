#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define MAX 10000
#define INF 20000

int n;
int v[5005];
vi adj[5005];

int min_moves[5005][MAX + 5];
void get_min_moves(int index, int parent) {
    for (int i = 2; i <= MAX; i++)
        min_moves[index][i] = i == v[index] ? 0 : i;
    for (int a : adj[index]) {
        if (a == parent)
            continue;
        get_min_moves(a, index);
        int multiples[MAX+5];
        for (int i = 0; i < MAX+5; i++)
            multiples[i] = INF;
        for (int i = 2; i <= MAX; i++)
            for (int j = i; j <= MAX; j+=i)
                multiples[i] = min(multiples[i], min_moves[a][j]);
        int to_add[MAX+5];
        for (int i = 0; i < MAX+5; i++)
            to_add[i] = INF;
        for (int i = 2; i <= MAX; i++)
            for (int j = i; j <= MAX; j+=i)
                to_add[j] = min(to_add[j], multiples[i]);
        for (int i = 2; i <= MAX; i++)
            min_moves[index][i] += to_add[i];
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
        scanf("%d", v + i);
    for (int i = 0; i < n-1; i++) {
        int a, b;
        scanf("%d%d", &a, &b);
        adj[a-1].push_back(b-1);
        adj[b-1].push_back(a-1);
    }

    get_min_moves(0, -1);
    int ans = INT_MAX;
    for (int i = 2; i <= MAX; i++)
        ans = min(ans, min_moves[0][i]);
    printf("%d\n", ans);
}