/*
ID: raditya1
TASK: fc
LANG: C++11              
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long LL;

#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 10000;

const double EPS = 1e-9;
const double PI = acos(-1);

// (POINT)
struct point {
  double x, y;
  point(double x = 0, double y = 0) : x(x), y(y) {}
  bool operator<(const point& p) const {
    if (fabs(x - p.x) > EPS)
      return x < p.x;
    return y < p.y;
  }
  bool operator==(const point& p) const {
    return (fabs(x - p.x) < EPS) && (fabs(y - p.y) < EPS);
  }
  point operator+(const point& p) const { return point(x+p.x, y+p.y);}
  point operator-(const point& p) const { return point(x-p.x, y-p.y);}
  point operator*(double s) const { return point(x*s, y*s);}
};

double dist(const point& a, const point& b) {
  return hypot(a.x - b.x, a.y - b.y);
}

// rotate p by theta degrees CCW w.r.t origin(0, 0)
point rotate(const point& p, double tetha) {
  // rotate matrix R(theta0 = [cos(theta) -sin(theta)]
  //                          [sin(theta)  cos(theta)]
  double rad = tetha * PI / 180.0;
  return point(p.x*cos(rad) - p.y*sin(rad),
               p.x*sin(rad) + p.y*cos(rad));
}
double cross(const point& a, const point& b) {
  return a.x * b.y - a.y * b.x;
}
double dot(const point& a, const point& b) {
  return a.x * b.x + a.y * b.y;
}
double norm_sq(const point& p) {
  return dot(p, p);
}
// return 1 = ccw, 0 = colinear, -1 = cw
int ccw(const point& p, const point& q, const point& r) {
  point pq = q - p, pr = r-p;
  double crs = cross(pq, pr);
  if (fabs(crs) < EPS) return 0;
  return crs > 0 ? 1 : -1;
}
bool between(const point& p,const point& q,const point& r) {
  return ccw(p, q, r) == 0 && (p.x-q.x) * (r.x-q.x) < EPS && (p.y-q.y) * (r.y-q.y) < EPS;
}
// calculate angle between OA and OB
double angle(const point& a, const point& o, const point& b) {
  point oa = a-o, ob = b-o;
  return acos(dot(oa, ob) / sqrt(norm_sq(oa) * norm_sq(ob)));
}


// Graham’s Scan Algorithm
// need implement operator<,-,cross,ccw on Point’s library
double dist2(point a, point b) {// norm_sq(b - a)
  return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

bool collinear(const point& x, const point& a, const point& b){
  return ccw(x, a, b) == 0;
}

point pivot;
bool angle_cmp(point a, point b) {
  if(collinear(pivot, a, b))
    return dist2(a, pivot) < dist2(b, pivot);
  return ccw(pivot, a, b) > 0;
}

// hasil convexHull tidak siklik(P[0] != P.back())
void convexHull(vector<point> & P) {
  int i, j, n = (int) P.size();
  if(n < 3) {
    return;
  }
  int PO = 0;
  for(i = 1; i < n; i++) {
    if(P[i] < P[PO]) {
      PO = i;
    }
  }
  swap(P[0], P[PO]);
  pivot = P[0];
  sort(++P.begin(), P.end(), angle_cmp);
  // if point on boundary is included then uncomment this:
  // int k = (int)P.size()-1; while (k-1 > 0 && ccw(P[0], P[k-1], P.back()) == 0) k--;
  // reverse(P.begin() + k, P.end());
  vector<point> S;
  S.push_back(P[0]);
  S.push_back(P[1]);
  i = 2;
  while(i < n) {
    j = (int) S.size() - 1;
    // if point on boundary is included then ccw >= 0
    if(j < 1 || ccw(S[j-1], S[j], P[i]) > 0) S.push_back(P[i++]);
    else S.pop_back();
  }
  P = S;
}

vector<point> ar;
int n;
int main(){
  freopen("fc.in", "r", stdin);
  freopen("fc.out", "w", stdout);
  scanf("%d", &n);
  for(int i = 0;i < n; ++i) {
    double x, y;
    scanf("%lf%lf", &x, &y);
    ar.push_back(point(x,y));
  }
  convexHull(ar);
  // for(int i = 0;i < (int) ar.size(); ++i) fprintf(stderr, "%lf %lf\n", ar[i].x, ar[i].y);
  if(n <= 1) {
    puts("0.00");
  }
  else if(n == 2){
    printf("%.2lf\n", dist(ar[0], ar[1]));
  }
  else{
    double distall = 0;
    int len = (int) ar.size();
    for(int i = 0;i < (int)ar.size(); ++i){
      distall += dist(ar[i], ar[(i + 1) % len]);
    }
    printf("%.2lf\n", distall); 
  }
  fclose(stdin);  
  fclose(stdout);
  return 0;
}
