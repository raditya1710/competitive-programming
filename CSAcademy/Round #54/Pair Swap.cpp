#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 1e5;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;

int n, k;
int ar[N + 5];


priority_queue<pii> pq;

int main(){
  ios::sync_with_stdio(false);
  cin >> n >> k;
  k = min(k, n - 1);
  for(int i = 0; i < n; ++i) cin >> ar[i];
  bool udah = false;
  for(int i = 1; i <= k; ++i){
    pq.push(mp(-ar[i], i));
  }
  for(int i = 0, j = k + 1; i < n - 1 && !udah; ++i, ++j){
    while(pq.top().se <= i) pq.pop();
    if(-(pq.top().fi) < ar[i]){
      swap(ar[i], ar[pq.top().se]);
      udah = true;
    }
    else{
      if(j < n) pq.push(mp(-ar[j], j));
    }
  }

  for(int i = 0;i < n; ++i) printf("%d%c", ar[i], i == n - 1 ? '\n' : ' ');
  return 0;
}