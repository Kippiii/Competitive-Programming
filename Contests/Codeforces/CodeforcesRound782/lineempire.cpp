#include <bits/stdc++.h>

using namespace std;

int main() {
   int t;
   scanf("%d", &t);
   while (t--) {
      long long n, a, b;
      scanf("%lld%lld%lld", &n, &a, &b);
      long long x[n];
      for (int i = 0; i < n; i++)
         scanf("%lld", x + i);

      long long sum_arr[n];
      sum_arr[n-1] = x[n-1];
      for (int i = n-2; i >= 0; i--)
         sum_arr[i] = sum_arr[i+1] + x[i];

      long long ans = b * x[0];
      long long best_ans = b * sum_arr[0];
      int cur_spot = x[0];
      ans += a * x[0];
      for (int i = 1; i < n; i++) {
         long long val1 = (sum_arr[i] - (n - i)*cur_spot)*b;
         best_ans = min(best_ans, ans + val1);
         ans += (x[i] - cur_spot)*(a+b);
         cur_spot = x[i];
      }

      printf("%lld\n", best_ans);
   }
}
