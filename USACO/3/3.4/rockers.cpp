/*
ID: raditya1
TASK: rockers
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 20;
int n, t, m;
int ar[N + 1];
int main(){
  freopen("rockers.in", "r", stdin);
  freopen("rockers.out", "w", stdout);
  cin >> n >> t >> m;
  for(int i = 0;i < n; ++i) cin >> ar[i];
  int maks = 0;
  for(int i = 1;i < (1 << n); ++i){
    if(__builtin_popcount(i) <= maks) continue;
    int now = 1;
    int tot = 0;
    bool bisa = true;
    for(int j = 0;j < n && bisa && now <= m; ++j){
      if(i & (1 << j)){
        if(ar[j] > t) bisa = false;
        if(tot + ar[j] > t){
          now++;
          tot = ar[j];
        }
        else{
          tot += ar[j];
        }
      }
    }
    if(bisa && now <= m) maks = max(maks, __builtin_popcount(i));
  }
  cout << maks << endl;
  fclose(stdin);
  fclose(stdout);
  return 0;
}