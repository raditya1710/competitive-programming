/*
ID: raditya1
TASK: ratios
LANG: C++                 
*/

#include <bits/stdc++.h>
using namespace std;
const int MAX = 100;

int ar[4][3][MAX + 1];
int ans[4] = {MAX, MAX, MAX, MAX};
int main(){
  freopen("ratios.in", "r", stdin);
  freopen("ratios.out", "w", stdout);
  for(int i = 0;i < 4; ++i) for(int j = 0;j < 3; ++j) cin >> ar[i][j][1];
  for(int i = 0;i < 4; ++i) for(int j = 0;j < 3; ++j) for(int k = 2; k <= MAX; ++k) ar[i][j][k] = k * ar[i][j][1];

  int sums = -1;
  for(int i = 0;i < MAX; ++i){
    for(int j = 0;j < MAX; ++j){
      for(int k = 0;k < MAX; ++k){
        if(i == 0 && j == 0 && k == 0) continue;
        int total[3] = {0, 0, 0};
        for(int l = 0;l < 3; ++l){
          total[l] = ar[1][l][i] + ar[2][l][j] + ar[3][l][k];
        }
        bool bisa = true;
        int kali = -1;
        for(int l = 0;l < 3 && bisa; ++l){
          if(ar[0][l][1] == 0){
            bisa &= (total[l] == 0);
          }
          else{
            if(total[l] % ar[0][l][1]) bisa = false;
            else if(kali == -1) kali = total[l] / ar[0][l][1];
            else bisa &= (kali == total[l] / ar[0][l][1]);
          }
        }
        if(bisa){
          if(i + j + k < ans[0] + ans[1] + ans[2]){
            ans[0] = i;
            ans[1] = j;
            ans[2] = k;
            ans[3] = kali;
          }
        }
      }
    }
  }
  if(ans[0] == MAX) puts("NONE");
  else printf("%d %d %d %d\n", ans[0], ans[1], ans[2], ans[3]);
  fclose(stdin);
  fclose(stdout);
  return 0;
}