/*
ID: raditya1
TASK: fence
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 500, M = 1 << 10;

vector<int> ve[N + 1];
int degree[N + 1];
int m;
int start = -1;
vector<int> hasil;
int last[N + 1];
int total[N + 1][N + 1], cnt[N + 1][N + 1];

inline void dfs(int now){
  for(int i = 0;i < (int)ve[now].size(); ++i){
    int u = ve[now][i];
    if(cnt[now][u] == total[now][u]) continue;
    cnt[now][u]++;
    cnt[u][now]++;
    dfs(u);
  }
  hasil.pb(now);
}

int main(){
  freopen("fence.in", "r", stdin);
  freopen("fence.out", "w", stdout);
  scanf("%d", &m);
  for(int i = 0;i < m; ++i){
    int x, y;
    scanf("%d%d", &x, &y);
    ve[x].pb(y);
    ve[y].pb(x);
    total[x][y]++;
    total[y][x]++;
  }
  start = 1;
  for(int i = 1;i <= N; ++i) {
    sort(ve[i].begin(), ve[i].end());
    degree[i] = (int) ve[i].size();
  }
  for(int i = 1;i <= N; ++i){
    if(degree[i] & 1) {
      start = i;break;
    }
  } 
  dfs(start);
  reverse(hasil.begin(), hasil.end());
  for(int i = 0;i < (int)hasil.size(); ++i) printf("%d\n", hasil[i]);
  fclose(stdin);
  fclose(stdout);
  return 0;
}