#include <bits/stdc++.h>

using namespace std;

pair<string, int> compute_stack(int n) {
   if (n == 1)
      return make_pair("1", 0);
   if (n % 2 == 0) {
      pair<string, int> tmp = compute_stack(n / 2);
      return make_pair(tmp.first + "d+", tmp.second + 1);
   }
   pair<string, int> tmp = compute_stack((n - 1) / 2);
   return make_pair(tmp.first + "d+1+", tmp.second + 2);
}

int main() {
   int n;
   cin >> n;
   int stack[n];
   for (int i = 0; i < n; i++)
      cin >> stack[i];

   int sums = 0;
   string ans = "";
   for (int i = n-1; i >= 0; i--) {
      pair<string, int> tmp = compute_stack(stack[i] + sums);
      sums += tmp.second;
      ans = tmp.first + ans;
   }

   cout << ans << endl;;
}
