/*
ID: raditya1
TASK: stamps
LANG: C++                 
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <cstring>

using namespace std;
const int N = 50, K = 200, MAX = 2e6;
int dp[MAX + 5];
int ar[N + 5];

int n, k;
int main(){
  freopen("stamps.in", "r", stdin);
  freopen("stamps.out", "w", stdout);
  scanf("%d%d", &k, &n);
  for(int i = 0;i < n; ++i) scanf("%d", &ar[i]);
  sort(ar, ar + n);
  if(ar[0] != 1){
    puts("1");
  }
  else {  
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    for(int i = 1;i <= MAX; ++i){
      for(int j = 0;j < n; ++j){
        int x = i - ar[j];
        if(x >= 0 && dp[x] != -1 && dp[x] != k){
          if(dp[i] == -1) dp[i] = dp[x] + 1;
          else dp[i] = min(dp[i], dp[x] + 1);
        }
      }
    }
    int ans = MAX + 1;
    for(int i = 1;i <= MAX && ans == MAX + 1; ++i){
      if(dp[i] == -1) ans = i;
    }
    printf("%d\n", ans - 1);
  }

  
  fclose(stdin);
  fclose(stdout);
  return 0;
}