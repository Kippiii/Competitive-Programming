#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>

int n, sqrtn;
vi adj[100005];
long long degree[100005];
vi heavy, light;
bool is_light[100005];

long long full_count();
long long full_count_dfs(int start);
bool is_triangle(int n1, int n2, int n3);
bool is_connected(int n1, int n2);
long long count_heavy_triangles();
long long count_light_triangles();

int main() {
   int m;
   scanf("%d%d", &n, &m);
   for (int i = 0; i < m; i++) {
      int u, v;
      scanf("%d%d", &u, &v);
      adj[u-1].push_back(v-1);
      adj[v-1].push_back(u-1);
   }

   for (int i = 0; i < n; i++) {
      sort(adj[i].begin(), adj[i].end());
      degree[i] = (int) adj[i].size();
   }

   long long ans = full_count();

   for (int i = 0; i < n; i++)
      is_light[i] = false;
   sqrtn = sqrt(n);
   for (int i = 0; i < n; i++) {
      if (degree[i] >= sqrtn)
         heavy.push_back(i);
      else {
         light.push_back(i);
         is_light[i] = true;
      }
   }

   ans -= count_heavy_triangles();
   ans -= count_light_triangles();
   printf("%lld\n", ans);
}

bool full_count_visited[100005];
long long full_count() {
   for (int i = 0; i < n; i++)
      full_count_visited[i] = false;

   long long ans = 0;
   for (int i = 0; i < n; i++)
      if (!full_count_visited[i])
         ans += full_count_dfs(i);
   return ans;
}

long long full_count_dfs(int start) {
   if (full_count_visited[start])
      return 0;
   full_count_visited[start] = true;
   if (degree[start] < 4)
      return 0;

   long long ans = 0;
   for (int a : adj[start])
      if (degree[a] >= 2)
         ans += ((degree[start]-1)*(degree[start]-2)*(degree[start]-3)/6) * (degree[a] - 1);

   return ans;
}

bool is_triangle(int n1, int n2, int n3) {
   return is_connected(n1, n2) && is_connected(n2, n3) && is_connected(n3, n1);
}

bool is_connected(int n1, int n2) {
   return binary_search(adj[n1].begin(), adj[n1].end(), n2);
}

long long count_heavy_triangles() {
   long long ans = 0;
   for (int q = 0; q < (int) heavy.size(); q++) {
      int i = heavy[q];
      for (int w = q+1; w < (int) heavy.size(); w++) {
         int j = heavy[w];
         for (int e = w+1; e < (int) heavy.size(); e++) {
            int k = heavy[e];
            if (is_triangle(i, j, k)) {
               ans += (degree[i] - 2)*(degree[i] - 3) + (degree[j] - 2)*(degree[j] - 3) + (degree[k] - 2)*(degree[k] - 3);
            }
         }
      }
   }
   return ans;
}

long long count_light_triangles() {
   long long ans = 0;
   for (int i : light) {
      for (int j : adj[i])
         for (int k : adj[i])
            if (j != k && is_triangle(i, j, k)) {
               if (is_light[j] && j <= i)
                  continue;
               if (is_light[k] && k <= i)
                  continue;
               if (j > k)
                  continue;
               ans += (degree[i] - 2)*(degree[i] - 3) + (degree[j] - 2)*(degree[j] - 3) + (degree[k] - 2)*(degree[k] - 3);
            }
   }
   return ans;
}
