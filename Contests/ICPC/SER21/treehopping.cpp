#include <bits/stdc++.h>

using namespace std;

#define MAX_N 100005

typedef vector<int> vi;

vector<vi> children;

bool visited[MAX_N];
void tree_dfs(vector<vi> &adj, int index) {
  visited[index] = true;
  for (auto close : adj[index]) {
    if (!visited[close]) {
      children[index].push_back(close);
      tree_dfs(adj, close);
    }
  }
}
void generate_tree(vector<vi> &adj, int n) {
  for (int i = 0; i < n; i++)
    visited[i] = false;
  children = vector<vi>(n, vi());
  tree_dfs(adj, 0);
}

int L[2*MAX_N], E[2*MAX_N], H[MAX_N], idx;
void dfs(int cur, int depth) {
  H[cur] = idx;
  E[idx] = cur;
  L[idx++] = depth;
  for (auto &nxt : children[cur]) {
    dfs(nxt, depth+1);
    E[idx] = cur;
    L[idx++] = depth;
  }
}
void buildRMQ() {
  idx = 0;
  memset(H, -1, sizeof H);
  dfs(0, 0);
}

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
    return min(i, j);
  }

  void build(int p, int L, int R) {
    if (L == R)
      st[p] = A[L];
    else {
      build(left(p), L, (L+R)/2);
      build(right(p), (L+R)/2+1, R);
      int p1 = st[left(p)];
      int p2 = st[right(p)];
      st[p] = conquer(st[left(p)], st[right(p)]);
    }
  }

  void propagate(int p, int L, int R) {
    if (lazy[p] != -1) {
      st[p] = lazy[p];
      if (L != R)
        lazy[left(p)] = lazy[right(p)] = lazy[p];
      else
        A[L] = lazy[p];
      lazy[p] = -1;
    }
  }

  int rmq(int p, int L, int R, int i, int j) {
    propagate(p, L, R);
    if (i > j) return -1;
    if (R <= j && L >= i) return st[p];

    int mid = (L+R)/2;
    return conquer(rmq(left(p), L, mid, i, min(mid, j)), rmq(right(p), mid+1, R, max(i, mid+1), j));
  }

public:
  SegmentTree(const vi &_A) {
    A = _A;
    n = (int) A.size();
    st.assign(4*n, 0);
    lazy.assign(4*n, -1);
    build(1, 0, n-1);
  }
  int rmq(int i, int j) {
    return rmq(1, 0, n-1, i, j);
  }
};

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int n;
    scanf("%d", &n);
    vector<vi> adj(n, vi());
    for (int i = 0; i < n-1; i++) {
      int a, b;
      scanf("%d%d", &a, &b);
      adj[a-1].push_back(b-1);
      adj[b-1].push_back(a-1);
    }
    generate_tree(adj, n);

    buildRMQ();

    vi new_L;
    for (int i = 0; i < 2*n-2; i++) {
      new_L.push_back(L[i]);
    }
    SegmentTree st(new_L);

    int perm[n];
    for (int i = 0; i < n; i++) {
      scanf("%d", perm + i);
      perm[i]--;
    }
    bool solvable = true;
    for (int i = 0; i < n-1; i++) {
      int a = perm[i];
      int b = perm[i+1];
      if (H[a] >= H[b]) {
        int tmp = a;
        a = b;
        b = tmp;
      }
      int common = st.rmq(H[a], H[b]);
      int dist = L[H[a]] + L[H[b]] - 2*common;
      //printf("%d, %d, %d, %d\n", L[a] common, dist);
      if (dist > 3) {
        solvable = false;
        break;
      }
    }

    if (solvable)
      printf("1\n");
    else
      printf("0\n");
  }
}
