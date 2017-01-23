#include <bits/stdc++.h>
using namespace std;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define all(x) (x).begin(), (x).end()
#define x first
#define y second
typedef long long ll;
const double EPS = 1e-9;
const int INF = 1<<30;
const ll INFLL = 1LL<<60;


template<typename T>
unordered_map<T,int> scale_to_consecutive_integers(vector<T> input) {
  sort(all(input));
  input.resize(unique(all(input)) - input.begin());
  unordered_map<T, int > res;
  REP(i, (int)input.size())
    res[input[i]] = i;
  return res;
}

namespace DiscreteSearchings {
namespace Boolean {

pair<ll, ll> binary_search_for_change_first_false(ll p, ll q, function<bool(ll)> func) {
  assert(func(p) == true);
  assert(func(q) == false);
  while (p + 1 <  q) {
    ll mid = (p + q) / 2;
    if (func(mid))
      p = mid;
    else
      q = mid;
  }
  return {p, q};
}

pair<ll, ll> binary_search_for_change_first_true(ll p, ll q, function<bool(ll)> func) {
  return binary_search_for_change_first_false(p, q, [func](ll x){return !func(x);});
}
}

namespace Ternary {

template<typename T>
pair<T, ll> ternary_search_minimize(ll p, ll q, function<T(ll)> func) {
  while (q - p >= 3) {
    int l = p + (q-p)/3,
        r = p + 2*(q-p)/3;
    if (func(l) <= func(r))
      q = r;
    else
      p = l;
  }
  vector<T> vals;
  for (ll i = p; i <= q; i++)
    vals.emplace_back(func(i));
  return {*min_element(all(vals)), p + min_element(all(vals)) - vals.begin() };
}

template<typename T>
pair<T, ll>ternary_search_maximize(ll p, ll q, function<T(ll)> func) {
  auto res = ternary_search_minimize(p, q, [func](ll x){return -func(x);});
  res.first *=-1;
  return res;
}


}
}
