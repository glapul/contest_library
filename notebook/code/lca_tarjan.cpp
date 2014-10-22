// LCA (algorytm Tarjana)
// Adam Polak

const int N = 1000000;
int n;                          // INPUT
vector<int> g[N];               // INPUT: graph
vector<pair<int,int*> > q[N];   // INPUT: queries
int p[N], anc[N];
bool col[N];

int set_find(int a) { return p[a]==a?a:p[a]=set_find(p[a]); }

void dfs(int u, int f) {
    FOREACH(v, g[u]) if (*v!=f) {
        dfs(*v, u);
        anc[p[set_find(u)]=set_find(*v)] = u;
    }
    col[u] = true;
    FOREACH(i,q[u]) 
        if (col[i->first]) *(i->second) = anc[set_find(i->first)];
}

void lca(int root) {
    REP(i,n) { p[i]=anc[i]=i; col[i]=0; }
    dfs(root, -1);
}
