#include <bits/stdc++.h>

using namespace std;

#define INF 1000000000000

#define ii pair<int, int>
#define iii pair<int, ii>

int main() {
   int n, k;
   scanf("%d%d", &n, &k);
   int nums[n][n];
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
         scanf("%d", &nums[i][j]);

   vector<ii> num_list[k];
   for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
         num_list[nums[i][j]-1].push_back(ii(i, j));

   long long row_dists[n];
   long long col_dists[n];
   for (int i = 0; i < n; i++) {
      row_dists[i] = INF;
      col_dists[i] = INF;
   }
   for (ii coord : num_list[0]) {
      row_dists[coord.first] = 0;
      col_dists[coord.second] = 0;
   }
   for (int num = 1; num < k; num++) {
      long long new_row[n];
      long long new_col[n];
      for (int i = 0; i < n; i++) {
         new_row[i] = INF;
         new_col[i] = INF;
      }

      for (ii coord : num_list[num]) {
         int row = coord.first;
         int col = coord.second;
         long long closest_dist = INF;
         for (int i = 0; i < n; i++) {
            long long cur_dist = row_dists[i] + (i - row)*(i - row);
            closest_dist = min(closest_dist, cur_dist);

            cur_dist = col_dists[i] + (i - col)*(i - col);
            closest_dist = min(closest_dist, cur_dist);
         }
         new_row[row] = min(new_row[row], closest_dist);
         new_col[col] = min(new_col[col], closest_dist);
      }

      for (int i = 0; i < n; i++) {
         row_dists[i] = new_row[i];
         col_dists[i] = new_col[i];
      }
   }

   long long ans = INF;
   for (int i = 0; i < n; i++) {
      ans = min(ans, row_dists[i]);
      ans = min(ans, col_dists[i]);
   }

   if (ans < INF)
      printf("%lld\n", ans);
   else
      printf("-1\n");
}
