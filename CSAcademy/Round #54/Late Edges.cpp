#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<int,pii> piii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 5e3;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;
const int INF = 2e9;
priority_queue<piii, vector<piii>, greater<piii> > pq;
int n, m;
vector<pii> ve[N + 5];
int dist[N + 5][2];
int main(){
  ios::sync_with_stdio(false);
  cin >> n >> m;
  for(int i = 0;i < m; ++i){
    int x, y, c;
    cin >> x >> y >> c;
    ve[x].pb(mp(y, c));
    ve[y].pb(mp(x, c));
  }
  for(int i = 0;i <= n; ++i) for(int j = 0;j < 2; ++j) dist[i][j] = INF;
  dist[1][0] = 0;
  pq.push(mp(0, mp(1, 0)));
  while(!pq.empty()){
    piii top = pq.top(); pq.pop();
    if(dist[top.se.fi][top.se.se] < top.fi) continue;
    for(int i = 0;i < (int)ve[top.se.fi].size(); ++i){
      pii now = ve[top.se.fi][i];
      if(now.se > top.fi){
        int selisih = now.se - top.se.se;
        int time_next = now.se + 1;
        if(selisih & 1){
          time_next++;
        } 
        if(dist[now.fi][top.se.se ^ 1] > time_next){
          dist[now.fi][top.se.se ^ 1] = time_next;
          pq.push(mp(time_next, mp(now.fi, top.se.se ^ 1)));
        }
      }
      else{
        if(dist[now.fi][top.se.se ^ 1] > top.fi + 1){
          dist[now.fi][top.se.se ^ 1] = top.fi + 1;
          pq.push(mp(top.fi + 1, mp(now.fi, top.se.se ^ 1)));
        }
      }
    }
  }
  int dists = INF;
  dists = min(dists, dist[n][0]);
  dists = min(dists, dist[n][1]);
  printf("%d\n", (dists == INF) ? -1 : dists);
  return 0;
}