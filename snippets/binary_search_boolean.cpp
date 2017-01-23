
pair<long long, long long> binary_search_for_change_first_false(long long p, long long q, function<bool(long long)> func) {
  assert(func(p) == true);
  assert(func(q) == false);
  while (p + 1 <  q) {
    long long mid = (p + q) / 2;
    if (func(mid))
      p = mid;
    else
      q = mid;
  }
  return {p, q};
}

pair<long long, long long> binary_search_for_change_first_true(long long p, long long q, function<bool(long long)> func) {
  return binary_search_for_change_first_false(p, q, [func](long long x){return !func(x);});
}
