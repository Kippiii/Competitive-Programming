#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>
#define iii pair<ii, int>
#define vii vector<ii>

int n, k, c;
iii contacts[1005];
vii adj[1005][12];
bool can_reach_without[1005][12][1005];
int last_appearance[1005];
bool visited[1005][12];

void fill_can_reach_without() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            can_reach_without[i][0][j] = true;
    for (int i = 0; i < n; i++)
        for (int j = 1; j <= k; j++)
            for (int l = 0; l < n; l++)
                can_reach_without[i][j][l] = false;
    
    for (int i = 1; i <= k; i++) {
        for (int j = 0; j < n; j++) {
            for (ii a : adj[j][i-1]) {
                int index = a.first;
                for (int l = 0; l < n; l++) {
                    if (j != l && can_reach_without[j][i-1][l])
                        can_reach_without[index][i][l] = true;
                }
            }
        }
    }
}

void fill_last_appearance() {
    for (int i = 0; i < n; i++)
        last_appearance[i] = -1;
    
    for (int i = 0; i < c; i++) {
        int a = contacts[i].first.first;
        int b = contacts[i].first.second;
        int d = contacts[i].second;
        last_appearance[a] = max(last_appearance[a], d);
        last_appearance[b] = max(last_appearance[b], d);
    }
}

void delete_edge(int a, int d, int b) {
    //printf("Deleting edge from %d to %d on day %d\n", a, b, d+1);
    for (int i = 0; i < (int) adj[a][d].size(); i++) {
        if (adj[a][d][i].first == b) {
            adj[a][d].erase(adj[a][d].begin()+i);
            return;
        }
    }
    printf("Could not delete edge from %d to %d on day %d\n", a, b, d+1);
    assert(false);
}

void trim_edges() {
    for (int i = 0; i < c; i++) {
        int a = contacts[i].first.first;
        int b = contacts[i].first.second;
        int d = contacts[i].second;
        if (!can_reach_without[a][d-1][b] || d < last_appearance[a])
            delete_edge(a, d-1, b);
        if (!can_reach_without[b][d-1][a] || d < last_appearance[b])
            delete_edge(b, d-1, a);
    }
}

void bfs() {
    queue<ii> q;
    for (int i = 0; i < n; i++) {
        q.push(ii(i, 0));
        visited[i][0] = true;
        for (int j = 1; j <= k; j++)
            visited[i][j] = false;
    }

    while (!q.empty()) {
        ii top = q.front();
        q.pop();
        for (ii a : adj[top.first][top.second]) {
            if (!visited[a.first][a.second]) {
                visited[a.first][a.second] = true;
                q.push(a);
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &k, &c);
    for (int i = 0; i < c; i++) {
        int a, b, d;
        scanf("%d%d%d", &a, &b, &d);
        contacts[i] = iii(ii(a-1, b-1), d);
    }

    for (int i = 0; i < c; i++) {
        int a = contacts[i].first.first;
        int b = contacts[i].first.second;
        int d = contacts[i].second;
        adj[a][d-1].push_back(ii(b, d));
        adj[b][d-1].push_back(ii(a, d));
    }
    fill_can_reach_without();
    fill_last_appearance();
    trim_edges();
    bfs();

    vector<int> ans;
    for (int i = 0; i < n; i++)
        if (visited[i][k])
            ans.push_back(i);
    
    printf("%d\n", (int) ans.size());
    for (int i : ans)
        printf("%d\n", i+1);
}