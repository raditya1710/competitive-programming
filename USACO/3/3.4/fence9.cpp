/*
ID: raditya1
TASK: fence9
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const double EPS = 1e-9;
int n, m, p;

int main(){
  freopen("fence9.in", "r", stdin);
  freopen("fence9.out", "w", stdout);
  
  cin >> n >> m >> p;
  int total = 0;
  for(int i = 1;i < m; ++i){
    double kiri = 1.0 * i / m * n;
    double ceilkiri = ceil(kiri);
    if(ceilkiri - kiri < EPS) ceilkiri++;
    double kanan = p + 1.0 * i / m * (n - p);
    double floorkanan = floor(kanan);
    if(kanan - floorkanan < EPS) floorkanan--;
    int l = (int) (ceilkiri + 0.5);
    int r = (int) floorkanan;

    total += max(0, r - l + 1); 
  }

  printf("%d\n", total);
  fclose(stdin);
  fclose(stdout);
  return 0;
}