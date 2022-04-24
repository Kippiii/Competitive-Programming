#include <bits/stdc++.h>

using namespace std;

int main() {
   int n, k;
   cin >> n >> k;
   string s[n];
   for (int i = 0; i < n; i++)
      cin >> s[i];

   bool graph[2*k][2*k];
   for (int i = 0; i < 2*k; i++)
      for (int j = 0; j < 2*k; j++)
         graph[i][j] = false;
   for (int i = 0; i < 2*k; i++)
      graph[i][i] = true;
   for (int i = 0; i < k; i++) {
      int true_index = 2*i;
      int false_index = 2*i + 1;
      for (int j = 0; j < n; j++) {
         for (int l = 0; l < k; l++) {
            if (i == l)
               continue;
            if (s[j][i] == 'T' || s[j][i] == 'F') {
               int index = (s[j][i] == 'T') ? true_index : false_index;
               if (s[j][l] == 'T')
                  graph[index][2*l+1] = true;
               else if (s[j][l] == 'F')
                  graph[index][2*l] = true;
            }
         }
      }
   }

   //Floyd Warshall
   for (int l = 0; l < 2*k; l++)
      for (int i = 0; i < 2*k; i++)
         for (int j = 0; j < 2*k; j++)
            if (graph[i][l] && graph[l][j])
               graph[i][j] = true;

   bool possible = true;
   string ans = "";
   for (int i = 0; i < k; i++)
      ans += "?";
   for (int i = 0; i < k; i++) {
      if (ans[i] != '?')
         continue;
      if (graph[2*i][2*i+1] && graph[2*i+1][2*i]) {
         possible = false;
         break;
      }
      if (!graph[2*i+1][2*i]) {
         for (int j = 0; j < k; j++) {
            if (graph[2*i+1][2*j])
               ans[j] = 'T';
            if (graph[2*i+1][2*j+1])
               ans[j] = 'F';
         }
      } else {
         for (int j = 0; j < k; j++) {
            if (graph[2*i][2*j])
               ans[j] = 'T';
            if (graph[2*i][2*j+1])
               ans[j] = 'F';
         }
      }
   }

   if (!possible)
      cout << "-1" << endl;
   else
      cout << ans << endl;
}
