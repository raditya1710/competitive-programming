/*
ID: raditya1
TASK: starry
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

const int N = 100;
const int INF = 1e9;
char ar[N + 5][N + 5];
int n, m;

struct cluster{
  int s_x, s_y;
  int f_x, f_y;
  int r, c;
  int idx = -1;
  int cnt = 0;
  vector<pii> v;
};

bool visit[N + 5][N + 5];

vector<pii> arah = {mp(-1,-1), mp(-1, 0), mp(-1, 1), mp(0, 1), mp(1, 1), mp(1, 0), mp(1, -1), mp(0, -1)};
vector<cluster> ve;

bool valid(int x, int y){
  return x >= 0 && y >= 0 && x < n && y < m && !visit[x][y];
}

inline void dfs(cluster &c, int x, int y){
  c.s_x = min(c.s_x, x);
  c.s_y = min(c.s_y, y);
  c.f_x = max(c.f_x, x);
  c.f_y = max(c.f_y, y);
  visit[x][y] = 1;
  c.v.pb(mp(x, y));
  c.cnt++;
  for(int i = 0;i < (int) arah.size(); ++i){
    int nowx = x + arah[i].fi;
    int nowy = y + arah[i].se;
    if(valid(nowx, nowy) && ar[nowx][nowy] == '1'){
      dfs(c, nowx, nowy);
    }
  }
}

pii trans(const pii &x){
  return mp(x.se, x.fi);
}

inline bool coba(const cluster&A, const cluster &B, int idx, bool transpose){
  int cnt = A.cnt;
  vector<pii> tempA;
  vector<pii> tempB;
  for(int i = 0;i < cnt; ++i){
    pii Anow = A.v[i];
    pii Bnow;
    switch(idx){
      case 0 : Bnow = B.v[i]; break;
      case 1 : Bnow = mp(B.v[i].fi, B.c - B.v[i].se - 1);break;
      case 2 : Bnow = mp(B.r - B.v[i].fi - 1, B.v[i].se); break;
      case 3 : Bnow = mp(B.r - B.v[i].fi - 1, B.c - B.v[i].se - 1); break;
      default : break;
    }
    if(transpose) Bnow = trans(Bnow);
    tempA.push_back(Anow);
    tempB.push_back(Bnow);
  }
  sort(tempA.begin(), tempA.end());
  sort(tempB.begin(), tempB.end());
  for(int i = 0; i < cnt; ++i){
    if(tempA[i] != tempB[i]) return false;
  }
  return true;
}

inline bool similar(const cluster& A, const cluster &B){
  if(A.cnt != B.cnt) return false;
  if(A.r == B.r && A.c == B.c){
    for(int i = 0;i < 4; ++i){
      if(coba(A, B, i, 0)) return true;
    }
  }
  if(A.r == B.c && A.c == B.r){
    for(int i = 0;i < 4; ++i){
      if(coba(A, B, i, 1)) return true;
    }
  }
  return false;
}
  
int main(){
  freopen("starry.in", "r", stdin);
  freopen("starry.out", "w", stdout);
  scanf("%d%d", &m, &n);
  for(int i = 0;i < n; ++i) scanf("%s", ar[i]);
  for(int i = 0;i < n; ++i){
    for(int j = 0;j < m; ++j){
      if(ar[i][j] == '1' && !visit[i][j]){
        cluster c;
        c.s_x = c.s_y = INF;
        c.f_x = c.f_y = -INF;
        dfs(c, i,j);
        c.r = c.f_x - c.s_x + 1;
        c.c = c.f_y - c.s_y + 1;
        for(int k = 0;k < c.cnt; ++k){
          c.v[k].fi -= c.s_x;
          c.v[k].se -= c.s_y;
        }
        ve.push_back(c);
      }
    }
  }
  int len = (int)ve.size();
  //fprintf(stderr, "SIZE %d\n", len);
  int curidx = 0;
  for(int i = 0;i < len; ++i){
    if(ve[i].idx != -1) continue;
    ve[i].idx = curidx;
    for(int j = i + 1;j < len; ++j){
      if(similar(ve[i], ve[j])) {
        ve[j].idx = curidx;
        //fprintf(stderr, "SIMILAR %d %d\n", i, j);
      }
    }
    curidx++;
  }
  for(int i = 0;i < len; ++i){
    const cluster& c = ve[i];
    for(int j = 0;j < (int) c.v.size(); ++j){
      const pii& now = c.v[j];
      ar[now.fi + c.s_x][now.se + c.s_y] = c.idx + 'a';
    }
  }

  for(int i = 0;i < n; ++i) puts(ar[i]);
  fclose(stdin);  
  fclose(stdout);
  return 0;
}
