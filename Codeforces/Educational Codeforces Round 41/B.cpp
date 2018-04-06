#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int MOD = 1e9 + 7;
const int INF = 1e9;
const double EPS = 1e-9;
const double pi = acos(-1);
const int N = 1e5;
int ar[N + 5];
int br[N + 5];
int n, k;

int pref[N + 5];
int prefB[N + 5];

int main(){
  scanf("%d%d", &n, &k);
  for(int i = 1;i <= n; ++i) scanf("%d", &ar[i]);
  for(int i = 1;i <= n; ++i) scanf("%d", &br[i]);

  int totnow = 0;
  int maks = 0;
  for(int i = 1;i <= n; ++i){
    pref[i] = pref[i - 1] + ar[i];
    prefB[i] = prefB[i - 1];
    if(br[i]) {
      prefB[i] += ar[i];
      totnow += ar[i];
    } 
  }
  maks = max(maks, totnow);
  for(int i = k; i <= n; ++i){
    maks = max(maks, pref[i] - pref[i - k] - (prefB[i] - prefB[i - k]) + totnow);
  }

  printf("%d\n", maks);

  return 0;
}