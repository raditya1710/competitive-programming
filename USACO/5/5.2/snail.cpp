/*
ID: raditya1
TASK: snail
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

const int N = 120;
bool visit[N + 5][N + 5];
int n;
int maks = 0;
int m;
bool invalid[N + 5][N + 5];

pii nexts[N + 5][N + 5][4];
vector<pii> arah = {mp(-1, 0), mp(1, 0), mp(0, -1), mp(0, 1)};

inline void DEBUG(int x, int y, int total, int cases){
  fprintf(stderr, "TOTAL: %d, X : %d, Y : %d. CASE %d\n", total, x, y, cases);
  for(int i = 1; i <= n; ++i){
    for(int j = 1;j <= n; ++j){
      if(invalid[i][j]) fprintf(stderr, "#");
      else if(i == x && j == y) fprintf(stderr, "S");
      else if(visit[i][j]) fprintf(stderr, "*");
      else fprintf(stderr, ".");
    }
    fprintf(stderr, "\n");
  }
}

inline bool valid(int x, int y){
  return x > 0 && y > 0 && x <= n && y <= n && !invalid[x][y];
}

inline void precompute(){
  for(int i = 1;i <= n; ++i){
    for(int j = 1;j <= n; ++j){
      if(invalid[i][j]) continue;
      for(int k = 0;k < (int) arah.size(); ++k){
        pii now = mp(i + arah[k].fi, j + arah[k].se);
        while(valid(now.fi, now.se)){
          nexts[i][j][k] = now;
          now.fi += arah[k].fi;
          now.se += arah[k].se;
        }
      }
    }
  }
}
inline void dfs(int x, int y, int dir, int total){
  //fprintf(stderr, "IN DFS %d %d %d %d\n", x, y, dir, total);
  maks = max(maks, total);
  for(int i = 0;i < (int) arah.size(); ++i){
    if(i == dir || ((i ^ dir) == 0)) continue;
    pii nex = nexts[x][y][i];
    if(nex.fi == -1 && nex.se == -1) continue;
    bool bisa = true;
    switch(i){
      case 0: bisa = (nex.fi < x);
              for(int j = x - 1; j >= nex.fi && bisa; --j){
                if(visit[j][nex.se]){
                  maks = max(maks, total + x - j - 1);
                  //if(maks == total + x - j - 1) DEBUG(j - 1, nex.se, maks, 0);
                  bisa = false;
                }
              }
              if(bisa){
                for(int j = nex.fi;j < x; ++j) visit[j][nex.se] = 1;
                dfs(nex.fi, y, i, total + x - nex.fi);
                for(int j = nex.fi;j < x; ++j) visit[j][nex.se] = 0;
              }
              break;
      case 1: bisa = (x < nex.fi);
              for(int j = x + 1; j <= nex.fi && bisa; ++j){
                if(visit[j][nex.se]){
                  maks = max(maks, total + j - x - 1);
                  //if(maks == total + j - x - 1) DEBUG(j - 1, nex.se, maks, 1);
                  bisa = false;
                }
              }
              if(bisa){
                for(int j = x + 1; j <= nex.fi; ++j) visit[j][nex.se] = 1;
                dfs(nex.fi, y, i, total + nex.fi - x);
                for(int j = x + 1; j <= nex.fi; ++j) visit[j][nex.se] = 0;
              }
              break;
      case 2: bisa = (nex.se < y);
              for(int j = y - 1; j >= nex.se && bisa; --j){
                if(visit[nex.fi][j]){
                  maks = max(maks, total + y - j - 1);
                  //if(maks == total + y - j - 1) DEBUG(nex.fi, j - 1, maks, 2);
                  bisa = false;
                }
              }
              if(bisa){
                for(int j = nex.se;j < y; ++j) visit[nex.fi][j] = 1;
                dfs(x, nex.se, i, total + y - nex.se);
                for(int j = nex.se;j < y; ++j) visit[nex.fi][j] = 0;
              }
              break;
      case 3: bisa = (y < nex.se);
              for(int j = y + 1; j <= nex.se && bisa; ++j){
                if(visit[nex.fi][j]){
                  maks = max(maks, total + j - y - 1);
                  //if(maks == total + j - y - 1) DEBUG(nex.fi, j - 1, maks, 3);
                  bisa = false;
                }
              }
              if(bisa){
                for(int j = y + 1;j <= nex.se; ++j) visit[nex.fi][j] = 1;
                dfs(x, nex.se, i, total + nex.se - y);
                for(int j = y + 1;j <= nex.se; ++j) visit[nex.fi][j] = 0;
              }
              break;
      default : break;
    }
  }
  //fprintf(stderr, "OUT DFS %d %d %d %d\n", x, y, dir, total);
} 
int main(){
  freopen("snail.in", "r", stdin);
  freopen("snail.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for(int i = 0;i < m; ++i){
    char ar[10];
    scanf("%s", ar);
    int col = ar[0] - 'A' + 1;
    int len = strlen(ar);
    int row = 0;
    for(int j = 1; j < len; ++j) row *= 10, row += ar[j] - '0';
    invalid[row][col] = 1;
  }
  memset(nexts, -1, sizeof nexts);
  //fprintf(stderr, "next[0][0][0] : %d,%d\n", nexts[0][0][0].fi, nexts[0][0][0].se);
  precompute();
  visit[1][1] = 1;
  dfs(1, 1, 2, 1);
  dfs(1, 1, 1, 1);
  printf("%d\n", maks);
  fclose(stdin);  
  fclose(stdout);
  return 0;
}

/*
10 9 
A9 
B2 
C7 
D4 
F5 
G8 
H3 
I10 
J1
*/