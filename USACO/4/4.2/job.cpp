/*
ID: raditya1
TASK: job
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
const int INF = 1e9;
int n, m1, m2;
int ar[N + 1], br[N + 1];

priority_queue<pii, vector<pii>, greater<pii> > pq;
vector<int> v;
vector<int> v2;
int totA = 0, totB = 0;
int main(){
  freopen("job.in", "r", stdin);
  freopen("job.out", "w", stdout);
  scanf("%d%d%d", &n, &m1, &m2);
  for(int i = 0;i < m1; ++i) scanf("%d", &ar[i]);
  for(int i = 0;i < m2; ++i) scanf("%d", &br[i]);
  sort(ar, ar + m1);
  sort(br, br + m2);
  for(int i = 0;i < m1; ++i) pq.push(mp(ar[i], i));
  for(int i = 0;i < n; ++i){
    pii top = pq.top(); pq.pop();
    v.push_back(top.fi);
    pq.push(mp(top.fi + ar[top.se], top.se));
  }
  while(!pq.empty()) pq.pop();
  totA = v.back();
  for(int i = 0;i < m2; ++i) pq.push(mp(br[i], i));
  for(int i = 0;i < n; ++i){
    pii top = pq.top(); pq.pop();
    v2.push_back(top.fi);
    pq.push(mp(top.fi + br[top.se], top.se));
  }
  while(!pq.empty()) pq.pop();
  reverse(v2.begin(), v2.end());
  for(int i = 0;i < n; ++i) totB = max(totB, v[i] + v2[i]);
  printf("%d %d\n", totA, totB);
  fclose(stdin);  
  fclose(stdout);
  return 0;
}
