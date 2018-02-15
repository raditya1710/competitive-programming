 /*
ID: raditya1
TASK: shopping
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 5, S = 99, MAX_DP = 10000, INF = 1e9;

struct offer {
  int n;
  int p;
  int code[N + 1];
  int amount[N + 1];
} O[S + 1];

struct product {
  int code;
  int k;
  int p;

  bool operator<(const product &p) const {
    return code < p.code;
  }
  bool operator>(const product &p) const {
    return code > p.code;
  }
  bool operator==(const product &p) const {
    return code == p.code;
  }
} P[N + 1];
int s, n;

int dp[MAX_DP + 5];
int mult[N + 1];

int conv_to_int(const vector<int>& v){
  int ans = 0;
  for(int i = 0;i < n; ++i) ans += v[i] * mult[i];
  return ans;
}

vector<int> conv_to_vector(int idx){
  vector<int> ans;
  for(int i = 0, sisaidx = idx;i < n; ++i){
    ans.pb(sisaidx / mult[i]);
    sisaidx %= mult[i];
  }
  return ans;
}

int main(){
  freopen("shopping.in", "r", stdin);
  freopen("shopping.out", "w", stdout);
  scanf("%d", &s);
  for(int i = 0;i < s; ++i){
    scanf("%d", &O[i].n);
    for(int j = 0;j < O[i].n; ++j){
      scanf("%d%d", &O[i].code[j], &O[i].amount[j]);
    }
    scanf("%d", &O[i].p);
  }
  scanf("%d", &n);
  for(int i = 0;i < n; ++i) scanf("%d%d%d", &P[i].code, &P[i].k, &P[i].p);
  sort(P, P + n);
  for(int i = 0;i < s; ++i){
    for(int j = 0;j < O[i].n; ++j){
      for(int k = 0;k < n; ++k){
        if(O[i].code[j] == P[k].code) {
          O[i].code[j] = k;
          break;
        }
      }
    }
  }
  int mult_now = 1;
  for(int i = n - 1;i >= 0; --i){
    mult[i] = mult_now;
    mult_now *= (P[i].k + 1);
  }
  dp[0] = 0;
  for(int i = 1; i < mult_now; ++i){
    dp[i] = INF;
    vector<int> v_now = conv_to_vector(i);
    
    /* Individual */
    for(int j = 0;j < n; ++j){
      if(v_now[j]){
        dp[i] = min(dp[i], dp[i - mult[j]] + P[j].p);
      }
    }

    for(int j = 0;j < s; ++j){
      vector<int> v_tmp = v_now;
      bool bisa = true;
      for(int k = 0;k < O[j].n && bisa; ++k){
        int idx = O[j].code[k];
        int amount = O[j].amount[k];
        if(v_tmp[idx] >= amount){
          v_tmp[idx] -= amount;
        } 
        else{
          bisa = false;
        }
      }
      if(bisa){
        int idx_now = conv_to_int(v_tmp);
        dp[i] = min(dp[i], dp[idx_now] + O[j].p);
      }
    }
  }
  printf("%d\n", dp[mult_now - 1]);
  fclose(stdin);
  fclose(stdout);
  return 0;
}