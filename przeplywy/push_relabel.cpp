#include <bits/stdc++.h>
using namespace std;
#define int long long

const int INF = 1LL<<50;
struct PushRelabelNetwork {
  struct Edge {
    int from;
    int to;
    int c;
    int cross_ref;
  };

  int n, s, t;
  vector<vector<Edge>> edges;
  vector<int> excess;
  vector<int> height;
  vector<vector<Edge>::iterator> next_neighbor;
  queue<int> qu;

  void push(Edge& e) {
    int p = min(excess[e.from], e.c);
    excess[e.from] -= p;
    excess[e.to]   += p;
    e.c -= p;
    edges[e.to][e.cross_ref].c += p;
    if (e.to != s && e.to != t && excess[e.to] == p)
      qu.push(e.to);
  }
  int relabel_count = 0;
  void relabel(int u) {
    relabel_count++;
    next_neighbor[u] = edges[u].begin();
    height[u] = 2*n+1;
    for (auto& e : edges[u]) {
      if (e.c > 0) {
        height[u] = min (height[u], height[e.to] + 1);
      }
    }
  }

  void discharge(int u) {
    while (excess[u] > 0) {
      if (next_neighbor[u] != edges[u].end()) {
        Edge& e = *next_neighbor[u];
        if (e.c > 0 && height[u] == 1 + height[e.to])
          push(e);
        else
          next_neighbor[u]++;
      } else {
        relabel(u);
      }
    }
  }

  PushRelabelNetwork(int n, int s, int t):n(n), s(s), t(t) {
    edges = vector<vector<Edge>>(n, vector<Edge>());
    excess = vector<int>(n);
    height = vector<int>(n);
    next_neighbor = vector<vector<Edge>::iterator>(n);
  }

  void AddEdge(int u, int v, int c) {
    edges[u].push_back({u, v, c, (int)edges[v].size()});
    edges[v].push_back({v, u, 0, (int)edges[u].size() - 1});
  }

  void global_relabelling() {
    queue<int> q;
    fill(height.begin(), height.end(), INF);
    height[t] = 0;
    q.push(t);
    while (!q.empty()) {
      int akt = q.front();
      q.pop();
      for (auto& e : edges[akt]) {
        if (height[e.to] != INF)
          continue;
        auto& rev = edges[e.to][e.cross_ref];
        if (rev.c > 0) {
          height[e.to] = height[akt] + 1;
          q.push(e.to);
        }
      }
    }
    height[s] = n;
    q.push(s);
    while (!q.empty()) {
      int akt = q.front();
      q.pop();
      for (auto& e : edges[akt]) {
        if (height[e.to] != INF)
          continue;
        auto& rev = edges[e.to][e.cross_ref];
        if (rev.c > 0) {
          height[e.to] = height[akt] + 1;
          q.push(e.to);
        }
      }
    }
  }

  int ComputeMaxFlow() {
    for (int i = 0; i < n; i++) {
      next_neighbor[i] = edges[i].begin();
    }
    height[s] = n;
    excess[s] = INF;
    for (auto& e : edges[s])
      push(e);
    for (;!qu.empty();qu.pop()) {
      int u = qu.front();
      discharge(u);
      if (relabel_count > n) {
        global_relabelling();
        relabel_count = 0;
      }
    }
    return excess[t];
  }
};

void solve() {
  int n, m, s, t;
  cin >> n >> m >> s >> t;
  s--;t--;
  PushRelabelNetwork g (n, s, t);
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    a--;b--;
    g.AddEdge(a, b, c);
  }
  cout << g.ComputeMaxFlow() << endl;
}

main() {
  int z;
  cin >> z;
  while (z--)
    solve();
}
