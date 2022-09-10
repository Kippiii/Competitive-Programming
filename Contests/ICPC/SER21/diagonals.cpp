#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define vii vector<ii>

int n;
int corners[9][9];
char slashes[8][9];

char get_slash(int x, int y) {
    if (x < 0 || y < 0)
        return 'X';
    if (x > n || y > n)
        return 'X';
    return slashes[x][y];
}

bool dfs_visit[10][10];
bool dfs(int x, int y, ii prev) {
    dfs_visit[x][y] = true;

    char nw = get_slash(x-1, y-1);
    char ne = get_slash(x, y-1);
    char sw = get_slash(x-1, y);
    char se = get_slash(x, y);

    bool cycle = false;
    if (nw == '\\' && prev != ii(x-1, y-1)) {
        if (dfs_visit[x-1][y-1])
            return true;
        cycle |= dfs(x-1, y-1, ii(x, y));
    }
    if (ne == '/' && prev != ii(x+1, y-1)) {
        if (dfs_visit[x+1][y-1])
            return true;
        cycle |= dfs(x+1, y-1, ii(x, y));
    }
    if (sw == '/' && prev != ii(x-1, y+1)) {
        if (dfs_visit[x-1][y+1])
            return true;
        cycle |= dfs(x-1, y+1, ii(x, y));
    }
    if (se == '\\' && prev != ii(x+1, y+1)) {
        if (dfs_visit[x+1][y+1])
            return true;
        cycle |= dfs(x+1, y+1, ii(x, y));
    }

    return cycle;
}

bool has_cycles() {
    for (int i = 0; i < n+1; i++)
        for (int j = 0; j < n+1; j++)
            dfs_visit[i][j] = false;
    
    bool cycle = false;
    for (int i = 0; i < n+1; i++)
        for (int j = 0; j < n+1; j++)
            if (!dfs_visit[i][j])
                cycle |= dfs(i, j, ii(-1, -1));
    
    return cycle;
}

bool update_corner(int x, int y, vii &changes) {
    if (corners[x][y] == -1)
        return true;
    if (x < 0 || y < 0 || x > n || y > n)
        return true;

    char nw = get_slash(x-1, y-1);
    char ne = get_slash(x, y-1);
    char sw = get_slash(x-1, y);
    char se = get_slash(x, y);

    int unknown = (nw == '.') + (ne == '.') + (sw == '.') + (se == '.');
    int pointed = (nw == '\\') + (ne == '/') + (sw == '/') + (se == '\\');

    if (unknown == corners[x][y] - pointed) {
        if (unknown == 0)
            return true;
        if (nw == '.') {
            slashes[x-1][y-1] = '\\';
            changes.push_back(ii(x-1, y-1));
        }
        if (ne == '.') {
            slashes[x][y-1] = '/';
            changes.push_back(ii(x, y-1));
        }
        if (sw == '.') {
            slashes[x-1][y] = '/';
            changes.push_back(ii(x-1, y));
        }
        if (se == '.') {
            slashes[x][y] = '\\';
            changes.push_back(ii(x, y));
        }
    } else if (pointed == corners[x][y]) {
        if (nw == '.') {
            slashes[x-1][y-1] = '/';
            changes.push_back(ii(x-1, y-1));
        }
        if (ne == '.') {
            slashes[x][y-1] = '\\';
            changes.push_back(ii(x, y-1));
        }
        if (sw == '.') {
            slashes[x-1][y] = '\\';
            changes.push_back(ii(x-1, y));
        }
        if (se == '.') {
            slashes[x][y] = '/';
            changes.push_back(ii(x, y));
        }
    } else if (unknown < corners[x][y] - pointed || pointed > corners[x][y]) {
        return false;
    } else {
        return true;
    }
    bool is_good = true;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            is_good &= update_corner(x+i, y+j, changes);
    return is_good;
}

bool backtrack(int value) {
    if (value == -1) {
        return true;
    }

    int x = value % n;
    int y = value / n;
    if (slashes[x][y] == '.') {
        slashes[x][y] = '\\';
        vii changes;
        bool valid = update_corner(x, y, changes) && update_corner(x+1, y, changes) && update_corner(x, y+1, changes) && update_corner(x+1, y+1, changes) && !has_cycles();
        if (valid) {
            bool found_sol = backtrack(value - 1);
            if (found_sol)
                return true;
        }
        for (ii change : changes)
            slashes[change.first][change.second] = '.';

        slashes[x][y] = '/';
        changes = vii();
        valid = update_corner(x, y, changes) && update_corner(x+1, y, changes) && update_corner(x, y+1, changes) && update_corner(x+1, y+1, changes) && !has_cycles();
        if (valid) {
            bool found_sol = backtrack(value - 1);
            if (found_sol)
                return true;
        }
        for (ii change : changes)
            slashes[change.first][change.second] = '.';

        slashes[x][y] = '.';
        return false;
    } else {
        return backtrack(value - 1);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n+1; i++) {
        char corner_str[n+2];
        scanf("%s", corner_str);
        for (int j = 0; j < n+1; j++) {
            if (corner_str[j] == '+')
                corners[i][j] = -1;
            else
                corners[i][j] = corner_str[j] - '0';
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            slashes[i][j] = '.';
        slashes[i][n] = 0;
    }

    vii changes;
    for (int i = 0; i < n+1; i++) {
        for (int j = 0; j < n+1; j++) {
            update_corner(i, j, changes);
        }
    }

    bool success = backtrack(n*n - 1);
    // assert(success)

    for (int i = 0; i < n; i++)
        printf("%s\n", slashes[i]);
}