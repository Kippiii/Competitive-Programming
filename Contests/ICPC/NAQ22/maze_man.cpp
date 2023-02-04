#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>

int n, m;
char maze[105][105];
bool can_get[105][105]['W' - 'A' + 3];

vector<ii> dirs = {ii(1, 0), ii(-1, 0), ii(0, 1), ii(0, -1)};

bool is_valid(int x, int y) {
    if (x < 0 || x >= n)
        return false;
    if (y < 0 || y >= m)
        return false;
    return true;
}

void flood_fill(int x, int y) {
    if (maze[x][y] < 'A' || maze[x][y] > 'W')
        return;
    int val = maze[x][y] - 'A';

    bool visited[n][m];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            visited[i][j] = false;
    visited[x][y] = true;

    queue<ii> q;
    for (ii dir : dirs) {
        if (!is_valid(x + dir.first, y + dir.second))
            continue;
        visited[x + dir.first][y + dir.second] = true;
        char c = maze[x + dir.first][y + dir.second];
        if (c != ' ' && c != '.')
            continue;
        q.push(ii(x + dir.first, y + dir.second));
        can_get[x + dir.first][y + dir.second][val] = true;
    }

    while (!q.empty()) {
        ii pos = q.front();
        q.pop();
        for (ii dir : dirs) {
            if (!is_valid(pos.first + dir.first, pos.second + dir.second))
                continue;
            if (visited[pos.first + dir.first][pos.second + dir.second])
                continue;
            char c = maze[pos.first + dir.first][pos.second + dir.second];
            if (c == 'X')
                continue;
            visited[pos.first + dir.first][pos.second + dir.second] = true;
            q.push(ii(pos.first + dir.first, pos.second + dir.second));
            can_get[pos.first + dir.first][pos.second + dir.second][val] = true;
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    char garbage[100];
    fgets(garbage, 98, stdin);
    for (int i = 0; i < n; i++)
        fgets(maze[i], m+5, stdin);
    
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int k = 0; k < 'W' - 'A' + 3; k++)
                can_get[i][j][k] = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            flood_fill(i, j);
    
    int impossible = 0;
    bool unique['W' - 'A' + 1];
    for (int i = 0; i < 'W' - 'A' + 1; i++)
        unique[i] = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (maze[i][j] == '.') {
                bool found = false;
                for (int k = 0; k < 'W' - 'A' + 1; k++) {
                    if (can_get[i][j][k] && !found) {
                        found = true;
                        unique[k] = true;
                    }
                }
                if (!found)
                    impossible++;
            }
        }
    }

    int num_unique = 0;
    for (int i = 0; i < 'W' - 'A' + 1; i++)
        if (unique[i])
            num_unique++;

    printf("%d %d\n", num_unique, impossible);
}