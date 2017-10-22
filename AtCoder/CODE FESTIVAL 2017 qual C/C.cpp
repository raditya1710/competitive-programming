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
int jum[N + 5];
int main(){
  string s, ss = "";
  cin >> s;
  for(int i = 0;i < s.length(); ++i){
    if(s[i] != 'x'){
      ss += s[i];
    }
  }
  string sss = ss;
  reverse(sss.begin(), sss.end());
  if(ss != sss){
    puts("-1");
    return 0;
  }
  else if(ss == ""){
    puts("0");
    return 0;
  }
  else{    
    int len = (int) ss.length();
    int tengah = (int) ss.length() / 2;
    int before = 0, after = 0;
    int poi = 0;
    for(int i = 0;i < s.length(); ++i){
      if(s[i] == 'x'){
        if(poi == 0) before++;
        else if(poi == len) after++;
        else{
          if(poi > tengah){
            if(len & 1){
              jum[poi - tengah - 1]--;
            }
            else{
              jum[poi - tengah]--;
            }
          }
          else{
            jum[tengah - poi]++;
          }
        }
      }
      else poi++;
    }

    int ans = abs(after - before);
    for(int i = 1;i <= tengah; ++i){
      ans += abs(jum[i]);
    }
    if(len & 1) ans += abs(jum[0]);
    cout << ans << endl; 
  }
  return 0;
}
