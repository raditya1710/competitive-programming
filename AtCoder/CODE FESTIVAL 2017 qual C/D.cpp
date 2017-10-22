#include <bits/stdc++.h>
using namespace std;
typedef long long LL;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back

const int N = 2e5;
const int MOD = 1e9 + 7;
const double EPS = 1e-9;
string s;
int n;
int ar[N + 5];
map<int, int> MAP;
int dp[N + 5];
int main(){
  cin >> s;
  n = (int) s.length();
  int xornow = 0;
  for(int i = 0;i < n; ++i){
    int idx = s[i] - 'a';
    xornow ^= (1 << idx);
    ar[i] = xornow;
  }
  MAP[0] = 0;
  for(int i = 0;i < n; ++i){
    int now = ar[i];
    dp[i] = -1;
    for(int j = 0;j < 26; ++j){
      int tmp = ar[i] ^ (1 << j);
      if(MAP.count(tmp)){
        int res = MAP[tmp] + 1;
        if(dp[i] == -1 || dp[i] > res){
          dp[i] = res;
        }
      }
    }
    if(MAP.count(ar[i])){
      int res = MAP[ar[i]] + 1;
      if(dp[i] == -1 || dp[i] > res){
        dp[i] = res;
      }
    }

    //printf("%d %d %d\n", i, ar[i], dp[i] );
    if(MAP.count(now)) MAP[now] = min(MAP[now], dp[i]);
    else MAP[now] = dp[i];
  }
  cout << dp[n - 1] << endl;
  return 0;
}