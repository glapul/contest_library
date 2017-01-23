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
