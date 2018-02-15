 /*
ID: raditya1
TASK: range
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 250;
int pref[N + 1][N + 1];

int n;
string s;

int main(){
  freopen("range.in", "r", stdin);
  freopen("range.out", "w", stdout);
  ios::sync_with_stdio(false);
  cin >> n;
  for(int i = 1;i <= n; ++i){
    cin >> s;
    for(int j = 0;j < n; ++j){
      pref[i][j + 1] = pref[i][j] + pref[i - 1][j + 1] - pref[i - 1][j] + s[j] - '0';
    }
  }
  for(int i = 2;i <= n; ++i){
    int max_j, max_k;
    max_j = max_k = n - i;
    int sqr_i = i * i;
    int tot = 0;
    for(int j = 0; j <= max_j; ++j){
      for(int k = 0;k <= max_k; ++k){
        if(pref[j + i][k + i] - pref[j][k + i] - pref[j + i][k] + pref[j][k] == sqr_i) tot++;
      }
    }
    if(tot) printf("%d %d\n", i, tot);
  }
  fclose(stdin);
  fclose(stdout);
  return 0;
}