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
const int N = 2e5;
int BIT[N + 5]; 
int ar[N + 5];
int n;

int update(int x, int val){
  for(int i = x; i <= n; i += (i & -i)){
    BIT[i] += val;
  }
}

int query(int x){
  int ans = 0;
  for(int i = x; i > 0; i -= (i & -i)){
    ans += BIT[i];
  } 
  return ans;
}
priority_queue<pii, vector<pii>, greater<pii> > pq;
int main(){
  scanf("%d", &n);
  for(int i = 1;i <= n; ++i) {
    scanf("%d", &ar[i]);
    update(i, 1);
    pq.push(mp(ar[i], i));
  }

  LL tot = 0;
  for(int i = 1; i < n; ++i){
    while(!pq.empty() && pq.top().fi < i) {
      pii tmp = pq.top();pq.pop();
      update(tmp.se, -1);
    }
    if(ar[i] > i){
      tot += query(min(ar[i], n)) - query(i);
      //fprintf(stderr, "TOT : %lld\n", tot);
    }
  }

  printf("%lld\n", tot);
  return 0;
}