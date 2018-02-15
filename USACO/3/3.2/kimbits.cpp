/*
ID: raditya1
TASK: kimbits
LANG: C++                 
*/

#include <bits/stdc++.h>
using namespace std;
const int BIT = 31;

int C[BIT + 1][BIT + 1];

const int MOD = 1e9;

void precompute(){
  C[0][0] = 1;
  for(int i = 1;i <= BIT; ++i){
    C[i][0] = 1;
    for(int j = 1;j <= i; ++j){
      C[i][j] = C[i - 1][j] + C[i - 1][j - 1];
    }
  }
}

int coba(int places, int ones){
  int res = 0;
  for(int i = 0;i <= min(places, ones); ++i){
    res += C[places][i];
  }
  return res;
}

int main(){
  freopen("kimbits.in", "r", stdin);
  freopen("kimbits.out", "w", stdout);

  int n, l, k;
  unsigned kk;
  cin >> n >> l >> kk;
  --kk;
  k = (int) kk;

  precompute();
  int sisal = l, sisak = k;
  for(int i = n - 1;i >= 0; --i){
    int below = coba(i, sisal);
    if(sisak < below){
      printf("0");
    }
    else{
      sisak -= below;
      printf("1");
      sisal--;
    }
  }

  puts("");
  fclose(stdin);
  fclose(stdout);
  return 0;
}