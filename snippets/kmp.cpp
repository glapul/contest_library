vector<int> compute_kmp(string& s) {
  vector<int> P {0};
  int t = 0;
  for (int i = 1; i <= (int)s.size(); i++) {
    while (t > 0 && s[i] == s[t])
      t = P[t - 1];
    if (s[i] == s[t])
      t++;
    P.push_back(t);
  }
}
