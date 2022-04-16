#include <bits/stdc++.h>

using namespace std;

void memoize(string &s);
bool check_sub(string &full, string &sub);
bool all_sub(string &s, int num, int alph_size);

int memo[1000007][26];
int first_letter[26];

int main() {
   string alph;
   cin >> alph;
   string s;
   cin >> s;
   int n;
   cin >> n;
   memoize(s);

   bool is_sub[n];
   int length[n];
   int shortest_not_sub = 99999999;
   for (int i = 0; i < n; i++) {
      string q;
      cin >> q;
      is_sub[i] = check_sub(s, q);
      length[i] = (int) q.size();
      if (!is_sub[i])
         shortest_not_sub = min(shortest_not_sub, length[i]);
   }
   bool is_shortest = true;
   assert(shortest_not_sub <= 99999999);
   if (shortest_not_sub != 99999999) {
      is_shortest = all_sub(s, shortest_not_sub-1, (int) alph.size());
   }
   for (int i = 0; i < n; i++) {
      if (is_sub[i])
         printf("0\n");
      else if (length[i] > shortest_not_sub)
         printf("0\n");
      else if (!is_shortest)
         printf("0\n");
      else
         printf("1\n");
   }
}

void memoize(string &s) {
   for (int i = 0; i < (int) s.size(); i++)
      for (int j = 0; j < 26; j++)
         memo[i][j] = -1;

   int next_letters[26];
   for (int i = 0; i < 26; i++)
      next_letters[i] = -1;
   for (int i = (int) s.size()-1; i >= 0; i--) {
      for (int j = 0; j < 26; j++)
         memo[i][j] = next_letters[j];
      next_letters[s[i] - 'a'] = i;
   }
   for (int i = 0; i < 26; i++)
      first_letter[i] = next_letters[i];
}

bool check_sub(string &full, string &sub) {
   if ((int) sub.size() > (int) full.size())
      return false;
   int index = first_letter[sub[0] - 'a'];
   for (int i = 1; i < (int) sub.size(); i++) {
      //cout << full << ", " << sub << ": " << index << endl;
      if (index == -1)
         return false;
      index = memo[index][sub[i] - 'a'];
   }
   return index != -1;
}

bool all_sub(string &s, int num, int alph_size) {
   if (num == 0)
      return true;
   int cur_level[(int) s.size()];
   for (int i = 0; i < (int) s.size(); i++)
      cur_level[i] = -1;
   int first_len = 0;
   for (int i = 0; i < 26; i++) {
      if (first_letter[i] != -1) {
         first_len++;
         cur_level[first_letter[i]] = 1;
      }
   }
   if (first_len < alph_size)
      return false;
   for (int i = 0; i < (int) s.size(); i++) {
      if (cur_level[i] == -1 || cur_level[i] >= num)
         break;
      int cur_len = 0;
      for (int j = 0; j < 26; j++) {
         if (memo[i][j] != -1) {
            cur_len++;
            if (cur_level[memo[i][j]] != -1)
               cur_level[memo[i][j]] = min(cur_level[memo[i][j]], cur_level[i]+1);
            else
               cur_level[memo[i][j]] = cur_level[i]+1;
         }
      }
      if (cur_len < alph_size)
         return false;
   }
   return true;
}
