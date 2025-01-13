#include <bits/stdc++.h>

#define rep(a, b) for (int a = 0; a < (b); ++a)
#define all(a) (a).begin(), (a).end()
#define endl '\n'
#define pb push_back
typedef long long ll;

using namespace std;
using ii = pair<int, int>;
using cint = const int;
using vii = vector<ii>;
using vi = vector<int>;
using vb = vector<bool>;
using vvi = vector<vector<int>>;
using vll = vector<ll>;
using Graph = vector<vector<int>>;
const int MOD = 1000000007;
const ll INF = 9223372036854775807;
const int iINF = 0x3f3f3f3f;

void dfs(vvi &G, vi &euler, vi &depth, vi &first, int v, int d = 0,
         int p = -1) {
  depth[v] = d;
  first[v] = euler.size();
  euler.push_back(v);
  for (auto nei : G[v]) {
    if (nei != p) {
      dfs(G, euler, depth, nei, d + 1, v);
      euler.push_back(v);
    }
  }
}

void solve() {
  // do dfs
  // build depth segTree
  // get first indexes and use these to query segtree
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);
  int t = 1;
  cin >> t;
  while (t--)
    solve();
  return 0;
}
s