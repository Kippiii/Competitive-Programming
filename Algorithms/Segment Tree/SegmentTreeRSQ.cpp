#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class SegmentTree {
private:
     vi st, A, lazy;
     int n;
     int left(int i) {
          return i << 1;
     }
     int right(int i) {
          return (i << 1) + 1;
     }

     int conquer(int i, int j) {
          if (i == -1) return j;
          if (j == -1) return i;
          return i + j;
     }

     void build(int p, int L, int R) {
          if (L == R)
               st[p] = A[L];
          else {
               build(left(p), L, (L + R) / 2);
               build(right(p), (L + R) / 2 + 1, R);
               int p1 = st[left(p)];
               int p2 = st[right(p)];
               st[p] = conquer(st[left(p)], st[right(p)]);
          }
     }

     void propagate(int p, int L, int R) {
          if (lazy[p] != -1) {
               st[p] = lazy[p] * (R - L + 1);
               if (L != R)
                    lazy[left(p)] = lazy[right(p)] = lazy[p];
               else
                    A[L] = lazy[p];
               lazy[p] = -1;
          }
     }

     int rsq(int p, int L, int R, int i, int j) {
          propagate(p, L, R);
          if (i > j) return -1;
          if (R <= j && L >= i) return st[p];

          int mid = (L + R) / 2;
          return conquer(rsq(left(p), L, mid, i, min(mid, j)), rsq(right(p), mid + 1, R, max(i, mid + 1), j));
     }

     void update(int p, int L, int R, int i, int j, int val) {
          propagate(p, L, R);
          if (i > j) return;
          if (R <= j && L >= i) {
               lazy[p] = val;
               propagate(p, L, R);
          } else {
               int mid = (L + R) / 2;
               update(left(p), L, mid, i, min(mid, j), val);
               update(right(p), mid + 1, R, max(i, mid + 1), j, val);
               st[p] = conquer(st[left(p)], st[right(p)]);
          }
     }

public:
     SegmentTree(const vi &_A) {
          A = _A;
          n = (int) A.size();
          st.assign(4*n, 0);
          lazy.assign(4*n, -1);
          build(1, 0, n - 1);
     }
     int rsq(int i, int j) {
          return rsq(1, 0, n - 1, i, j);
     }
     void update(int i, int j, int val) {
          update(1, 0, n - 1, i, j, val);
     }
};
