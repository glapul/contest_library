// Dwuspójne składowe itd. - mosty traktowane jak dwuspójne!
// Linie oznaczone [D], [M], [A], [L] potrzebne tylko, jeśli szukamy
//     numeracji [D]wuspójnych, [M]ostów, p.[A]rtykulacji, funkcji [L]ow
// Maciek Wawro

const int MAXN = 1000005;

struct Edge{ // W momencie rozpoczęcia algorytmu musi być bcc = -1 i bridge = 0
    Edge* rev;
    int dest;
    int bcc;        //OUT: Numer komponentu
    bool bridge;    //OUT: Czy most                         /*M*/
    Edge(int v) : dest(v), bcc(-1) {
        bridge = false;                                     /*M*/
    };
};

int N;                  //IN: Liczba wierzchołków
list<Edge>  adj[MAXN];  //IN: Listy sąsiedztwa
int  visit[MAXN];
bool  artp[MAXN];  //OUT: True, jeśli dany wierzchołek jest p.art. /*A*/
int      bcc_num;  //OUT: Liczba komponentów                /*D*/
int    low[MAXN];                                           /*L*/

stack<Edge*> _stack;                                        /*D*/
int        _dfsTime;
int bccDFS(int v, bool root = false) {
    int lo = visit[v] = ++_dfsTime;
    FOREACH(it, adj[v]) {
        if(it -> bcc != -1) continue;
        _stack.push(&*it);                                  /*D*/
        it->rev->bcc = -2;
        if(!visit[it->dest]) {
            int ulo = bccDFS(it->dest);
            lo = min(ulo, lo);
            it->bridge = it->rev->bridge = (ulo > visit[v]);/*M*/
            if(ulo >= visit[v]) {                           /*AD*/
                artp[v] = !root; root = false;              /*A*/
                Edge* edge;                                 /*D*/
                do {
                    edge = _stack.top();                    /*D*/
                    _stack.pop();                           /*D*/
                    edge->bcc = edge->rev->bcc = bcc_num;   /*D*/
                } while(edge != &*it);                      /*D*/
                ++bcc_num;                                  /*D*/
            }                                               /*AD*/
        } else lo = min(lo, visit[it->dest]);
    }
    low[v] = lo;                                            /*L*/
    return lo;
}

void computeBCC(){
    fill(artp, artp+N, false);                              /*A*/
    fill(visit, visit+N, false);
    _dfsTime = 1;
    bcc_num = 0;                                            /*D*/
    REP(i,N) if(!visit[i]) bccDFS(i, true);
}
