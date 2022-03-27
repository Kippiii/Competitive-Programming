#include <bits/stdc++.h>

using namespace std;

#define ii pair<int, int>

#define MAX_N 20

double pr[1 << MAX_N][MAX_N];
double ex[1 << MAX_N];

int main() {
   int n;
   scanf("%d", &n);
   double p[n];
   for (int i = 0; i < n; i++)
      scanf("%lf", p+i);

   vector<int> combs[n+1];
   for (int comb = 0; comb < (1 << n); comb++) {
      int count = 0;
      for (int i = 0; i < n; i++) {
         if (comb & (1 << i)) {
            count++;
         }
      }
      combs[count].push_back(comb);
   }

   for (int comb : combs[2]) {
      for (int i = 0; i < n; i++)
         if (comb & (1 << i))
            pr[comb][i] = 0;
      ex[comb] = 0;
   }

   double cur_p[1 << n];
   double cur_np[1 << n];
   for (int comb = 0; comb < 1 << n; comb++) {
      double my_p = 1;
      double my_np = 1;
      for (int i = 0; i < n; i++) {
         if (comb & (1 << i)) {
            my_p *= p[i];
            my_np *= 1 - p[i];
         }
      }
      cur_p[comb] = my_p;
      cur_np[comb] = my_np;
   }

   for (int i = 3; i <= n; i++) {
      for (int comb : combs[i]) {
         for (int j = 0; j < n; j++) {
            if ((comb & (1 << j))) {
               pr[comb][j] = p[j]*cur_np[comb ^ (1 << j)] + (1-p[j])*cur_p[comb ^ (1 << j)];
            }
         }
      }

      for (int comb : combs[i]) {
         double sum1 = 0;
         double sum2 = 0;
         for (int k = 0; k < n; k++) {
            if (comb & (1 << k)) {
               sum1 += pr[comb][k];
               sum2 += pr[comb][k] * ex[comb ^ (1 << k)];
            }
         }
         ex[comb] = (1 + sum2)/sum1;
      }
   }

   printf("%lf\n", ex[(1 << n) - 1]);
}
