/*
ID: raditya1
TASK: race3
LANG: C++11              
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 50;
int n = -1;

vector<int> ve[N + 5];
vector<pii> elist;
vector<int> AP;
vector<int> split;
bool adj[N + 5][N + 5];
bool adj2[N + 5][N + 5];

bool visit[N + 5];
bool visit2[N + 5];
inline void findAP(){
  for(int i = 1;i < n; ++i){
    for(int j = 0;j < (int) elist.size(); ++j) adj[elist[j].fi][elist[j].se] = false;
    memset(visit, 0, sizeof visit);
    memset(visit2, 0, sizeof visit2);
    queue<int> q;
    q.push(0);
    visit[0] = true;
    while(!q.empty()){
      int idx = q.front(); q.pop();
      if(idx == i) continue;
      for(int j = 0;j < (int)ve[idx].size(); ++j){
        int to = ve[idx][j];
        adj[idx][to] = true;
        if(!visit[to]){
          visit[to] = true;
          q.push(to);
        }
      }
    }
    if(!visit[n]) {
      AP.push_back(i);

      //Check if this is splitting point or not
      for(int j = 0;j < (int) elist.size(); ++j) adj2[elist[j].fi][elist[j].se] = false;
      q.push(i);
      visit2[i] = true;
      while(!q.empty()){
        int idx = q.front(); q.pop();
        for(int j = 0;j < (int)ve[idx].size(); ++j){
          int to = ve[idx][j];
          adj2[idx][to] = true;
          if(!visit2[to]){
            visit2[to] = true;
            q.push(to);
          }
        }
      }
      bool splitting = true;
      for(int j = 0;j < (int)elist.size() && splitting; ++j){
        if(adj[elist[j].fi][elist[j].se] && adj2[elist[j].fi][elist[j].se]) splitting = false;
      }
      for(int j = 0;j <= n && splitting; ++j){
        if(i == j) continue;
        if(visit[j] && visit2[j]) splitting = false;
      }
      if(splitting) split.push_back(i);
    }
  }
}

int main(){
  freopen("race3.in", "r", stdin);
  freopen("race3.out", "w", stdout);
  int x;
  while(scanf("%d", &x), x != -1){
    n++;
    while(x != -2){
      ve[n].pb(x);
      elist.pb(mp(n, x));
      scanf("%d", &x);
    }
  }
  findAP();
  printf("%d", (int) AP.size());
  for(int i = 0; i < (int) AP.size(); ++i) printf(" %d", AP[i]);
  puts("");

  printf("%d", (int) split.size());
  for(int i = 0;i < (int) split.size(); ++i) printf(" %d", split[i]);
  puts("");
  fclose(stdin);  
  fclose(stdout);
  return 0;
}
