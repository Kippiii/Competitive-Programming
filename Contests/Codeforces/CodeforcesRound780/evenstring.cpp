#include <bits/stdc++.h>

using namespace std;

int calc_removal(string &s, int index);

int memo[200005];
int next_letter[200005];

int main() {
   int t;
   cin >> t;
   while (t--) {
      string s;
      cin >> s;
      int n = (int) s.size();
      for (int i = 0; i < n; i++)
         memo[i] = -1;
      int last_letter[26];
      for (int i = 0; i < 26; i++)
         last_letter[i] = n;
      for (int i = n-1; i >= 0; i--) {
         next_letter[i] = last_letter[s[i] - 'a'];
         last_letter[s[i] - 'a'] = i;
      }

      int ans = calc_removal(s, 0);
      cout << ans << endl;
   }
}

int calc_removal(string &s, int index) {
   if (index < 0 || index >= (int) s.size())
      return 0;
   if (memo[index] != -1)
      return memo[index];
   int ans = calc_removal(s, index+1)+1;
   if (next_letter[index] < (int) s.size())
      ans = min(ans, calc_removal(s, next_letter[index]+1) + (next_letter[index] - index) - 1);
   memo[index] = ans;
   return memo[index];
}
