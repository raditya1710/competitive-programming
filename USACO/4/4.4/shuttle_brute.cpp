/*
ID: raditya1
TASK: shuttle
LANG: C++11              
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
const int N = 12;
int n;
map<pii, pii> MAP;

//W = 1;
//B = 0;
vector<int> sol;
queue<pii> q;
int main(){
  freopen("shuttle.in", "r", stdin);
  freopen("shuttle.out", "w", stdout);
  scanf("%d", &n);

  pii s = mp((1 << n) - 1, n);
  pii t = mp((1 << (2 * n)) - (1 << n), n);
  //cerr << s.fi << " " << s.se << "; " << t.fi << " " << t.se << endl;
  pii ans = mp(-1, -1);
  q.push(s);
  MAP[s] = mp(-1, -1);
  while(!q.empty()){
    pii top = q.front(); q.pop();
    if(top == t) {
      ans = top;
      break;
    }
    
    if(top.se > 1){
      int lef = top.se - 2;
      int rig = top.se - 1;
      int bitlef = top.fi & (1 << lef);
      int bitrig = top.fi & (1 << rig);
      //fprintf(stderr, "MASUK CUY %d %d %d %d %d\n", top.fi, lef, rig, bitlef, bitrig);
      if(!bitlef + !bitrig == 1){ //they are different
        pii topnew = mp(top.fi - bitlef - bitrig + ((!bitlef) << lef) + ((!bitrig) << rig), top.se - 2);
        //fprintf(stderr, "MASUK DONG %d %d\n", topnew.fi, topnew.se);
        if(!MAP.count(topnew)){
          MAP[topnew] = top;
          q.push(topnew);
        }
      }
    }
    if(top.se > 0){
      pii topnew = mp(top.fi, top.se - 1);
      if(!MAP.count(topnew)){
        MAP[topnew] = top;
        q.push(topnew);
      }
    }
    if(top.se < 2 * n - 1){ // tiati sama ini
      int lef = top.se;
      int rig = top.se + 1;
      int bitlef = top.fi & (1 << lef);
      int bitrig = top.fi & (1 << rig);
      if(!bitlef + !bitrig == 1){ //they are different
        pii topnew = mp(top.fi - bitlef - bitrig + ((!bitlef) << lef) + ((!bitrig) << rig), top.se + 2);
        if(!MAP.count(topnew)){
          MAP[topnew] = top;
          q.push(topnew);
        }
      }
    }
    if(top.se < 2 * n){ // tiati sama ini
      pii topnew = mp(top.fi, top.se + 1);
      if(!MAP.count(topnew)){
        MAP[topnew] = top;
        q.push(topnew);
      }
    }
  }

  while(MAP.count(ans) && MAP[ans] != mp(-1, -1)){
    sol.push_back(ans.se);
    ans = MAP[ans];
  }

  reverse(sol.begin(), sol.end());
  int len = (int) sol.size();
  for(int i = 0;i < len; ++i){
    if(i && (i % 20) == 0) puts("");
    else if(i) printf(" ");
    printf("%d", sol[i] + 1);
  }
  puts("");
  fclose(stdin);  
  fclose(stdout);
  return 0;
}
