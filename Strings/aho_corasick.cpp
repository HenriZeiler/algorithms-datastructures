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

struct AhoCorasick {
  const static int A = 26; // alphabet size
  struct Vert {
    array<int, A> next{};
    int marked = 0; // custom data
    Vert() = default;
  };
  vector<Vert> trie{Vert()}; // init with root
  void add_string(const string &s) {
    int v = 0;
    for (char c : s) {
      c -= 'a';
      if (!trie[v].next[c]) {
        trie[v].next[c] = trie.size();
        trie.emplace_back();
      }
      v = trie[v].next[c];
    }
    trie[v].marked++;
  }
  void finalize() {
    queue<array<int, 4>> q{{{0, 0, 0, 0}}};
    while (size(q)) {
      auto [v, p, plink, pch] = q.front();
      q.pop();
      int link = p == 0 ? 0 : trie[plink].next[pch];
      trie[v].marked += trie[link].marked;
      rep(c, A) {
        if (!trie[v].next[c]) // no child for c
          trie[v].next[c] = trie[link].next[c];
        else
          q.push({trie[v].next[c], v, link, c});
      } // after this loop: compute v’s aggregates
    }
  } // build automaton
};