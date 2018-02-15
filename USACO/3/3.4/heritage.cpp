/*
ID: raditya1
TASK: heritage
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
string s[2];

int idx = 0, len;
struct node{
  char c;
  node* l;
  node* r;
  node() {}

};

node* root;

inline void dfs(int l, int r, node* now){
  if(l > r) return;
  if(l == r){
    now->c = s[0][l];
    idx++;
    return;
  }
  int idx_now = -1;
  for(int i = l;i <= r && idx_now == -1; ++i){
    if(s[1][idx] == s[0][i]) idx_now = i;
  }
  now->c = s[1][idx];
  idx++;
  if(idx_now > l){
    now->l = new node();
    dfs(l, idx_now - 1, now->l);
  }
  if(idx_now < r){
    now->r = new node();
    dfs(idx_now + 1, r, now->r);
  }
}

inline void dfs2(node* now){
  if(now->l) dfs2(now->l);
  if(now->r) dfs2(now->r);
  printf("%c", now->c);
}

int main(){
  freopen("heritage.in", "r", stdin);
  freopen("heritage.out", "w", stdout);
  cin >> s[0] >> s[1];
  len = s[0].length();
  root = new node();
  dfs(0, len - 1, root);
  dfs2(root);
  puts("");
  fclose(stdin);
  fclose(stdout);
  return 0;
}