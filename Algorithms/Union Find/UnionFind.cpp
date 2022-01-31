#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

class UnionFind {
private: vi p, rank, size; int setCount;
public:
     UnionFind(int N) {
          p.assign(N, 0);
          rank.assign(N, 0);
          size.assign(N, 1);
          for (int i = 0; i < N; i++)
               p[i] = i;
          setCount = N;
     }
     int findSet(int i) {
          return (p[i] == i) ? i : (p[i] = findSet(p[i]));
     }
     bool isSameSet(int i, int j) {
          return findSet(i) == findSet(j);
     }
     void unionSet(int i, int j) {
          if (!isSameSet(i, j)) {
               int x = findSet(i);
               int y = findSet(j);
               if (rank[x] > rank[y])
                    p[y] = x;
               else {
                    p[x] = y;
                    if (rank[x] == rank[y])
                         rank[y]++;
               }
               setCount--;
               size[x] += size[y];
               size[y] = size[x];
          }
     }
     int numDisjointSets() {
          return setCount;
     }
     int sizeOfSet(int i) {
          return size[i];
     }
};
