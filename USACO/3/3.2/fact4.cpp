/*
ID: raditya1
TASK: fact4
LANG: C++                 
*/

#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9;
int main(){
  freopen("fact4.in", "r", stdin);
  freopen("fact4.out", "w", stdout);

  int n;
  cin >> n;
  long long now = 1;
  for(int i = 1;i <= n; ++i){
    now *= i;
    while(now % 10 == 0) now /= 10;
    now %= MOD;
  }
  cout << now % 10 << endl;
  fclose(stdin);
  fclose(stdout);
  return 0;
}