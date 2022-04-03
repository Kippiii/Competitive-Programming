#include <bits/stdc++.h>

using namespace std;

#define dd pair<long double, long double>
#define vdd vector<dd>

#define ERROR 0.000001

dd search_edge(vdd &vertices, int left_vert);
int find_edge(vdd &vertices);
int examine_edge(vdd &vertices, int left_vert);
long double get_area(vdd &vertices, int start, int end);

double total_area;

int main() {
   int n;
   scanf("%d", &n);
   vdd vertices;
   for (int i = 0; i < n; i++) {
      long double x, y;
      scanf("%Lf%Lf", &x, &y);
      vertices.push_back(dd(x, y));
   }
   reverse(vertices.begin()+1, vertices.end());
   total_area = get_area(vertices, 0, n-1);

   int left_vert = find_edge(vertices);
   dd ans = search_edge(vertices, left_vert);
   printf("%Lf %Lf\n", ans.first, ans.second);
}

dd search_edge(vdd &vertices, int left_vert) {
   //printf("%d\n", left_vert);
   //TODO Check vertices
   long double left_x = vertices[left_vert].first;
   long double left_y = vertices[left_vert].second;
   long double right_x = vertices[left_vert+1].first;
   long double right_y = vertices[left_vert+1].second;
   vertices.insert(vertices.begin()+left_vert+1, dd(0.0, 0.0));

   //printf("%Lf, %Lf, %Lf, %Lf\n", left_x, left_y, right_x, right_y);

   while (true) {
      long double mid_x = (left_x + right_x) / 2.0;
      long double mid_y = (left_y + right_y) / 2.0;
      //printf("%Lf, %Lf\n", mid_x, mid_y);
      vertices[left_vert+1] = dd(mid_x, mid_y);
      long double left_area = get_area(vertices, 0, left_vert+1);
      long double right_area = total_area - left_area;
      //printf("%Lf, %Lf\n", left_area, right_area);
      if (abs(left_area - right_area) < ERROR)
         return vertices[left_vert+1];
      if (left_area < right_area) {
         left_x = mid_x;
         left_y = mid_y;
      } else {
         right_x = mid_x;
         right_y = mid_y;
      }
   }

   assert(false);
   return dd(0, 0);
}

int find_edge(vdd &vertices) {
   int low = 1;
   int high = (int) vertices.size() - 2;
   int mid = (low + high) / 2;
   while (low < high) {
      mid = (low + high) / 2;
      int comp = examine_edge(vertices, mid);
      if (comp == 0)
         break;
      if (comp < 0)
         low = mid + 1;
      else
         high = mid - 1;
   }
   if (examine_edge(vertices, mid) != 0)
      mid = (low + high) / 2;
   assert(examine_edge(vertices, mid) == 0);
   return mid;
}

int examine_edge(vdd &vertices, int left_vert) {
   int left_info = -1;
   int right_info = 1;
   if (left_vert > 1) {
      long double left_area = get_area(vertices, 0, left_vert);
      long double right_area = total_area - left_area;
      left_info = left_area < right_area ? -1 : 1;
   }
   if (left_vert+1 < (int) vertices.size()-2) {
      long double left_area = get_area(vertices, 0, left_vert+1);
      long double right_area = total_area - left_area;
      right_info = left_area < right_area ? -1 : 1;
   }
   assert(left_info <= right_info);
   if (left_info == right_info)
      return left_info;
   return 0;
}

long double get_area(vdd &vertices, int start, int end) {
   long double sum1 = 0;
   long double sum2 = 0;
   for (int i = start; i < end; i++) {
      sum1 += vertices[i].first * vertices[i+1].second;
      sum2 += vertices[i].second * vertices[i+1].first;
   }
   sum1 += vertices[end].first*vertices[start].second;
   sum2 += vertices[end].second*vertices[start].first;
   return abs(sum1 - sum2) / 2;
}
