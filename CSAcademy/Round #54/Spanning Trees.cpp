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
int main(){
  cin >> n >> k;

  if(n >= 2 && n <= 3 && k == 0){
    puts("-1");
    return 0;
  }
  else if(n == 1){
    puts("0");
    return 0;
  }
  int m = (n - 1) << 1;
  m -= k;
  cout << m << endl;
  if(k == 0){
    for(int i = 1;i <= n - 1; ++i){
      printf("%d %d %d\n", i, i + 1, i);
    }
    printf("%d %d %d\n", 1, n - 1, n);
    for(int i = 1;i <= n - 2; ++i) printf("%d %d %d\n", n, n - i - 1, n + i);
  }
  else{
    for(int i = 1;i <= k; ++i){
      printf("%d %d %d\n", i, i + 1, 1000000 + i);
    }
    for(int i = 1;i < n - k; ++i){
      printf("%d %d %d\n", 1, k + i + 1, i);
      printf("%d %d %d\n", k + 1, k + i + 1, 2000000 + i);
    }
  }
  return 0;
}