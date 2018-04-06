#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int MOD = 1e9 + 7;
const int INF = 1e9;
const double EPS = 1e-9;
const double pi = acos(-1);
const int N = 1e5;
pii point[N + 5];
pii bagi[N + 5];
int n;
map<pii, int> MAP;
bool valid[N + 5];

pii ret(pii grad){
  int gcd = __gcd(abs(grad.fi), abs(grad.se));
  pii ans;
  if(grad.fi == 0) ans = mp(0, 1);
  else if(grad.se == 0) ans = mp(1, 0);
  else{
    ans = mp(abs(grad.fi) / gcd, abs(grad.se) / gcd);
    bool minus = (grad.fi < 0) ^ (grad.se < 0);
    if(minus) ans.fi *= -1;
  }
  return ans;
}

int main(){
  scanf("%d", &n);
  for(int i = 0;i < n; ++i) scanf("%d%d", &point[i].fi, &point[i].se);

  if(n <= 4) {
    printf("YES\n");
    return 0;
  }

  sort(point, point + n);
  
  bool ketemu = false;
  for(int loop = 0; loop < 3 && !ketemu; ++loop){
    MAP.clear();
    pii pointnow = point[loop];
    for(int i = 0;i < n; ++i){
      point[i].fi -= pointnow.fi;
      point[i].se -= pointnow.se;
    }
    for(int i = 0;i < n; ++i){ 
      if(i == loop) continue;
      bagi[i] = ret(point[i]);
      MAP[bagi[i]]++;
    }
    for(int i = 0;i < n && !ketemu; ++i){
      if(i == loop) continue;
      if(MAP[bagi[i]] >= 2){
        ketemu = true;
        valid[loop] = true;
        for(int j = 0;j < n; ++j){
          if(j == loop) continue;
          if(bagi[j] == bagi[i]) valid[j] = true;
        }
      }
    }
  }
  
  if(!ketemu){
    puts("NO");
    return 0;
  }

  //fprintf(stderr, "LEWAT\n");
  vector<pii> v;
  for(int i = 0;i < n; ++i){
    if(!valid[i]) v.push_back(point[i]);
  }

  if(v.size() <= 2){
    puts("YES");
    return 0;
  }
  sort(v.begin(), v.end());
  for(int i = 1;i < (int) v.size(); ++i){
    v[i].fi -= v[0].fi;
    v[i].se -= v[0].se;
  }
  pii bagis = ret(v[1]);
  for(int i = 2;i < (int) v.size(); ++i){
    pii baginow = ret(v[i]);
    if(baginow != bagis) {
      puts("NO");
      return 0;
    }
  } 

  puts("YES");
  return 0;
}