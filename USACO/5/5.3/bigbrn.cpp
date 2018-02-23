/*
ID: raditya1
TASK: bigbrn
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

const int N = 1000;
bool ada[N + 5][N + 5];
int pref[N + 5][N + 5];
int n, m;

inline bool coba(int x){
  int sqr = x * x;
  for(int i = x; i <= n; ++i){
    for(int j = x; j <= n; ++j){
      if(pref[i][j] - pref[i - x][j] - pref[i][j - x] + pref[i - x][j - x] == sqr) return true;
    } 
  }
  return false;
}

int main(){
  freopen("bigbrn.in", "r", stdin);
  freopen("bigbrn.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for(int i = 1;i <= m; ++i){
    int x, y;
    scanf("%d%d", &x, &y);
    ada[x][y] = 1;
  }
  for(int i = 1;i <= n; ++i){
    for(int j = 1;j <= n; ++j){
      pref[i][j] = pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1] + !ada[i][j];
    }
  }
  int ans = 0;
  int mins = 1;
  int maks = n;
  while(mins <= maks){
    int piv = (mins + maks) >> 1;
    if(coba(piv)) {
      ans = piv;
      mins = piv + 1;
    }
    else{
      maks = piv - 1;
    }
  }
  printf("%d\n", ans);
  fclose(stdin);  
  fclose(stdout);
  return 0;
}