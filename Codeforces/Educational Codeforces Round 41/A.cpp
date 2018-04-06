#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int MOD = 1e9 + 7;
const int INF = 1e9;
const LL INFL = 1e18;
const double EPS = 1e-9;
const double pi = acos(-1);
int n, m;
const int N = 1000;
int cnt[N + 5];

int main(){
  scanf("%d%d", &n, &m);
  for(int i = 0;i < m; ++i){
    int x;
    scanf("%d", &x);
    cnt[x]++;
  }
  int mins = m;
  for(int i = 1;i <= n; ++i) mins = min(mins, cnt[i]);

  printf("%d\n", mins);
  return 0;
}