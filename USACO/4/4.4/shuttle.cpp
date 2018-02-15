/*
ID: raditya1
TASK: shuttle
LANG: C++11              
 */

#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
const int N = 12;
int n;
vector<int> ans;
int main(){
  freopen("shuttle.in", "r", stdin);
  freopen("shuttle.out", "w", stdout);
  scanf("%d", &n);
  int dir = 0;
  int lnow = n + 1;
  int rnow = n + 1;
  while(lnow > 1){
    lnow--;
    rnow++;
    if(dir == 0){ // left -> right
      for(int i = lnow; i <= rnow; i += 2){
        ans.push_back(i);
      }
    }
    else{
      for(int i = rnow; i >= lnow; i -= 2){
        ans.push_back(i);
      }
    }
    dir ^= 1;
  }
  while(lnow <= n){
    lnow++;
    rnow--;
    if(dir == 0){ // left -> right
      for(int i = lnow; i <= rnow; i += 2){
        ans.push_back(i);
      }
    }
    else{
      for(int i = rnow; i >= lnow; i -= 2){
        ans.push_back(i);
      }
    }
    dir ^= 1;
  }
  int len = (int) ans.size();
  for(int i = 0;i < len; ++i){
    if(i && (i % 20) == 0) puts("");
    else if(i) printf(" ");
    printf("%d", ans[i]);
  }
  puts("");
  fclose(stdin);  
  fclose(stdout);
  return 0;
}
