template<typename T>
unordered_map<T,int> scale_to_consecutive_integers(vector<T> input) {
  sort(all(input));
  input.resize(unique(all(input)) - input.begin());
  unordered_map<T, int > res;
  for (int i = 0; i < (int)input.size(); i++)
    res[input[i]] = i;
  return res;
}
