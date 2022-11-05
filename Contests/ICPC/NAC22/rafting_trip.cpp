#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define vii vector<ii>

int r, c;
char grid[505][505];
bool visited[505][505];
bool been_before[505][505];
vii tree[505][505];
vii roots;
ii loop[505][505];

bool is_valid(int x, int y) {
    return x >= 0 && x < r && y >= 0 && y < c;
}

void dfs(int x, int y) {
    if (!is_valid(x, y) || been_before[x][y])
        return;
    if (grid[x][y] != 'v' && grid[x][y] != '^' && grid[x][y] != '<' && grid[x][y] != '>')
        return;
    
    stack<ii> s;
    s.push(ii(x, y));
    visited[x][y] = true;
    been_before[x][y] = true;
    ii prev = ii(x, y);
    while (is_valid(prev.first, prev.second)) {
        ii next = ii(-1, -1);
        switch (grid[prev.first][prev.second]) {
            case 'v':
                next = ii(prev.first+1, prev.second);
                break;
            case '^':
                next = ii(prev.first-1, prev.second);
                break;
            case '<':
                next = ii(prev.first, prev.second-1);
                break;
            case '>':
                next = ii(prev.first, prev.second+1);
                break;
            default:
                break;
        }
        if (grid[next.first][next.second] != 'v' && grid[next.first][next.second] != '^' && grid[next.first][next.second] != '<' && grid[next.first][next.second] != '>') {
            next = ii(-1, -1);
        }
        if (!is_valid(next.first, next.second)) {
            roots.push_back(prev);
            break;
        }
        if (visited[next.first][next.second]) {
            roots.push_back(prev);
            ii top(-1, -1);
            while (top.first != next.first || top.second != next.second) {
                top = s.top();
                s.pop();
                loop[top.first][top.second] = next;
                visited[top.first][top.second] = false;
            }
            break;
        }
        if (been_before[next.first][next.second]) {
            tree[next.first][next.second].push_back(prev);
            break;
        }
        visited[next.first][next.second] = true;
        been_before[next.first][next.second] = true;
        tree[next.first][next.second].push_back(prev);
        prev = next;
        s.push(next);
    }

    while (!s.empty()) {
        ii cur = s.top();
        s.pop();
        visited[cur.first][cur.second] = false;
    }
}

void gen_tree() {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++) {
            visited[i][j] = false;
            loop[i][j] = ii(-1, -1);
        }
    
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            dfs(i, j);

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if (loop[i][j].first != -1 && loop[i][j].second != -1) {
                if (loop[i][j].first == i && loop[i][j].second == j)
                    continue;
                vii for_loop;
                vii old;
                for (ii adj: tree[i][j]) {
                    if (loop[i][j] != loop[adj.first][adj.second])
                        for_loop.push_back(adj);
                    else
                        old.push_back(adj);
                }
                tree[i][j] = old;
                for (ii val : for_loop)
                    tree[loop[i][j].first][loop[i][j].second].push_back(val);
            }
        }
    }
}

bool started[505][505];
vii new_spots[505][505];
int tree_explore(int x, int y, set<ii> &spots) {
    stack<ii> s;
    s.push(ii(x, y));

    int ans = 0;
    while (!s.empty()) {
        ii cur = s.top();
        s.pop();
        x = cur.first;
        y = cur.second;

        if (!started[x][y]) {
            if (is_valid(x-1, y) && grid[x-1][y] == '#' && spots.find(ii(x-1, y)) == spots.end())
                new_spots[x][y].push_back(ii(x-1, y));
            if (is_valid(x+1, y) && grid[x+1][y] == '#' && spots.find(ii(x+1, y)) == spots.end())
                new_spots[x][y].push_back(ii(x+1, y));
            if (is_valid(x, y-1) && grid[x][y-1] == '#' && spots.find(ii(x, y-1)) == spots.end())
                new_spots[x][y].push_back(ii(x, y-1));
            if (is_valid(x, y+1) && grid[x][y+1] == '#' && spots.find(ii(x, y+1)) == spots.end())
                new_spots[x][y].push_back(ii(x, y+1));

            if ((int) tree[x][y].size() == 0) {
                ans = max(ans, (int) spots.size() + (int) new_spots[x][y].size());
                continue;
            }

            for (ii spot : new_spots[x][y])
                spots.insert(spot);
            s.push(ii(x, y));
            for (ii node : tree[x][y])
                s.push(node);
            started[x][y] = true;
        } else {
            for (ii spot : new_spots[x][y])
                spots.erase(spot);
        }
    }
    
    return ans;
}

int max_spots() {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            started[i][j] = false;
    int ans = 0;
    set<ii> spots;
    for (ii root : roots) {
        ans = max(ans, tree_explore(root.first, root.second, spots));
    }
    return ans;
}

int main() {
    scanf("%d%d", &r, &c);
    for (int i = 0; i < r; i++)
        scanf("%s", grid[i]);
    
    gen_tree();
    int ans = max_spots();

    printf("%d\n", ans);
}