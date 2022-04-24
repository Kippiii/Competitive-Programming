#include <bits/stdc++.h>

using namespace std;

int main() {
   int t;
   cin >> t;
   while (t--) {
      int n, k;
      cin >> n >> k;
      int orig_k = k;
      string s;
      cin >> s;
      bool bits[n];
      for (int i = 0; i < n; i++)
         bits[i] = s[i] == '1';

      int flips[n];
      for (int i = 0; i < n; i++)
         flips[i] = 0;
      if (!bits[0] && k > 0) {
         int first_one = -1;
         for (int i = 1; i < n; i++) {
            if (bits[i]) {
               first_one = i;
               break;
            }
         }
         if (first_one != -1) {
            for (int i = 0; i < n; i++) {
               if (i == first_one)
                  continue;
               bits[i] = !bits[i];
            }
            flips[first_one]++;
         } else {
            for (int i = 0; i < n-1; i++)
               bits[i] = !bits[i];
            flips[n-1]++;
         }
         k--;
      }
      if (k % 2 == 1) {
         for (int i = 1; i < n; i++)
            bits[i] = !bits[i];
         flips[0]++;
         k--;
      }
      assert(k >= 0);

      int num_zeros = 0;
      for (int i = 0; i < n; i++)
         if (!bits[i])
            num_zeros++;
      int zero_flips = 0;
      while (num_zeros > 1 && k > 0) {
         zero_flips += 2;
         num_zeros -= 2;
         k -= 2;
      }
      assert(k >= 0);
      for (int i = 0; i < n; i++) {
         if (!bits[i] && zero_flips > 0) {
            zero_flips--;
            bits[i] = !bits[i];
            flips[i]++;
         }
      }
      assert(zero_flips == 0);
      if (num_zeros > 0 && k > 0) {
         for (int i = 0; i < n; i++)
            if (!bits[i]) {
               bits[i] = !bits[i];
               flips[i]++;
               k--;
               num_zeros--;
               break;
            }
         bits[n-1] = !bits[n-1];
         flips[n-1]++;
         k--;
      }
      assert(k >= 0);
      assert(k % 2 == 0);
      flips[0] += k;

      int sum = 0;
      for (int i = 0; i < n; i++)
         sum += flips[i];
      assert(sum == orig_k);

      for (int i = 0; i < n; i++)
         printf("%c", bits[i] ? '1' : '0');
      printf("\n");
      for (int i = 0; i < n; i++)
         printf("%d ", flips[i]);
      printf("\n");
   }
}
