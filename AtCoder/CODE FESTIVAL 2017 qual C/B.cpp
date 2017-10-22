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
int main(){
  int n;
  scanf("%d", &n);
  int now = 1;
  int bisa = 1;
  for(int i = 0;i < n; ++i){
    int x;
    scanf("%d", &x);
    now *= 3;
    if(!(x & 1)){
      bisa <<= 1;
    }
  }
  printf("%d\n", now - bisa);
  return 0;
}
