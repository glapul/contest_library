// SILNIE SPÓJNE SKŁADOWE (algrotym Tarjana) + 2SAT
// Adam Polak

const int N = 100*1000;
const int NIL = (-1);

int n;              // INPUT
vector<int> g[N];   // INPUT

int t, in[N], low[N];
stack<int> s;
bool stacked[N];

int scc[N], scc_n;  // OUTPUT (SCC)
bool value[N];      // OUTPUT (2SAT)

void tarjan(int u) {
    low[u] = in[u] = t++;
    s.push(u);
    stacked[u] = true;
    FOREACH(v, g[u]) {
        if (in[*v]==NIL) {
            tarjan(*v);
            low[u] = min(low[u], low[*v]);
        } else if (stacked[*v]) low[u] = min(low[u], in[*v]);
    }
    if (low[u]==in[u]) {
        for(;;) {
            int v = s.top(); s.pop();
            stacked[v] = false;
            scc[v] = scc_n;
            if (v==u) break;
        }
        scc_n++;
    }
}

void tarjan_scc() {
	REP(i,n) { in[i] = low[i] = NIL; stacked[i] = false; }
	scc_n = t = 0;
	REP(i,n) if(in[i]==NIL) tarjan(i);
}

// 2SAT usage:
// 1) n = 2*variables
// 2) REP(i,n) g[i].clear();
// 3) add_constr(...) //np. add_constr(zm1, 1, zm2, 0) = ((NOT zm1) OR zm2)
// 4) solve_2sat();         
void add_constr(int a, bool neg_a, int b, bool neg_b) {
    g[2*a+neg_a].push_back(2*b+1-neg_b);
    g[2*b+neg_b].push_back(2*a+1-neg_a);
}

bool solve_2sat() {
    tarjan_scc();
    int v[scc_n], c[scc_n];
    REP(i,(n/2)) if (scc[2*i]==scc[2*i+1]) return false;
    REP(i,n) v[scc[i]] = i;
    REP(i,scc_n) c[i] = NIL;
    REP(i,scc_n) if (c[i]==NIL) {
        c[i] = 1;
        c[scc[v[i]^1]] = 0;
    }
    REP(i,(n/2)) value[i] = c[scc[2*i+1]];
    return true;
}
