/*
ID: raditya1
TASK: butter
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 500, P = 800, C = 1450;

int n, p, c;
int ar[N + 5];
int dist[N + 5][P + 5];
priority_queue<pii, vector<pii>, greater<pii> > pq;
vector<pii> ve[P + 5];
int main(){
  freopen("butter.in", "r", stdin);
  freopen("butter.out", "w", stdout);
  scanf("%d%d%d", &n, &p, &c);
  for(int i = 0;i < n; ++i) scanf("%d", &ar[i]);
  for(int i = 0;i < c; ++i){
    int x, y, cost;
    scanf("%d%d%d", &x, &y, &cost);
    ve[x].pb(mp(y, cost));
    ve[y].pb(mp(x, cost));
  }
  memset(dist, -1, sizeof dist);
  for(int i = 0;i < n; ++i){
    dist[i][ar[i]] = 0;
    pq.push(mp(0, ar[i]));
    while(!pq.empty()){
      pii top = pq.top();pq.pop();

      if(dist[i][top.se] != top.fi) continue;

      for(int j = 0;j < (int)ve[top.se].size(); ++j){
        pii u = ve[top.se][j];
        if(dist[i][u.fi] == -1 || dist[i][u.fi] > top.fi + u.se){
          dist[i][u.fi] = top.fi + u.se;
          pq.push(mp(dist[i][u.fi], u.fi));
        }
      }
    }
  }
  int min_dist = -1;
  for(int i = 1;i <= P; ++i){
    int total_dist = 0;
    bool possible = true;
    for(int j = 0;j < n && possible; ++j){
      if(dist[j][i] == -1) possible = false;
      else total_dist += dist[j][i];
    }
    if(possible && (min_dist == -1 || min_dist > total_dist)){
      min_dist = total_dist;
    }
  }

  printf("%d\n", min_dist);
  fclose(stdin);
  fclose(stdout);
  return 0;
}