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

string ar[N + 5];
int n;
int tot[26];
int main(){
  cin >> n;
  for(int i = 0;i < n; ++i){
    cin >> ar[i];
    tot[ar[i][0] - 'a']++;
  }
  int banyak = 0;
  for(int i = 0;i < n; ++i){
    bool bisa = true;
    tot[ar[i][0] - 'a']--;
    for(int j = 0;j < ar[i].size(); ++j){
      if(tot[ar[i][j] - 'a'] == 0) bisa = false;
      tot[ar[i][j] - 'a']--;
    }

    for(int j = 0;j < ar[i].size(); ++j){
      tot[ar[i][j] - 'a']++;
    }
    tot[ar[i][0] - 'a']++;
    banyak += bisa;
  }
  printf("%d\n", banyak);
  return 0;
}