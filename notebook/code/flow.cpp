// MAKSYMALNY PRZEPLYW O(V^3) (algorytm Push-Relabel)
// Adam Polak

const int N = 100*1000;

struct Edge {
    int v,cap,flow;
    int back_ind;
    Edge *back;
    Edge(int vi, int ci):v(vi),cap(ci){}
};

/* Usage:
   1) n=...; s=...; t=...;
   2) REP(i,n) g[i].clear();
   3) add_edge(...);
   4) compute_flow();
*/

int n,s,t;
int e[N],h[N];
vector<Edge> g[N];
vector<Edge>::iterator cur[N];

void bfs(int start, int start_h) {
    queue<int> q;
    h[start] = start_h;
    for(q.push(start);!q.empty();q.pop()) {
        int u = q.front();
        FOREACH(i,g[u])
            if (i->back->flow < i->back->cap && h[i->v]>h[u]+1) {
                    h[i->v] = h[u] + 1;
                    q.push(i->v);
            }
    }
}

int compute_flow() {
    queue<int> q;
    REP(i,n) {
        FOREACH(j,g[i]) {
            j->flow = 0;
            j->back = &g[j->v][j->back_ind];
        }
        cur[i] = g[i].begin();
        h[i] = e[i] = 0;
    }
    FOREACH(i,g[s]) {
        i->flow = i->cap;
        i->back->flow = -i->flow;
        if (e[i->v]==0 && i->v!=t) q.push(i->v);
        e[i->v] += i->flow;
    }
    h[s] = n;
    int relabel_counter = 0;
    for(;!q.empty();q.pop()) {
        int u = q.front();
        while (e[u]>0) {
            if (cur[u]==g[u].end()) { // relabel
                relabel_counter++;
                h[u] = 2*n+1;
                FOREACH(i,g[u]) if(i->flow < i->cap) h[u]=min(h[u],1+h[i->v]);
                cur[u] = g[u].begin(); 
                continue; 
            }
            if (cur[u]->flow < cur[u]->cap && h[u]==h[cur[u]->v]+1) { // push
                int d = min(e[u], cur[u]->cap - cur[u]->flow);
                cur[u]->flow += d;
                cur[u]->back->flow -= d;
                e[u] -= d;
                e[cur[u]->v] += d;
                if (e[cur[u]->v]==d && cur[u]->v!=t && cur[u]->v!=s) q.push(cur[u]->v);
            } else cur[u]++; 
        }
        if (relabel_counter >= n) { 
            REP(i,n) h[i]=2*n+1;
            bfs(t,0);
            bfs(s,n);
            relabel_counter = 0;
        }
    }
    return e[t];
}

void add_edge(int a, int b, int c, int c_back=0) {
    assert(a != b);  // NIE wrzucac petelek!
    g[a].push_back(Edge(b,c));
    g[b].push_back(Edge(a,c_back));
    g[a].back().back_ind = g[b].size()-1;
    g[b].back().back_ind = g[a].size()-1;
}

// MAKSYMALNY PRZEPLYW (algorytm Edmondsa-Karpa)
// Adam Polak

const int N = 1000;
int n, cap[N][N];   // INPUT
int flow[N][N];     // OUTPUT

int edmonds(int s, int t) {
    int b,e,q[n],p[n],d,FLOW=0;
    REP(i,n) REP(j,n) flow[i][j]=0;
    for(;;) {
        REP(i,n) p[i]=-1;
        for(q[b=e=0]=s;b<=e;b++)
            REP(v,n) 
                if (flow[q[b]][v] < cap[q[b]][v] && p[v]<0)
                    p[q[++e]=v] = q[b];
        if (p[t]<0) break;
        d = cap[p[t]][t] - flow[p[t]][t];
        for(int i=t;i!=s;i=p[i]) d=min(d,cap[p[i]][i]-flow[p[i]][i]);
        for(int i=t;i!=s;i=p[i]) {
            flow[p[i]][i] += d;
            flow[i][p[i]] -= d;
        }
        FLOW += d;
    }
    return FLOW;
}
