/*
ID: raditya1
TASK: frameup
LANG: C++11              
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 30;

char s[N + 5][N + 5];
struct elem{
  char ar[N + 5][N + 5];
  vector<char> urut;
  vector<char> sisa;

  elem& operator=(const elem& e){
    for(int i = 0;i <= N; ++i) for(int j = 0;j <= N; ++j) ar[i][j] = e.ar[i][j];
    urut = e.urut;
    sisa = e.sisa;
    return (*this);
  }
};

int n, m;

vector<char> lis;
vector<vector<char> > ans;

pii upperleft[1 << 8];
pii bottomright[1 << 8];

queue<elem> q;

inline void generate_unique_chars(){
  for(int i = 0;i < n; ++i){
    for(int j = 0;j < m; ++j){
      if(s[i][j] != '.') lis.pb(s[i][j]);
    }
  }
  sort(lis.begin(), lis.end());
  lis.resize(unique(lis.begin(), lis.end()) - lis.begin());
  fill(upperleft, upperleft + (1 << 8), mp(N, N));
  fill(bottomright, bottomright + (1 << 8), mp(-1, -1));

  for(int i = 0;i < n; ++i){
    for(int j = 0;j < m; ++j){
      if(s[i][j] != '.'){
        char c = s[i][j];
        upperleft[c].fi = min(upperleft[c].fi, i);
        upperleft[c].se = min(upperleft[c].se, j);
        bottomright[c].fi = max(bottomright[c].fi, i);
        bottomright[c].se = max(bottomright[c].se, j);
      }
    }
  }
}

bool bisa(char c, const elem& e){
  int ans = -4;
  for(int i = upperleft[c].fi; i <= bottomright[c].fi; ++i) {
    char c1 = e.ar[i][upperleft[c].se];
    char c2 = e.ar[i][bottomright[c].se];
    ans += ((c1 == c) || (c1 == '*'));
    ans += ((c2 == c) || (c2 == '*'));
  }

  for(int i = upperleft[c].se; i <= bottomright[c].se; ++i) {
    char c1 = e.ar[upperleft[c].fi][i];
    char c2 = e.ar[bottomright[c].fi][i];
    ans += ((c1 == c) || (c1 == '*'));
    ans += ((c2 == c) || (c2 == '*'));
  }
  return ans == (bottomright[c].fi - upperleft[c].fi + bottomright[c].se - upperleft[c].se) * 2;
}

void removechar(char c, elem&e){
  for(int i = upperleft[c].fi; i <= bottomright[c].fi; ++i) {
    e.ar[i][upperleft[c].se] = '*';
    e.ar[i][bottomright[c].se] = '*';
  }
  for(int i = upperleft[c].se; i <= bottomright[c].se; ++i) {
    e.ar[upperleft[c].fi][i] = '*';
    e.ar[bottomright[c].fi][i] = '*';
  }
}

int main(){
  freopen("frameup.in", "r", stdin);
  freopen("frameup.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for(int i = 0;i < n; ++i) scanf("%s", s[i]);

  generate_unique_chars();
  elem init;
  for(int i = 0;i < n; ++i) for(int j = 0;j < m; ++j) init.ar[i][j] = s[i][j];
  init.urut.clear();
  init.sisa = lis;
  q.push(init);
  while(!q.empty()){
    elem top = q.front(); q.pop();
    // DEBUG
    // fprintf(stderr, "MULAI\n");
    // for(int i = 0;i < n; ++i) fprintf(stderr, "%s\n", top.ar[i]);
    // END OF DEBUG
    if(top.sisa.size() == 0){
      ans.push_back(top.urut);
      continue;
    }
    for(int i = 0;i < (int) top.sisa.size(); ++i){
      char c = top.sisa[i];
      if(bisa(c, top)){
        elem now = top;
        now.urut.push_back(c);
        now.sisa.erase(now.sisa.begin() + i);
        removechar(c, now);
        q.push(now);
      }
    }
  }

  for(int i = 0;i < (int) ans.size(); ++i){
    reverse(ans[i].begin(), ans[i].end());
  }
  sort(ans.begin(), ans.end());
  for(int i = 0;i < (int) ans.size(); ++i){
    for(int j = 0;j < (int) ans[i].size(); ++j) printf("%c", ans[i][j]);
    puts("");
  }

  fclose(stdin);
  fclose(stdout);
  return 0;
}
