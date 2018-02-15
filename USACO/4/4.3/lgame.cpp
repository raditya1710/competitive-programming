/*
ID: raditya1
TASK: lgame
LANG: C++11              
 */

#include <bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef pair<char,int> pci;
typedef pair<string,int> psi;

const int MULT = 8;

#define fi first
#define se second
#define mp make_pair
#define pb push_back
int ar[] = {2, 5, 4, 4, 1, 6, 5, 5, 1, 7,
            6, 3, 5, 2, 3, 5, 7, 2, 1, 2,
            4, 6, 6, 7, 5, 7};

vector<pci> base;
vector<psi> ve;
vector<psi> tiny;
map<int, string> MAP;

int conv_to_int(const vector<pci>& v){
  int ans = 0;
  for(int i = 0; i < (int) v.size(); ++i){
    ans += v[i].se;
    ans *= MULT;
  }
  return ans;
}
vector<string> res;

bool leq(int a, int b){
  while(a > 0 || b > 0){
    if((a % MULT) > (b % MULT)) return false;
    a /= MULT;
    b /= MULT;
  }
  return true;
}

int main(){
  freopen("lgame.in", "r", stdin);
  freopen("lgame.out", "w", stdout);
  string s;
  cin >> s;
  sort(s.begin(), s.end());
  int len = (int) s.size();
  int idx = 0;
  for(int i = 1;i < len; ++i){
    if(s[i] != s[i - 1]){
      base.pb(mp(s[i - 1], i - idx));
      idx = i;
    }
  }
  base.pb(mp(s[len - 1], len - idx));
  int BASE_HASH = conv_to_int(base);

  ifstream f("lgame.dict");
  if(f.is_open()){
    string line;
    while(getline(f, line)){
      if(line == ".") break;
      bool bisa = true;
      vector<pci> v(base);
      for(int i = 0;i < (int) v.size(); ++i) v[i].se = 0;

      for(int i = 0;i < (int) line.size() && bisa; ++i){
        bool ketemu = false;
        for(int j = 0;j < (int) v.size() && !ketemu; ++j){
          if(v[j].fi == line[i] && v[j].se < base[j].se){
            ketemu = true;
            v[j].se++;
          }
        }
        bisa = ketemu;
      } 
      if(bisa){
        ve.pb(mp(line, conv_to_int(v)));
      }
    }
    f.close();
  }
  int maks = 0;
  for(int i = (int) ve.size() - 1; i >= 0; --i){
    vector<pci> v(base);
    int score = 0;
    const string &s_now = ve[i].fi;
    for(int j = 0;j < (int) s_now.size(); ++j){
      for(int k = 0;k < (int) v.size(); ++k){
        if(v[k].fi == s_now[j]){
          v[k].se--;
          score += ar[s_now[j] - 'a'];
        }
      }
    }
    int len_sisa = (int)s.size() - (int)s_now.size(); 
    if(len_sisa >= 3){
      int max_score = 0;
      vector<string> max_str;
      for(int j = 0; j < (int) tiny.size(); ++j){
        int hash_total = tiny[j].se + ve[i].se;
        if(leq(hash_total, BASE_HASH)){
          int score = 0;
          const string &tiny_now = tiny[j].fi;
          for(int k = 0;k < (int) tiny_now.size(); ++k){
            score += ar[tiny_now[k] - 'a'];
          }
          if(max_score < score){
            max_score = score;
            max_str.clear();
            max_str.push_back(tiny[j].fi);
          }
          else if(max_score == score){
            max_str.push_back(tiny[j].fi);
          }
        }
      }
      if(max_score > 0){
        if(maks < score + max_score){
          maks = score + max_score;
          res.clear();
          for(int j = 0;j < (int) max_str.size(); ++j){
            res.push_back(s_now + " " + max_str[j]);
          }
        }
        else if(maks == score + max_score){
          for(int j = 0;j < (int) max_str.size(); ++j){
            res.push_back(s_now + " " + max_str[j]);
          }
        }
      }
    }
    if(maks < score){
      maks = score;
      res.clear();
      res.pb(s_now);
    }
    else if(maks == score){
      res.pb(s_now);
    }
    if(s_now.size() <= 4) tiny.push_back(ve[i]);
  }

  printf("%d\n", maks);
  for(int i = (int) res.size() - 1;i >= 0; --i){
    puts(res[i].c_str());
  }
  fclose(stdin);  
  fclose(stdout);
  return 0;
}
