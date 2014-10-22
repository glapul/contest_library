// LCA i LAQ online (algorytm z drabinami)
// Adam Polak

const int N = 100000;

int n;                  // INPUT
vector<int> graph[N];   // INPUT

int in[N], out[N], p[N], size[N], l_ind[N], depth[N], dfstime;
vector<int> ladder[N]; // Clear these vectors after each testcase!

void dfs(int u) {
    in[u] = dfstime++; size[u] = 1; int best_s = 0; l_ind[u] = u;
    FOREACH(v, graph[u]) if (*v != p[u]) {
        p[*v] = u; depth[*v] = depth[u] + 1;
        dfs(*v);
        if (size[*v] > best_s) { best_s = size[*v]; l_ind[u] = l_ind[*v]; }
        size[u] += size[*v];
    }
    ladder[l_ind[u]].push_back(u);
    out[u] = dfstime++;
}

void init(int root) { dfstime = 0; p[root] = -1; depth[root] = 0; dfs(root); }

inline bool is_anc(int a, int b) { return (in[a] <= in[b] && out[b] <= out[a]); }

int LCA(int a, int b) {  // Lowest common ancestor
    int k = l_ind[a];
    while(!is_anc(*(ladder[k].end()-1), b)) k = l_ind[p[*(ladder[k].end()-1)]];
    int l = 0, r = ladder[k].size() - 1;
    while(l < r) {
        int mid = (l + r) / 2;
        if (is_anc(ladder[k][mid], b) && is_anc(ladder[k][mid], a))
            r = mid; 
        else 
            l = mid+1;
    }
    return ladder[k][l];
}

int LAQ(int a, int x) {  // Level ancestor query
    if (depth[a] < x) return -1;
    int d = depth[a] - x;
    int k = l_ind[a];
    while(depth[*(ladder[k].end()-1)] > d) k = l_ind[p[*(ladder[k].end()-1)]];
    return *(ladder[k].end() - 1 - d + depth[*(ladder[k].end()-1)]);
}
