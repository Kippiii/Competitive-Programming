#include <bits/stdc++.h>

#define LSOne(S) ((S) & -(S))

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

class FenwickTree {
private: vll ft;
public:
     FenwickTree(int n) {
          ft.assign(n + 1, 0);
     }
     void build(const vll &f) {
          int n = (int) f.size() - 1;
          ft.assign(n + 1, 0);
          for (int i = 1; i <= n; i++) {
               ft[i] += f[i];
               if (i + LSOne(i) <= n) {
                    ft[i + LSOne(i)] += ft[i];
               }
          }
     }
     FenwickTree(const vll &f) {
          build(f);
     }
     ll rsq(int a) {
          int sum = 0;
          for (; a; a -= LSOne(a)) sum += ft[a];
          return sum;
     }
     ll rsq(int a, int b) {
          return rsq(b) - ((a == 1) ? 0 : rsq(a));
     }
     void update(int a, int val) {
          for (; a < (int) ft.size(); a += LSOne(a)) ft[a] += val;
     }
};
