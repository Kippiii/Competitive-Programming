#include <bits/stdc++.h>

using namespace std;

int main() {
   int t;
   scanf("%d", &t);
   while (t--) {
      int n;
      scanf("%d", &n);
      int p[n];
      p[0] = -1;
      for (int i = 1; i < n; i++) {
         scanf("%d", p+i);
         p[i]--;
      }

      int num_children[n+1];
      for (int i = 0; i < n+1; i++)
         num_children[i] = 0;
      for (int i = 0; i < n; i++)
         num_children[p[i]+1]++;

      sort(num_children, num_children + n + 1);
      int num_internal = 0;
      for (int i = 0; i < n+1; i++)
         if (num_children[i] > 0)
            num_internal++;
      for (int i = n; i >= 0; i--) {
         int j = n - i;
         num_children[i] -= max(0, num_internal - j);
      }

      sort(num_children, num_children + n + 1);
      int ans = num_internal;
      while (num_children[n] > 0) {
         num_children[n]--;
         int index = n;
         while (index > 0 && !(num_children[index] <= 0 && num_children[index-1] <= 0)) {
            if (num_children[index] < num_children[index-1]) {
               int tmp = num_children[index];
               num_children[index] = num_children[index-1];
               num_children[index-1] = tmp;
            }
            num_children[index]--;
            index--;
         }
         num_children[0]--;
         ans++;
      }

      printf("%d\n", ans);
   }
}
