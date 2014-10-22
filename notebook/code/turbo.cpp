// MAKSYMALNE SKOJARZENIE w grafie dwudzielnym ("Turbomatching")
// Adam Polak

const int N = 10000;
int n1,n2;          // INPUT
vector<int> g[N];   // INPUT
int m1[N], m2[N];   // OUTPUT
bool c[N];

bool dfs(int u) {
    if (u<0) return true;
    if (c[u]) return false; else c[u]=true;
    FOREACH(v, g[u]) 
        if (dfs(m2[*v])) { m1[u] = *v; m2[*v] = u; return true; }
    return false;
}

int matching() {
    REP(i,n1) m1[i]=-1;
    REP(i,n2) m2[i]=-1;
    bool changed;
    do {
        changed = 0;
        REP(i,n1) c[i]=false;
        REP(i,n1) if (m1[i]<0) changed |= dfs(i);
    } while(changed);
    int siz = 0;
    REP(i,n1) siz += (m1[i]!=-1);
    return siz;
}
