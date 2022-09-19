#include <bits/stdc++.h>

using namespace std;

#define NINF LLONG_MIN
#define PINF LLONG_MAX

int n, p, m, ar, ac;
char op_north, op_east, op_west, op_south;
int k_north, k_east, k_west, k_south;
int x[11], y[11], c[11];

long long memo[11][11][22][1 << 10];

long long operate(long long c, char op, int k) {
    if (c == NINF)
        return NINF;
    switch (op) {
        case '+':
            return c + k;
        case '-':
            return c - k;
        case '*':
            return c * k;
        case '/':
            if (c >= 0)
                return c / k;
            if (-c % k == 0)
                return c / k;
            return (c-k) / k;
    }
}

long long max_cost(int y_pos, int x_pos, int moves, int mask) {
    if (x_pos < 0 || x_pos >= n || y_pos < 0 || y_pos >= n)
        return NINF;
    if (memo[x_pos][y_pos][moves][mask] != PINF)
        return memo[x_pos][y_pos][moves][mask];

    if (moves == 0) {
        if (x_pos == ac-1 && y_pos == ar-1 && mask == (1 << p) - 1)
            return 0;
        return NINF;
    }

    int delivery = -1;
    for (int i = 0; i < p; i++)
        if (y[i]-1 == x_pos && x[i]-1 == y_pos && !(mask & (1 << i)))
            delivery = i;

    long long ans = operate(max_cost(y_pos + 1, x_pos, moves-1, mask), op_north, k_north);
    ans = max(ans, operate(max_cost(y_pos - 1, x_pos, moves-1, mask), op_south, k_south));
    ans = max(ans, operate(max_cost(y_pos, x_pos + 1, moves-1, mask), op_west, k_west));
    ans = max(ans, operate(max_cost(y_pos, x_pos - 1, moves-1, mask), op_east, k_east));
    ans = max(ans, max_cost(y_pos, x_pos, moves-1, mask));
    if (delivery != -1) {
        int new_mask = mask | (1 << delivery);
        ans = max(ans, operate(operate(max_cost(y_pos + 1, x_pos, moves-1, new_mask), op_north, k_north), '+', c[delivery]));
        ans = max(ans, operate(operate(max_cost(y_pos - 1, x_pos, moves-1, new_mask), op_south, k_south), '+', c[delivery]));
        ans = max(ans, operate(operate(max_cost(y_pos, x_pos + 1, moves-1, new_mask), op_west, k_west), '+', c[delivery]));
        ans = max(ans, operate(operate(max_cost(y_pos, x_pos - 1, moves-1, new_mask), op_east, k_east), '+', c[delivery]));
        ans = max(ans, operate(max_cost(y_pos, x_pos, moves-1, new_mask), '+', c[delivery]));
    }

    memo[x_pos][y_pos][moves][mask] = ans;
    return ans;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int case_num = 1; case_num <= t; case_num++) {
        scanf("%d%d%d%d%d", &n, &p, &m, &ar, &ac);
        scanf(" %c%d", &op_north, &k_north);
        scanf(" %c%d", &op_east, &k_east);
        scanf(" %c%d", &op_west, &k_west);
        scanf(" %c%d", &op_south, &k_south);
        for (int i = 0; i < p; i++)
            scanf("%d%d%d", x+i, y+i, c+i);

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < m+1; k++)
                    for (int l = 0; l < (1 << p); l++)
                        memo[i][j][k][l] = PINF;

        long long ans = NINF;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                ans = max(ans, max_cost(i, j, m, 0));

        if (ans > NINF)
            printf("Case #%d: %lld\n", case_num, ans);
        else
            printf("Case #%d: IMPOSSIBLE\n", case_num);
    }
}