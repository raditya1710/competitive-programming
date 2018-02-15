/*
ID: raditya1
TASK: msquare
LANG: C++11              
*/

#include <bits/stdc++.h>
using namespace std;

#define pb push_back

const int N = 40320, C = 8;

int fact[C + 1];
vector<int> awal, akhir;
int num[N + 5];
int before[N + 5];
char ar[N + 5];

vector<int> conv_to_vector(int x){
  vector<int> ans;
  vector<int> v(C);
  for(int i = 0;i < C; ++i) v[i] = i;

  for(int i = 0, sisax = x;i < C; ++i){
    int idx_i = sisax / fact[C - i - 1];
    sisax %= fact[C - i - 1];
    ans.pb(v[idx_i]);
    v.erase(v.begin() + idx_i);
  }
  return ans;
}
queue<int> q;

vector<int> convA(const vector<int>& v){
  vector<int> vA;
  vA.pb(v[7]);
  vA.pb(v[6]);
  vA.pb(v[5]);
  vA.pb(v[4]);
  vA.pb(v[3]);
  vA.pb(v[2]);
  vA.pb(v[1]);
  vA.pb(v[0]);
  return vA;
}

vector<int> convB(const vector<int>& v){
  vector<int> vB;
  vB.pb(v[3]);
  vB.pb(v[0]);
  vB.pb(v[1]);
  vB.pb(v[2]);
  vB.pb(v[5]);
  vB.pb(v[6]);
  vB.pb(v[7]);
  vB.pb(v[4]);
  return vB;
}

vector<int> convC(const vector<int>& v){
  vector<int> vC;
  vC.pb(v[0]);
  vC.pb(v[6]);
  vC.pb(v[1]);
  vC.pb(v[3]);
  vC.pb(v[4]);
  vC.pb(v[2]);
  vC.pb(v[5]);
  vC.pb(v[7]);
  return vC;
}

int conv_to_int(const vector<int> &V){
  vector<int> v(C);
  for(int i = 0;i < C; ++i) v[i] = i;

  int ans = 0;
  for(int i = 0;i < V.size(); ++i){
    int x = lower_bound(v.begin(), v.end(), V[i]) - v.begin();
    ans += x * fact[C - i - 1];
    v.erase(v.begin() + x); 
  } 
  return ans;
}

int main(){
  freopen("msquare.in", "r", stdin);
  freopen("msquare.out", "w", stdout);
  fact[0] = 1;
  for(int i = 1;i <= C; ++i) fact[i] = fact[i - 1] * i;
  
  for(int i = 0;i < C; ++i) {
    int x;
    cin >> x;
    x--;
    akhir.push_back(x);
  }
  memset(num, -1, sizeof num);
  int idxakhir = conv_to_int(akhir);
  num[0] = 0;
  before[0] = -1;
  q.push(0);
  bool ketemu = false;
  while(!q.empty() && !ketemu){
    int idxnow = q.front(); q.pop();
    if(idxnow == idxakhir){
      printf("%d\n", num[idxnow]);
      string s = "";
      int idxtmp = idxnow;
      while(idxtmp > 0){
        s += ar[idxtmp];
        idxtmp = before[idxtmp];
      }
      reverse(s.begin(), s.end());
      for(int i = 0;i < (int)s.size(); ++i){
        if(i && (i % 60 == 0)) printf("\n");
        printf("%c", s[i]);
      }
      puts("");
      ketemu = true;
      continue;
    }

    vector<int> v_now = conv_to_vector(idxnow);
    vector<int> vA = convA(v_now);
    int idxA = conv_to_int(vA);
    if(num[idxA] == -1){
      num[idxA] = num[idxnow] + 1;
      ar[idxA] = 'A';
      before[idxA] = idxnow;
      q.push(idxA);
    }

    vector<int> vB = convB(v_now);
    int idxB = conv_to_int(vB);
    if(num[idxB] == -1){
      num[idxB] = num[idxnow] + 1;
      ar[idxB] = 'B';
      before[idxB] = idxnow;
      q.push(idxB);
    }

    vector<int> vC = convC(v_now);
    int idxC = conv_to_int(vC);
    if(num[idxC] == -1){
      num[idxC] = num[idxnow] + 1;
      ar[idxC] = 'C';
      before[idxC] = idxnow;
      q.push(idxC);
    }
  }
  fclose(stdin);
  fclose(stdout);
  return 0;
}