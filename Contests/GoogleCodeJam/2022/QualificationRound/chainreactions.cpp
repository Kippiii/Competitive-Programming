#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define ii pair<long long, long long>
#define vii vector<ii>

ii get_fun(vvi &tree, int index);

int n;
int f[100005];

int main() {
   int t;
   scanf("%d", &t);
   for (int case_num = 1; case_num <= t; case_num++) {
      scanf("%d", &n);
      for (int i = 0; i < n; i++)
         scanf("%d", f + i);
      int p[n];
      for (int i = 0; i < n; i++)
         scanf("%d", p + i);

      vvi tree(n+1, vi());
      for (int i = 0; i < n; i++)
         tree[p[i]].push_back(i+1);

      ii ans = get_fun(tree, 0);
      printf("Case #%d: %lld\n", case_num, ans.first + ans.second);
   }
}

ii get_fun(vvi &tree, int index) {
   if ((int) tree[index].size() == 0)
      return ii(0, f[index-1]);
   vii vals;
   for (int i : tree[index])
      vals.push_back(get_fun(tree, i));
   int smallest = 0;
   for (int i = 1; i < (int) vals.size(); i++)
      if (vals[i].second < vals[smallest].second)
         smallest = i;
   ii ans(0, 0);
   for (int i = 0; i < (int) vals.size(); i++) {
      if (i == smallest) {
         ans.second += max(vals[i].second, (long long) (index >= 1 ? f[index-1] : 0));
      } else {
         ans.first += vals[i].second;
      }
      ans.first += vals[i].first;
   }
   return ans;
}
