/*
ID: raditya1
TASK: milk6
LANG: C++11              
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long LL;
typedef pair<pii,LL> piil;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int MAXN = 32;
const int M = 1000, MULTIPLIER = M * 2;
const LL INFL = 1000000000000000000LL;

LL G[MAXN + 5][MAXN + 5], rG[MAXN + 5][MAXN + 5];
bool dont[MAXN + 5][MAXN + 5];
int n, m;
int level[MAXN + 5];
vector<int> adj[MAXN + 5];

inline bool build_level_graph(int s, int t){
  memset(level, -1, sizeof level);
  level[s] = 0;
  queue<int> q;
  q.push(s);
  while(!q.empty()){
    int now = q.front(); q.pop();
    for(int i = 0;i < (int) adj[now].size(); ++i){
      int u = adj[now][i];
      if(level[u] == -1 && rG[now][u] > 0){
        level[u] = level[now] + 1;
        q.push(u);
      }
    }
  }
  return level[t] > 0;
}

inline LL sendflow(int u, int t, LL flow, int start[]){
  //fprintf(stderr, "sendflow(%d, %d, %lld), start[%d] : %d\n", u, t, flow, u, start[u]);
  if(u == t) return flow;
  for(; start[u] < (int)adj[u].size(); start[u]++){
    int v = adj[u][start[u]];
    //fprintf(stderr, "LOOP %d %d %d %d %lld\n", u, v, level[u], level[v], G[u][v]);
    if(rG[u][v] > 0 && level[v] == level[u] + 1){
      LL tempflow = sendflow(v, t, min(flow, rG[u][v]), start);
      if(tempflow > 0){
        rG[u][v] -= tempflow;
        rG[v][u] += tempflow;
        return tempflow;
      }
    }
  }
  return 0;
} 

inline LL DinicMaxFlow(int s, int t){
  LL totflow = 0;

  while(build_level_graph(s, t)){
    int *start = new int[MAXN + 5];
    for(int i = 0;i <= n; ++i) start[i] = 0;
    while(LL flow = sendflow(s, t, INFL, start)){
      totflow += flow;
      // fprintf(stderr, "%lld %lld\n", totflow, flow );
    }
    // fprintf(stderr, "TOTFLOW: %lld\n", totflow);
    delete [] start;
  }

  return totflow;
}

int visit[MAXN + 5];
inline void dfs(int now){
  visit[now] = 1;
  for(int i = 0;i < (int)adj[now].size(); ++i){
    int u = adj[now][i];
    if(!visit[u] && rG[now][u] > 0){
      dfs(u);
    }
  }
}

vector<int> cutidx;
vector<piil> edges; 

void init(){
  for(int i = 0;i < (int) edges.size(); ++i){
    int e = edges[i].fi.fi, s = edges[i].fi.se;
    rG[e][s] = G[e][s];
    rG[s][e] = G[s][e];
  }
}

int main(){
  freopen("milk6.in", "r", stdin);
  freopen("milk6.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for(int i = 1;i <= m; ++i){
    int s, e, c;
    scanf("%d%d%d", &s, &e, &c);
    adj[s].pb(e);
    adj[e].pb(s);
    LL f = 1LL * c * MULTIPLIER + 1;
    edges.pb(mp(mp(s, e), f));
    G[s][e] += f;
  }
  init();
  for(int i = 1;i <= n; ++i){
    sort(adj[i].begin(), adj[i].end());
    adj[i].resize(unique(adj[i].begin(), adj[i].end()) - adj[i].begin());
    // fprintf(stderr, "%d: %d\n", i, (int)adj[i].size());
  }
  LL maxflow = DinicMaxFlow(1, n);
  LL real_flow = maxflow / MULTIPLIER;
  int num_cut = (int)(maxflow % MULTIPLIER);

  for(int i = 0, idx_cut = 0;i < (int) edges.size() && idx_cut < num_cut; ++i){
    int u = edges[i].fi.fi;
    int v = edges[i].fi.se;
    LL f = edges[i].se;
    G[u][v] -= f;
    init();
    LL tempflow = DinicMaxFlow(1, n);
    if(tempflow + f == maxflow) {
      cutidx.push_back(i + 1);
      idx_cut++;
      maxflow -= f;
    }
    else G[u][v] += f;
  }

  fprintf(stderr, "%d %d\n", num_cut, (int) cutidx.size());
  assert(num_cut == (int) cutidx.size());
  printf("%lld %d\n", real_flow, num_cut);
  for(int i = 0;i < num_cut; ++i) printf("%d\n", cutidx[i]);

  fclose(stdin);  
  fclose(stdout);
  return 0;
}
