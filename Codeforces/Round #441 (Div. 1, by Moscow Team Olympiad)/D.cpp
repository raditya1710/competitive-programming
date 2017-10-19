#include <bits/stdc++.h>
using namespace std;
const int N = 2e5;
int segtree[(1 << 19) + 5];
int segmax[(1 << 19) + 5];

int ar[N + 5];
int n;

inline void build(int l, int r, int idx){
  if(l == r){
    segtree[idx] = ar[l];
    segmax[idx] = l;
    return;
  }
  int m = (l + r) >> 1;
  int chd = idx << 1;
  build(l, m, chd);
  build(m + 1, r, chd | 1);
  segtree[idx] = segtree[chd] | segtree[chd | 1];
  segmax[idx] = ar[segmax[chd]] > ar[segmax[chd | 1]] ? segmax[chd] : segmax[chd | 1];
}

inline int query(int l, int r, int ql, int qr, int idx){
  if(l > qr || r < ql) return 0;
  if(l >= ql && r <= qr) return segtree[idx];

  int m = (l + r) >> 1;
  int chd = idx << 1;
  return query(l, m, ql, qr, chd) | query(m + 1, r, ql, qr, chd | 1);
}

inline int querymax(int l, int r, int ql, int qr, int idx){
  if(l >= ql && r <= qr) return segmax[idx];
  int m = (l + r) >> 1;
  int chd = idx << 1;
  int maks = -1;
  if(m >= ql){
    int ans = querymax(l, m, ql, qr, chd);
    if(maks == -1 || ar[maks] < ar[ans]){
      maks = ans;
    }
  }
  if(m + 1 <= qr){
    int ans = querymax(m + 1, r, ql, qr, chd | 1);
    if(maks == -1 || ar[maks] < ar[ans]){
      maks = ans;
    }
  }
  return maks;
}

inline int cariL(int x){
  int l = 0;
  int r = x;
  int ans = x;
  while(l <= r){
    int piv = (l + r) >> 1;
    if(query(0, n - 1, piv, x, 1) == ar[x]){
      ans = piv;
      r = piv - 1;
    }
    else{
      l = piv + 1;
    }
  }
  return ans;
}

inline int cariR(int x){
  int l = x;
  int r = n - 1;
  int ans = x;
  while(l <= r){
    int piv = (l + r) >> 1;
    if(query(0, n - 1, x, piv, 1) == ar[x]){
      ans = piv;
      l = piv + 1;
    }
    else{
      r = piv - 1;
    }
  }
  return ans;
}


inline long long rek(int l, int r){
  if(l > r) return 0;
  if(l == r) return 1;
  int idxmax = querymax(0, n - 1, l, r, 1);
  int ansL = max(l, cariL(idxmax));
  int ansR = min(cariR(idxmax), r);
  long long ans = 1LL * (idxmax - ansL + 1) * (ansR - idxmax + 1);
  ans += rek(l, idxmax - 1) + rek(idxmax + 1, r);
  return ans;
}

int main(){
  scanf("%d", &n);
  for(int i = 0;i < n; ++i){
    scanf("%d", &ar[i]);
  }
  build(0, n - 1, 1);

  long long total = ((1LL * n * (n + 1)) >> 1) - rek(0, n - 1);
  printf("%lld\n", total);
  return 0;
}