#include <bits/stdc++.h>

using namespace std;

#define MAX_N 18

int count_close(int i, int j);

int n, k;
int s[1 << MAX_N];

int main() {
   scanf("%d%d", &n, &k);
   for (int i = 0; i < (1 << n); i++)
      scanf("%d", s + i);

   sort(s, s + (1 << n), greater<int>());
   int ans = count_close(1, 2);
   printf("%d\n", ans);
}

int count_close(int i, int j) {
   if (i >= (1 << n))
      return 0;
   int num_close = 0;
   int ip = 0;
   int jp = i;
   while (ip < i && jp < j) {
      if (s[ip] - s[jp] <= k) {
         jp++;
         num_close++;
      }
      ip++;
   }
   num_close += count_close(j, 2*j);
   return num_close;
}
