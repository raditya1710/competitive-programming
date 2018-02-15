 /*
ID: raditya1
TASK: camelot
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int R = 30, C = 26, INF = 1e9;

int r, c;

pii king;
vector<pii> knights;
void input(){
  cin >> r >> c;
  char cc; int x;
  cin >> cc >> x;
  king = mp(x - 1, cc - 'A');
  while(cin >> cc >> x){
    knights.pb(mp(x - 1, cc - 'A'));
  }
}

pii arah[] = {mp(-1, -2), mp(-2, -1), mp(-2, 1), mp(-1, 2), mp(1, 2), mp(2, 1), mp(2, -1), mp(1, -2)};

int dist[R + 5][C + 5][R + 5][C + 5];
bool visible[R + 5][C + 5];

bool valid(int x, int y){
  return x >= 0 && y >= 0 && x < r && y < c;
}

queue<pii> q;

int distking(pii x, pii y){
  return max(abs(x.fi - y.fi), abs(x.se - y.se));
}

void precompute(){
  memset(dist, -1, sizeof dist);
  for(int i = 0;i < r;++i){
    for(int j = 0;j < c; ++j){
      dist[i][j][i][j] = 0;
      q.push(mp(i, j));
      while(!q.empty()){
        pii tmp = q.front();q.pop();
        for(int x = 0; x < 8; ++x){
          pii now = mp(tmp.fi + arah[x].fi, tmp.se + arah[x].se);
          if(valid(now.fi, now.se) && dist[i][j][now.fi][now.se] == -1){
            dist[i][j][now.fi][now.se] = dist[i][j][tmp.fi][tmp.se] + 1;
            q.push(now);
          }
        }
      }
    }
  }
}

int main(){
  freopen("camelot.in", "r", stdin);
  freopen("camelot.out", "w", stdout);
  ios::sync_with_stdio(false);
  input();  
  precompute();
  int min_dist = INF;
  for(int i = 0;i < r; ++i){
    for(int j = 0;j < c; ++j){
      bool bisa = true;
      int dist_total = 0;
      for(int k = 0;k < (int)knights.size() && bisa; ++k){
        if(dist[knights[k].fi][knights[k].se][i][j] == -1) bisa = false;
        else dist_total += dist[knights[k].fi][knights[k].se][i][j];
      }
      if(!bisa) continue;
      min_dist = min(min_dist, dist_total + distking(king, mp(i,j)));

      for(int k = 0;k < (int)knights.size(); ++k){
        int dist_now = dist_total - dist[knights[k].fi][knights[k].se][i][j];
        for(int l = king.fi - 3;l <= king.fi + 3; ++l){
          if(l < 0 || l >= r) continue;
          for(int m = king.se - 3;m <= king.se + 3; ++m){
            if(m < 0 || m >= c) continue;
            if(dist[knights[k].fi][knights[k].se][l][m] != -1 && dist[l][m][i][j] != -1){
              min_dist = min(min_dist, dist_now + dist[knights[k].fi][knights[k].se][l][m] + dist[l][m][i][j] + distking(king, mp(l,m)));
            }
          }
        }
      }
    }
  }

  cout << min_dist << endl;
  fclose(stdin);
  fclose(stdout);
  return 0;
}