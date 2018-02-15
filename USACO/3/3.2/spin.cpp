/*
ID: raditya1
TASK: spin
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 5, W = 5, MAX_DEGREE = 360;

struct wheel{
  pii wedge[W];
  int wedges;
  int speed;

} ar[N + 1];

bool inside(int start, int angle, int degree){
  int last = start + angle;
  if((degree >= start && degree <= last) || (degree + MAX_DEGREE >= start && degree + MAX_DEGREE <= last)){
    return true;
  }
  return false;
}

int main(){
  freopen("spin.in", "r", stdin);
  freopen("spin.out", "w", stdout);
  for(int i = 0;i < N; ++i) {
    scanf("%d%d", &ar[i].speed, &ar[i].wedges);
    for(int j = 0;j < ar[i].wedges; ++j) scanf("%d%d", &ar[i].wedge[j].fi, &ar[i].wedge[j].se);
  }
  int ans = -1;
  for(int i = 0;i < MAX_DEGREE && ans == -1; ++i){
    for(int ii = 0; ii < MAX_DEGREE && ans == -1; ++ii){
      int total = 0;
      for(int j = 0;j < N; ++j){
        bool bisa = false;
        for(int k = 0;k < ar[j].wedges && !bisa; ++k){
          int start_now = (ar[j].wedge[k].fi + i * ar[j].speed) % MAX_DEGREE;
          bisa |= inside(start_now, ar[j].wedge[k].se, ii);
        }
        total += bisa;
      }
      if(total == N){
        ans = i;
      }
    }
  }

  if(ans == -1) printf("none\n");
  else printf("%d\n", ans);

  fclose(stdin);
  fclose(stdout);
  return 0;
}