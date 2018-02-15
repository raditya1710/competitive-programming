 /*
ID: raditya1
TASK: game1
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 100;
int n;
int ar[N + 1];
int dp[N + 1][N + 1];

int main(){
  freopen("game1.in", "r", stdin);
  freopen("game1.out", "w", stdout);
  ios::sync_with_stdio(false);
  int total = 0;
  cin >> n;
  for(int i = 0;i < n; ++i){
    cin >> ar[i];
    total += ar[i];
    if(n & 1) dp[i][i] = ar[i];
    else dp[i][i] = -ar[i];
  } 
  for(int i = 1;i < n; ++i){
    int max_j = n - i;
    for(int j = 0;j < max_j; ++j){
      int dp1 = dp[j][j + i - 1];
      int dp2 = dp[j + 1][j + i];
      if((i ^ n) & 1){
        if(dp1 + ar[j + i] < dp2 + ar[j]){
          dp[j][i + j] = dp2 + ar[j];
        }
        else{
          dp[j][i + j] = dp1 + ar[j + i];
        }
      }
      else{
        if(dp1 - ar[j + i] < dp2 - ar[j]){
          dp[j][i + j] = dp1 - ar[j + i];
        }
        else{
          dp[j][i + j] = dp2 - ar[j];
        }
      }
      //printf("dp[%d][%d] : %d\n", j, i + j, dp[j][i + j]);
    }    
  }
  int A = (total + dp[0][n - 1]) >> 1;
  printf("%d %d\n", A, total - A);
  fclose(stdin);
  fclose(stdout);
  return 0;
}
