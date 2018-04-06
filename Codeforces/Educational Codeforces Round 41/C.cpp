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

const int N = 100;
char cboard[4][N + 5][N + 5];
int board[4][N + 5][N + 5];
int n;
int urut[] = {0, 1, 2, 3};
int main(){
  scanf("%d", &n);
  for(int k = 0;k < 4; ++k){
    for(int i = 0;i < n; ++i){
      scanf("%s", cboard[k][i]);
      for(int j = 0;j < n; ++j){
        board[k][i][j] = cboard[k][i][j] - '0';
      }
    }
  }
  int mins = INF;
  do{
    int tot2 = 0;
    int tot = 0;
    for(int k = 0;k < 4; ++k){
      for(int i = 0;i < n; ++i){
        for(int j = 0;j < n; ++j){
          int expect = ((i * n + j) & 1) ^ (k & 1);
          tot += expect ^ board[urut[k]][i][j];
          tot2 += (!expect) ^ board[urut[k]][i][j];
        }
      }
    }
    mins = min(mins, tot);
    mins = min(mins, tot2);
  }
  while(next_permutation(urut, urut + 4));

  printf("%d\n", mins);

  return 0;
}