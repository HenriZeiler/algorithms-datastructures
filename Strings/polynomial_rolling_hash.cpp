#include <bits/stdc++.h>

#include <tuple>
#include <utility>
using namespace std;

// clang-format off
void in(auto &arg) { cin >> arg;}
void out(const auto &arg) { cout << arg << " ";}
template<class T> concept RangeIo = ranges::range<T> && !convertible_to<T, string>;
void in(RangeIo auto &arg) {for (auto && x : arg ) in(x);}
void out(const RangeIo auto &arg) {for (auto & x : arg) out(x);}
void in(auto&... args) { (in(args), ...); }
void outl(const auto&... args) { ((out(args)), ...); cout << endl;}

template <typename T> using vec = vector<T>;
using num = long long;
using ll = long long;
using ull = unsigned long long;
#define arr(n) array<num, n>

// clang-format on
// -------------------------------------

const __int128 MOD1 = 1e9 + 7;
const __int128 MOD2 = bit_cast<num>(4.8);

struct mint {
  __int128 val;
  __int128 mod;
  explicit mint(__int128 mod, __int128 n = 0)
      : mod(mod), val((n % mod + mod) % mod) {}
  friend mint operator+(mint a, mint b) { return mint(a.mod, a.val + b.val); }
  friend mint operator-(mint a, mint b) {
    return mint(a.mod, a.val - b.val + a.mod);
  }
  friend mint operator*(mint a, mint b) { return mint(a.mod, a.val * b.val); }
  friend bool operator==(mint a, mint b) { return a.val == b.val; }
  friend bool operator<(mint a, mint b) { return a.val < b.val; }
  mint pow(num e) const {
    mint e_mint(mod, e);
    return e == 0
               ? mint(mod, 1)
               : mint(mod, val * val).pow(e / 2) * mint(mod, (e % 2 ? val : 1));
  }
  mint inv() { return pow(mod - 2); }
};

mint BASE1(MOD1, 67);
mint BASE2(MOD2, 1e9 + 7);

mint rolling_hash(const string &s, const mint base, num mod) {
  mint h(mod, 0);
  for (char c : s) {
    mint val(mod, (unsigned char)c + 1);
    h = h * base + val;
  }
  return h;
}