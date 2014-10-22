// MAX FLOW MIN COST O(V^2F)
// Adam Polak

// Usage: vide push-relabel

typedef int capacity_t;
typedef int cost_t;

const int N = 10000;
// use INFINITY from cmath if cost_t is a double
const cost_t INF = 1000*1000*1000; 

struct edge {
    int from, v;
    capacity_t cap, flow;
    cost_t cost, dist;
    int revIndex;
    bool residual() { return flow<cap; }
    edge(int _f, int _v, capacity_t _cap, cost_t _cost):
        from(_f),v(_v),cap(_cap),flow(0),cost(_cost),dist(_cost){}
};

int n,s,t;
cost_t d[N];
vector<edge>::iterator p[N];
vector<edge> g[N];

bool queued[N];
void bellmanFord() {
    REP(i,n) { d[i]=INF; queued[i]=0; }
    queue<int> q;
    d[s]=0; q.push(s); queued[s]=0;
    while(!q.empty()) {
        int u=q.front(); q.pop(); queued[u]=0;
        FOREACH(i, g[u])
            if (i->residual() && d[i->v] > d[u]+i->dist) {
                d[i->v] = d[u]+i->dist;
                p[i->v] = i;
                if (!queued[i->v]) { q.push(i->v); queued[i->v]=1; }
            }
    }
}

void dijkstra() {
    REP(i,n) { d[i]=INF; }
    priority_queue< pair<cost_t,int>, vector<pair<cost_t,int> >, 
        greater<pair<cost_t,int> > > q;
    d[s]=0; q.push(make_pair(0,s));
    while(!q.empty()) {
        int u = q.top().second;
        cost_t dist = q.top().first;
        q.pop();
        if (dist!=d[u]) continue;
        FOREACH(i, g[u])
            if (i->residual() && d[i->v] > d[u]+i->dist) {
                d[i->v] = d[u]+i->dist;
                p[i->v] = i;
                q.push(make_pair(d[i->v],i->v));
            }
    }
}

void usePotentials() {
    REP(u,n) FOREACH(i, g[u])
        i->dist = i->dist + d[i->from] - d[i->v];
}

// Mozna (za/od)komentowac linie z gwiazdkami - w praktyce bywa szybciej
capacity_t FLOW;
cost_t COST;
void fordFulkerson() {
    FLOW = 0;
    COST = 0;
    bellmanFord();       // *
    usePotentials();     // *
    for(;;) {
        // bellmanFord();   // * dijkstra sux ;)
        dijkstra();      // *
        usePotentials(); // *
        if (d[t]==INF) break;
        cost_t cost = 0;
        for(int u=t;u!=s;u=p[u]->from) {
            p[u]->flow++;
            g[p[u]->v][p[u]->revIndex].flow--;
            cost += p[u]->cost;
        }
        FLOW ++; COST += cost;
    }
}

void addEdge(int a, int b, capacity_t f, cost_t c) {
    assert(a != b);  // NIE wrzucac petelek!
    g[a].push_back(edge(a,b,f,c));
    g[b].push_back(edge(b,a,0,-c));
    g[a].back().revIndex = g[b].size()-1;
    g[b].back().revIndex = g[a].size()-1;
}
