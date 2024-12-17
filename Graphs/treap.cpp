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

struct TreapNode {
  int key_, prio_;
  TreapNode *l_ = nullptr, *r_ = nullptr;
};

pair<TreapNode *, TreapNode *> split(TreapNode *cur_node, int key) {
  if (cur_node->key_ < key) {
    if (cur_node->r_ != nullptr) {
      auto [rl, rr] = split(cur_node->r_, key);
      cur_node->r_ = rl;
      return make_pair(cur_node, rr);
    } else {
      return make_pair(cur_node, nullptr);
    }
  } else {
    if (cur_node->l_ != nullptr) {
      auto [ll, lr] = split(cur_node->l_, key);
      if (cur_node->l_ != nullptr)
        cur_node->l_ = lr;
      return make_pair(ll, cur_node);
    } else {
      return make_pair(nullptr, cur_node);
    }
  }
}

TreapNode *
merge(TreapNode *l,
      TreapNode *r) { // assumption: all keys in l smaller than all keys in r
  if (l->prio_ < r->prio_) { // equal prios should never be encountered
    if (l->r_ != nullptr) {
      TreapNode *tmp = merge(l->r_, r);
      l->r_ = tmp;
      return l;
    } else {
      l->r_ = r;
      return l;
    }
  } else {
    if (r->l_ != nullptr) {
      TreapNode *tmp = merge(l, r->l_);
      r->l_ = tmp;
      return r;
    } else {
      r->l_ = l;
      return r;
    }
  }
}

void solve() {}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.precision(10);
  int t = 1; // cin >> t;
  while (t--)
    solve();
  return 0;
}