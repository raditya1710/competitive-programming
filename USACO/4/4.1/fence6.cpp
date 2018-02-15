/*
ID: raditya1
TASK: fence6
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 100, INF = 1e9;
int n;

int idxnow = 0;

struct edge{
  int len;
  vector<int> vkiri;
  vector<int> vkanan;
  int nkiri;
  int nkanan;
} E[N + 1];

vector<pii> ve[N + 1];
int num[N + 1][2];
int dist[N + 5];

priority_queue<pii, vector<pii>, greater<pii> > pq;
bool invalid[N + 1][N + 1];
int idxcase[N + 1][N + 1];
int main(){
  freopen("fence6.in", "r", stdin);
  freopen("fence6.out", "w", stdout);
  scanf("%d", &n);
  memset(idxcase, -1, sizeof idxcase);
  memset(num, -1, sizeof num);
  for(int i = 0;i < n; ++i){
    int x;
    scanf("%d", &x);
    scanf("%d%d%d", &E[x].len, &E[x].nkiri, &E[x].nkanan);
    for(int j = 0;j < E[x].nkiri; ++j){
      int idx;
      scanf("%d", &idx);
      E[x].vkiri.pb(idx);
      idxcase[idx][x] = 0;
    }
    for(int j = 0;j < E[x].nkanan; ++j){
      int idx;
      scanf("%d", &idx);
      E[x].vkanan.pb(idx);
      idxcase[idx][x] = 1;
    }
    sort(E[x].vkiri.begin(), E[x].vkiri.end());
    sort(E[x].vkanan.begin(), E[x].vkanan.end());
  }
  for(int i = 1;i <= n; ++i){
    int idxkiri = -1, idxkanan = -1;
    for(int j = 0;j < (int)E[i].vkiri.size() && idxkiri == -1; ++j){
      int u = E[i].vkiri[j];
      if(num[u][idxcase[i][u]] != -1){
        idxkiri = num[u][idxcase[i][u]];
      }
    }
    if(idxkiri == -1){
      idxkiri = idxnow;
      idxnow++;
    }

    for(int j = 0;j < (int)E[i].vkanan.size() && idxkanan == -1; ++j){
      int u = E[i].vkanan[j];
      if(num[u][idxcase[i][u]] != -1){
        idxkanan = num[u][idxcase[i][u]];
      }
      if(idxkanan == -1){
        idxkanan = idxnow;
        idxnow++;
      }
    }

    num[i][0] = idxkiri;
    num[i][1] = idxkanan;

  }

  for(int i = 1;i <= n; ++i){
    ve[num[i][0]].pb(mp(num[i][1], E[i].len));
    ve[num[i][1]].pb(mp(num[i][0], E[i].len));
    //printf("EDGE %d: %d %d\n",i, num[i][0], num[i][1]);
  }
  int mindist = INF;
  for(int e = 1;e <= n; ++e){
    fill(dist, dist + n + 1, INF);
    while(!pq.empty()) pq.pop();
    int start = num[e][0];
    int fin = num[e][1];
    dist[start] = 0;
    for(int i = 0;i < (int)ve[start].size(); ++i){
      pii u = ve[start][i];
      if(u.fi == fin) continue;
      dist[u.fi] = u.se;
      pq.push(mp(u.se, u.fi));
    }
    while(!pq.empty()){
      pii top = pq.top();pq.pop();
      if(top.fi != dist[top.se]) continue;
      if(top.se == fin){
        mindist = min(mindist, top.fi + E[e].len);
        break;
      }
      for(int i = 0;i < (int)ve[top.se].size(); ++i){
        pii u = ve[top.se][i];
        if(dist[u.fi] > dist[top.se] + u.se){
          dist[u.fi] = dist[top.se] + u.se;
          pq.push(mp(dist[u.fi], u.fi));
        }
      }
    }
  }
  printf("%d\n", mindist);

  fclose(stdin);  
  fclose(stdout);
  return 0;
}