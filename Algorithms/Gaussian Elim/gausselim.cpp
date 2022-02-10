#include <bits/stdc++.h>

using namespace std;

const int MAX_N = 3;
struct AugMatrix {
   double mat[MAX_N][MAX_N + 1];
};
struct ColVect {
   double vec[MAX_N];
};

ColVect gauss_elim(AugMatrix aug, int n, int m) {
   assert(n <= m); // n = vars, m = equations
   for (int i = 0; i < m-1; i++) {
      int l = i;
      for (int j = i+1; j < m; j++)
         if (fabs(aug.mat[j][i]) > fabs(aug.mat[l][i]))
            l = j;
      for (int j = i; j <= n; j++)
         swap(aug.mat[l][j], aug.mat[i][j]);
      for (int j = i+1; j < m; j++)
         for (int k = n; k >= i; k--)
            aug.mat[j][k] -= aug.mat[i][k] * aug.mat[j][i] / aug.mat[i][i];
   }

   ColVect ans;
   for (int j = m-1; j >= 0; j--) {
      double tmp = 0;
      for (int k = j+1; k < n; k++)
         tmp += aug.mat[j][k]*ans.vec[k];
      ans.vec[j] = (aug.mat[j][n] - tmp) / aug.mat[j][j];
   }
   return ans;
}
