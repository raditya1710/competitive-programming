/*
ID: raditya1
TASK: nuggets
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
const int N = 10, MAX = 1e5, MAXC = 256;
int n;
int ar[N + 5];
bool bisa[MAX + 5];
int main(){
  freopen("nuggets.in", "r", stdin);
  freopen("nuggets.out", "w", stdout);
  scanf("%d", &n);
  int fpb = 0;
  for(int i = 0;i < n; ++i) {
    scanf("%d", &ar[i]);
    fpb = __gcd(ar[i], fpb);
  }

  sort(ar, ar + n);
  if(fpb > 1 || ar[0] == 1){
    puts("0");
    return 0;
  }
  int cnt = 0, last = -1;
  for(int i = 0;i < n; ++i) bisa[ar[i]] = 1;
  for(int i = 1;i <= MAX; ++i){
    if(bisa[i]){
      cnt++;
      for(int j = 0;j < n; ++j) bisa[i + ar[j]] = 1;
    }
    else{
      last = i;
      cnt = 0;
    }
    if(cnt >= MAXC) break;
  }
  printf("%d\n", last);
  fclose(stdin);  
  fclose(stdout);
  return 0;
}