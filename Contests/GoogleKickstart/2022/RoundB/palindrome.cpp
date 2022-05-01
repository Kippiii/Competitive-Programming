#include <bits/stdc++.h>

using namespace std;

bool is_palindrome(long long n);

int main() {
   int t;
   scanf("%d", &t);
   for (int case_num = 1; case_num <= t; case_num++) {
      long long a;
      scanf("%lld", &a);
      long long ans = 0;
      for (long long i = 1; i*i <= a; i++) {
         if (a % i == 0) {
            if (is_palindrome(i)) {
               ans++;
            }
            if (i != a/i && is_palindrome(a / i)) {
               ans++;
            }
         }
      }
      printf("Case #%d: %lld\n", case_num, ans);
   }
}

bool is_palindrome(long long n) {
   string s = to_string(n);
   string r(s);
   reverse(r.begin(), r.end());
   return s == r;
}
