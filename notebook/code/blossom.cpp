// MAKSYMALNE SKOJARZENIE w dowolnym grafie O(V^3)
// Bartosz Walczak

const int MAXN = 100; // maksymalna liczba wierzcholkow

int n;                 // IN: liczba wierzcholkow
bool edge[MAXN][MAXN]; // IN: macierz sasiedztwa (mozna zmienic na liste)
int mate[MAXN];        // OUT: wierzcholek skojarzony (-1 oznacza brak)
int label[MAXN], base[MAXN], prev1[MAXN], prev2[MAXN];
bool mark[MAXN];

bool prepare(int v) {
    for (;;) {
        mark[v] = !mark[v];
        if (mate[v]==-1) return mark[v];
        v = base[prev2[mate[v]]];
    }
}

int shrink(int v, int b1, int b2, queue<int> &Q) {
    while (mark[v]) {
        prev1[v] = b1; prev2[v] = b2;
        mark[mate[v]] = true;
        Q.push(mate[v]);
        v = base[prev2[mate[v]]];
    }
    return v;
}

bool make_blos(int i, int j, int bi, int bj, queue<int> &Q) {
    if (label[i]!=1 || i==j) return false;
    if (prepare(i), prepare(j)) return true;
    int b = (shrink(i, bi, bj, Q), shrink(j, bj, bi, Q));
    REP(v,n) if (mark[base[v]]) base[v] = b;
    return false;
}

void rematch(int i, int j) {
    int next = mate[i];
    mate[i] = j;
    if (next==-1) return;
    mate[next] = -1;
    rematch(prev2[next], prev1[next]);
    rematch(prev1[next], prev2[next]);
}

bool augment() {
    queue<int> Q;
    REP(i,n) {
        label[i] = mate[i]==-1;
        if (mate[i]==-1) Q.push(i);
        mark[i] = false;
        base[i] = i;
    }
    while (!Q.empty()) {
        int cur = Q.front(); Q.pop();
        REP(i,n) /*tu zmienic*/ if (edge[cur][i] && i!=mate[cur]) {
            if (!label[i]) {
                label[i] = -1;
                label[mate[i]] = 1;
                Q.push(mate[i]);
                prev1[i] = i; prev2[i] = cur;
            }
            else if (make_blos(base[i], base[cur], i, cur, Q)) {
                rematch(i, cur); rematch(cur, i);
                return true;
            }
        }
    }
    return false;
}

int compute_gcm() { // zwraca licznosc maksymalnego skojarzenia
    fill_n(mate, n, -1);
    int res = 0;
    while (augment()) ++res;
    return res;
}
