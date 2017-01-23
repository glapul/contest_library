#include <bits/stdc++.h>
using namespace std;
#define int long long

const int MX = 200 * 1000 + 7;
const int INF = 1LL << 50;

typedef pair<int,int> Range;
#define x first
#define y second

/* 0 indexed Fenwick tree
 * type: long long
 * ops:
 * add(x, v) - add v to the element at x
 * sum_prefix(x) - get the sum of elements in [0, x]
 * sum_interval(x, y) - get the sum of elemenents in [x, y]
 *   */
struct FenwickTree {
  vector<int> tp;
  FenwickTree(int n=0) {
    tp = vector<int>(n + 1);
  }
  void add (int x, int v) {
    x++;
    for(;x < (int)tp.size(); x+=x&-x)
      tp[x] += v;
  }
  int sum_prefix(int x) {
    x++;
    int res = 0;
    for(;x >0; x-=x&-x)
      res += tp[x];
    return res;
  }
  int sum_interval(int x, int y) {
    return sum_prefix(y) - sum_prefix(x - 1);
  }
};

int intersect(const Range& a, const Range& b) {
  if (a.x > b.y || b.x > a.y)
    return 0;
  if (a.x >= b.x && a.y <= b.y)
    return 2;
  return 1;
}

struct MinPlusTree {
  struct Node {
    int minimum, added_value;
    Node() : minimum(INF), added_value(0) {}
  };

  int n;
  vector<Node> tree;
  MinPlusTree(int n=0):n(n) {
    tree = vector<Node>(4 * n);
  }
  void _add(int v, Range range, Range op_range, int val) {
    int intrsc = intersect(range, op_range);
    if (intrsc == 0)
      return;
    if (intrsc == 2) {
      tree[v].added_value += val;
      tree[v].minimum += val;
    }
    if (intrsc == 1) {
      int mid = (range.x + range.y) / 2;
      Range left_range  {range.x, mid},
            right_range {mid + 1, range.y};
      _add(2*v, left_range, op_range, val);
      _add(2*v+1, right_range, op_range, val);
      tree[v].minimum = min(tree[2*v].minimum, tree[2*v+1].minimum) + tree[v].added_value;
    }
  }
  void add(Range range, int val) {
    _add(1, Range {0, n - 1}, range, val);
  }
  int _query(int v, Range range, Range op_range) {
    int intrsc = intersect(range, op_range);
    if (intrsc == 0)
      return INF;
    if (intrsc == 2) {
      return tree[v].minimum;
    }
    if (intrsc == 1) {
      int mid = (range.x + range.y) / 2;
      Range left_range  {range.x, mid},
            right_range {mid + 1, range.y};
      int l  =_query(2*v, left_range, op_range);
      int r = _query(2*v+1, right_range, op_range);
      return min(l, r) + tree[v].added_value;
    }
    throw(-1);
  }
  int query(Range range) {
    return _query(1, Range{0, n-1}, range);
  }
};
