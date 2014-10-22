// Dominatory w grafie skierowanym O(E log(V))
// Zalozenie: Kazdy wierzcholek jest osiagalny z korzenia
// Bartosz Walczak

const int MAXN = 100; // maksymalna liczba wierzcholkow

int n, root;           // IN: liczba wierzcholkow, korzen
bool edge[MAXN][MAXN]; // IN: macierz sasiedztwa (mozna zmienic na liste)
int dom[MAXN];         // OUT: bezposredni dominator (dom[root]==-1)
int semi[MAXN], vertex[MAXN], parent[MAXN], anc[MAXN], label[MAXN];
int head[MAXN], next[MAXN];
int cur_time;

void search(int w) {
    semi[w] = cur_time;
    vertex[cur_time] = w;
    ++cur_time;
    FOR(v,0,n) /*tu zmienic*/ if (edge[w][v] && semi[v]==-1)
      { parent[v] = w; search(v); }
}

void compress(int v) {
    if (anc[anc[v]]==-1) return;
    compress(anc[v]);
    if (semi[label[anc[v]]] < semi[label[v]]) label[v] = label[anc[v]];
    anc[v] = anc[anc[v]];
}

int eval(int v) {
    if (anc[v]==-1) return v;
    compress(v);
    return label[v];
}

void compute_dominators() {
    FOR(v,0,n) { semi[v]=anc[v]=head[v]=-1; label[v]=v; }
    cur_time = 0;
    search(root);
    FORD(i,n,1) {
        int w = vertex[i];
        FOR(v,0,n) /*tu zmienic*/ if (edge[v][w])
          semi[w] = min(semi[w], semi[eval(v)]);
        next[w] = head[vertex[semi[w]]];
        head[vertex[semi[w]]] = w;
        anc[w] = parent[w];
        while (head[parent[w]]!=-1) {
            int v = head[parent[w]];
            head[parent[w]] = next[v];
            int u = eval(v);
            dom[v] = semi[u]<semi[v] ? u : parent[w];
        }
    }
    FOR(i,1,n) {
        int w = vertex[i];
        if (dom[w]!=vertex[semi[w]]) dom[w] = dom[dom[w]];
    }
    dom[root] = -1;
}
