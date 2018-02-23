/*
ID: raditya1
TASK: theme
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

const int N = 5000;
const int INF = 1e9;
const int PRIM = 229;
const LL MOD = 252097800623LL;
const int TRANS = 88;

int n;
int ar[N + 5];
LL kali[N + 5];
int selisih[N + 5];
map<LL, bool> MAP;
queue<LL> q;
bool coba(int piv){
  //fprintf(stderr, "COBA %d\n", piv);
  int x = piv - 1;
  while(!q.empty()) q.pop();
  MAP.clear();
  LL hash = 0;
  for(int i = 1; i <= x; ++i){
    hash *= PRIM;
    hash += selisih[i];
    hash %= MOD;
  }
  //fprintf(stderr, "PUSH %lld\n", hash);
  q.push(hash);
  int nextpiv = x + piv;
  for(int i = piv;i < nextpiv; ++i){
    hash -= selisih[i - x] * kali[x - 1];
    hash %= MOD;
    if(hash < 0) hash += MOD;
    hash *= PRIM;
    hash += selisih[i];
    hash %= MOD;
    q.push(hash);
    //fprintf(stderr, "PUSH %lld\n", hash);
  }
  for(int i = nextpiv; i < n; ++i){
    LL fir = q.front(); q.pop();
    //fprintf(stderr, "POP %lld\n", fir);
    MAP[fir] = true;
    hash -= selisih[i - x] * kali[x - 1];
    hash %= MOD;
    if(hash < 0) hash += MOD;
    hash *= PRIM;
    hash += selisih[i];
    hash %= MOD;
    if(MAP.count(hash)) {
      //fprintf(stderr, "\n");
      return true;
    }
    q.push(hash);
    //fprintf(stderr, "PUSH %lld\n", hash);
  }
  //fprintf(stderr, "\n");
  return false;
}

int main(){
  freopen("theme.in", "r", stdin);
  freopen("theme.out", "w", stdout);
  kali[0] = 1;
  for(int i = 1;i <= N; ++i){
    kali[i] = kali[i - 1] * PRIM % MOD;
  }
  scanf("%d", &n);
  for(int i = 1;i <= n; ++i){
    scanf("%d", &ar[i]);
  }
  for(int i = 1;i < n; ++i){
    selisih[i] = ar[i] - ar[i + 1] + TRANS;
  }

  int ans = 0;
  int mins = 5;
  int maks = n / 2;
  while(mins <= maks){
    int piv = (mins + maks) >> 1;
    if(coba(piv)){
      mins = piv + 1;
      ans = piv;
    }
    else{
      maks = piv - 1;
    }
  }
  printf("%d\n", ans);
  fclose(stdin);  
  fclose(stdout);
  return 0;
}