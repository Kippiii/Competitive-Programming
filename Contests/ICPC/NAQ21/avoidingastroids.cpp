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

typedef ColVect Point;
struct Line {
   Point p;
   ColVect m;
};
struct Ray {
   Point start;
   ColVect dir;
   double radius;
};
struct LineSeg {
   Point end1;
   Point end2;
};

ColVect get_diff(ColVect v1, ColVect v2) {
   ColVect ans;
   for (int i = 0; i < 3; i++)
      ans.vec[i] = v1.vec[i] - v2.vec[i];
   return ans;
}

double magnitude(ColVect v) {
   double ans = 0;
   for (int i = 0; i < 3; i++)
      ans += v.vec[i]*v.vec[i];
   return sqrt(ans);
}

Line get_line(Ray r) {
   Line ans;
   ans.p = r.start;
   ans.m = r.dir;
   return ans;
}

Line get_line(LineSeg ls) {
   Line ans;
   ans.p = ls.end1;
   ans.m = get_diff(ls.end2, ls.end1);
   return ans;
}

double get_mult(Point p, Line l) {
   for (int i = 0; i < 3; i++)
      if (l.m.vec[i] != 0)
         return (p.vec[i] - l.p.vec[i]) / l.m.vec[i];
   return 0; //FAIL
}

ColVect cross_prod(ColVect v1, ColVect v2) {
   ColVect ans;
   ans.vec[0] = v1.vec[1]*v2.vec[2] - v1.vec[2]*v2.vec[1];
   ans.vec[1] = v1.vec[2]*v2.vec[0] - v1.vec[0]*v2.vec[2];
   ans.vec[2] = v1.vec[0]*v2.vec[1] - v1.vec[1]*v2.vec[0];
   return ans;
}

double dot_prod(ColVect v1, ColVect v2) {
   double ans;
   for (int i = 0; i < 3; i++)
      ans += v1.vec[i] * v2.vec[i];
   return ans;
}

ColVect proj(ColVect from, ColVect onto) {
   double mult = dot_prod(from, onto) / (magnitude(onto)*magnitude(onto));
   ColVect ans;
   for (int i = 0; i < 3; i++)
      ans.vec[i] = mult*onto.vec[i];
   return ans;
}

bool on_ray(Point p, Ray r) {
   return get_mult(p, get_line(r)) >= 0;
}

bool on_segment(Point p, LineSeg ls) {
   double mult = get_mult(p, get_line(ls));
   return mult >= 0 && mult <= 1;
}

Point intersect(Line l1, Line l2) {
   AugMatrix system;
   for (int i = 0; i < 3; i++) {
      system.mat[i][0] = l1.m.vec[i];
      system.mat[i][1] = -l2.m.vec[i];
      system.mat[i][2] = l2.p.vec[i] - l1.p.vec[i];
   }
   ColVect sol = gauss_elim(system, 2, 3);

   Point ans;
   for (int i = 0; i < 3; i++)
      ans.vec[i] = l1.p.vec[i] + sol.vec[0]*l1.m.vec[i];
   return ans;
}

bool on_line(Point p, Line l) {
   double mult = get_mult(p, l);
   for (int i = 0; i < 3; i++)
      if (l.p.vec[i] + mult*l.m.vec[i] != p.vec[i])
         return false;
   return true;
}

Point closest_point(Point p, Line l) {
   if (on_line(p, l))
      return p;

   Point ans;
   ColVect projection = proj(get_diff(p, l.p), l.m);
   for (int i = 0; i < 3; i++)
      ans.vec[i] = l.p.vec[i] + projection.vec[i];
   return ans;
}

pair<Point, Point> get_closest(Line l1, Line l2) {
   ColVect norm = cross_prod(l1.m, l2.m);
   // Special case when lines are parallel
   if (magnitude(norm) == 0) {
      pair<Point, Point> ans;
      ans.first = l1.p;
      ans.second = closest_point(l1.p, l2);
      return ans;
   }

   AugMatrix system;
   for (int i = 0; i < 3; i++) {
      system.mat[i][0] = l1.m.vec[i];
      system.mat[i][1] = -l2.m.vec[i];
      system.mat[i][2] = norm.vec[i];
      system.mat[i][3] = l2.p.vec[i] - l1.p.vec[i];
   }
   ColVect solution = gauss_elim(system, 3, 3);

   pair<Point, Point> ans;
   for (int i = 0; i < 3; i++) {
      ans.first.vec[i] = l1.p.vec[i] + solution.vec[0]*l1.m.vec[i];
      ans.second.vec[i] = l2.p.vec[i] + solution.vec[1]*l2.m.vec[i];
   }

   return ans;
}

double calc_dist(Point p1, Point p2) {
   double ans = 0;
   for (int i = 0; i < 3; i++)
      ans += (p1.vec[i] - p2.vec[i])*(p1.vec[i] - p2.vec[i]);
   return ans;
}

double calc_dist(Point p, Ray r) {
   Point closest = closest_point(p, get_line(r));
   if (on_ray(closest, r))
      return calc_dist(closest, p);
   return calc_dist(p, r.start);
}

double calc_dist(Point p, LineSeg ls) {
   Point closest = closest_point(p, get_line(ls));
   if (on_segment(closest, ls))
      return calc_dist(closest, p);
   return min(calc_dist(p, ls.end1), calc_dist(p, ls.end2));
}

double calc_dist(Ray r, LineSeg ls) {
   // Find closest points between infinite lines
   Line ray_line = get_line(r);
   Line seg_line = get_line(ls);
   pair<Point, Point> points = get_closest(ray_line, seg_line);
   Point ray_point = points.first;
   Point seg_point = points.second;

   // Checks if this occurs at right place
   if (on_ray(ray_point, r) && on_segment(seg_point, ls))
      return calc_dist(ray_point, seg_point);

   // Dealing with edge cases
   double ans = calc_dist(r.start, ls);
   ans = min(ans, calc_dist(ls.end1, r));
   ans = min(ans, calc_dist(ls.end2, r));
   return ans;
}

int main() {
   LineSeg ship_path;
   int n;
   scanf("%lf%lf%lf%lf%lf%lf%d", &ship_path.end1.vec[0], &ship_path.end1.vec[1], &ship_path.end1.vec[2], &ship_path.end2.vec[0], &ship_path.end2.vec[1], &ship_path.end2.vec[2], &n);
   Ray astroids[n];
   for (int i = 0; i < n; i++) {
      int m;
      scanf("%lf%lf%lf%lf%lf%lf%d", &astroids[i].start.vec[0], &astroids[i].start.vec[1], &astroids[i].start.vec[2], &astroids[i].dir.vec[0], &astroids[i].dir.vec[1], &astroids[i].dir.vec[2], &m);
      double radius = -1;
      for (int j = 0; j < m; j++) {
         Point p;
         scanf("%lf%lf%lf", &p.vec[0], &p.vec[1], &p.vec[2]);
         radius = max(radius, calc_dist(astroids[i].start, p));
      }
      astroids[i].radius = radius;
   }

   bool reachable = true;

   for (int i = 0; i < n; i++) {
      double dist = calc_dist(astroids[i], ship_path);

      reachable &= dist > astroids[i].radius + pow(10, -6);
   }

   if (reachable)
      printf("Go\n");
   else
      printf("Surrender\n");
}
