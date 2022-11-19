#include <bits/stdc++.h>

using namespace std;

#define vi vector<int>
#define vvi vector<vi>
#define vvvi vector<vvi>

vi result;

void unique(vi &a) {
     sort(a.begin(), a.end());
     auto i = a.begin();
     while (i != a.end() && i+1 != a.end()) {
          if (*i == *(i+1))
               a.erase(i+1);
          else
               i++;
     }
}

class SegmentTree {
private:
     vi raw_vals;
     vvi vals;
     vi val_count;
     int n;
     int left(int i) {
          return i << 1;
     }
     int right(int i) {
          return (i << 1) + 1;
     }

     void pre_add(int p, int L, int R, int i) {
          if (i < raw_vals[L] || i > raw_vals[R])
               return;
          val_count[p]++;
          if (L == R)
               return;
          int mid = (L + R) / 2;
          pre_add(left(p), L, mid, i);
          pre_add(right(p), mid+1, R, i);
     }

     void build(int p, int L, int R) {
          vals[p].assign(val_count[p], 0);
          val_count[p] = 0;
          if (L == R)
               return;
          int mid = (L + R) / 2;
          build(left(p), L, mid);
          build(right(p), mid+1, R);
     }

     void add(int p, int L, int R, int i, int v) {
          if (i < raw_vals[L] || i > raw_vals[R])
               return;
          vals[p][val_count[p]++] = v;
          if (L == R)
               return;
          int mid = (L + R) / 2;
          add(left(p), L, mid, i, v);
          add(right(p), mid+1, R, i, v);
     }

     void get(int p, int L, int R, int l, int h) {
          if (h < raw_vals[L] || l > raw_vals[R])
               return;
          if (l <= raw_vals[L] && h >= raw_vals[R]) {
               for (int i = 0; i < val_count[p] && (int) result.size() < 50; i++)
                    result.push_back(vals[p][i]);
               return;
          }
          int mid = (L + R) / 2;
          get(left(p), L, mid, l, min(raw_vals[mid], h));
          get(right(p), mid+1, R, max(l, raw_vals[mid+1]), h);
     }

public:
     SegmentTree(const vi &_raws) {
          raw_vals = _raws;
          n = (int) raw_vals.size();
          vals.assign(4*n, vi());
          val_count.assign(4*n, 0);
     }
     void pre_add(int i) {
          pre_add(1, 0, n-1, i);
     }
     void build() {
          build(1, 0, n-1);
     }
     void add(int i, int v) {
          add(1, 0, n-1, i, v);
     }
     void get(int l, int h) {
          get(1, 0, n-1, l, h);
     }
};

class SegmentTree2D {
private:
     vector<SegmentTree> trees;
     vi raw_vals;
     vvi vals;
     vi val_count;
     int n;
     int left(int i) {
          return i << 1;
     }
     int right(int i) {
          return (i << 1) + 1;
     }

     void pre_add1(int p, int L, int R, int x) {
          if (x < raw_vals[L] || x > raw_vals[R])
               return;
          val_count[p]++;
          if (L == R)
               return;
          int mid = (L + R) / 2;
          pre_add1(left(p), L, mid, x);
          pre_add1(right(p), mid+1, R, x);
     }

     void build1(int p, int L, int R) {
          vals[p].assign(val_count[p], 0);
          val_count[p] = 0;
          if (L == R)
               return;
          int mid = (L + R) / 2;
          build1(left(p), L, mid);
          build1(right(p), mid+1, R);
     }

     void pre_add2(int p, int L, int R, int x, int y) {
          if (x < raw_vals[L] || x > raw_vals[R])
               return;
          vals[p][val_count[p]++] = y;
          if (L == R)
               return;
          int mid = (L + R) / 2;
          pre_add2(left(p), L, mid, x, y);
          pre_add2(right(p), mid+1, R, x, y);
     }

     void build2(int p, int L, int R) {
          if (val_count[p] == 0)
               return;
          unique(vals[p]);
          trees[p] = SegmentTree(vals[p]);
          if (L == R)
               return;
          int mid = (L + R) / 2;
          build2(left(p), L, mid);
          build2(right(p), mid+1, R);
     }

     void pre_add3(int p, int L, int R, int x, int y) {
          if (val_count[p] == 0)
               return;
          if (x < raw_vals[L] || x > raw_vals[R])
               return;
          trees[p].pre_add(y);
          if (L == R)
               return;
          int mid = (L + R) / 2;
          pre_add3(left(p), L, mid, x, y);
          pre_add3(right(p), mid+1, R, x, y);
     }

     void build3(int p, int L, int R) {
          if (val_count[p] == 0)
               return;
          trees[p].build();
          if (L == R)
               return;
          int mid = (L + R) / 2;
          build3(left(p), L, mid);
          build3(right(p), mid+1, R);
     }

     void add(int p, int L, int R, int x, int y, int v) {
          if (val_count[p] == 0)
               return;
          if (x < raw_vals[L] || x > raw_vals[R])
               return;
          trees[p].add(y, v);
          if (L == R)
               return;
          int mid = (L + R) / 2;
          add(left(p), L, mid, x, y, v);
          add(right(p), mid+1, R, x, y, v);
     }

     void get(int p, int L, int R, int xl, int xh, int yl, int yh) {
          if (val_count[p] == 0)
               return;
          if (xh < raw_vals[L] || xl > raw_vals[R])
               return;
          if (xl <= raw_vals[L] && xh >= raw_vals[R]) {
               trees[p].get(yl, yh);
               return;
          }
          int mid = (L + R) / 2;
          get(left(p), L, mid, xl, min(raw_vals[mid], xh), yl, yh);
          get(right(p), mid+1, R, max(xl, raw_vals[mid+1]), xh, yl, yh);
     }

public:
     SegmentTree2D(const vi &_raw) {
          raw_vals = _raw;
          n = (int) raw_vals.size();
          trees.assign(4*n, SegmentTree(vi()));
          vals.assign(4*n, vi());
          val_count.assign(4*n, 0);
     }
     void pre_add1(int x) {
          pre_add1(1, 0, n-1, x);
     }
     void build1() {
          build1(1, 0, n-1);
     }
     void pre_add2(int x, int y) {
          pre_add2(1, 0, n-1, x, y);
     }
     void build2() {
          build2(1, 0, n-1);
     }
     void pre_add3(int x, int y) {
          pre_add3(1, 0, n-1, x, y);
     }
     void build3() {
          build3(1, 0, n-1);
     }
     void add(int x, int y, int v) {
          add(1, 0, n-1, x, y, v);
     }
     void get(int xl, int xh, int yl, int yh) {
          result = vi();
          get(1, 0, n-1, xl, xh, yl, yh);
     }
};

int main() {
     int n, q;
     scanf("%d%d", &n, &q);
     int x[n], y[n], h[n];
     for (int i = 0; i < n; i++)
          scanf("%d%d%d", x+i, y+i, h+i);
     int xl[q], yl[q], xh[q], yh[q];
     for (int i = 0; i < q; i++)
          scanf("%d%d%d%d", xl+i, yl+i, xh+i, yh+i);
     
     vi x_vals(x, x+n);
     unique(x_vals);
     SegmentTree2D st(x_vals);

     for (int i = 0; i < n; i++)
          st.pre_add1(x[i]);
     st.build1();
     for (int i = 0; i < n; i++)
          st.pre_add2(x[i], y[i]);
     st.build2();
     for (int i = 0; i < n; i++)
          st.pre_add3(x[i], y[i]);
     st.build3();
     for (int i = 0; i < n; i++)
          st.add(x[i], y[i], h[i]);
     
     for (int i = 0; i < q; i++) {
          st.get(xl[i], xh[i], yl[i], yh[i]);
          if ((int) result.size() >= 45)
               printf("1\n");
          else {
               sort(result.begin(), result.end());
               bool has_triangle = false;
               for (int i = 2; i < (int) result.size(); i++) {
                    if (result[i-2] + result[i-1] > result[i]) {
                         has_triangle = true;
                         break;
                    }
               }
               if (has_triangle)
                    printf("1\n");
               else
                    printf("0\n");
          }
     }
}