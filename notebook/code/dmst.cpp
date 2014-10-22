/* MINIMALNE SKIEROWANE DRZEWO ROZPINAJACE O(E log(V))
   Zalozenia: 1. do korzenia nie wchodzi zadna krawedz
              2. istnieje sciezka z korzenia do kazdego innego wierzcholka    */

// Bartosz Walczak

const int MAXN = 100, MAXM = 100; // maksymalna liczba wierzcholkow i krawedzi

struct edge { // krawedz/element kolejki zlaczalnej
    int u, v; // IN: poczatek i koniec krawedzi 
    int key;  // IN: waga krawedzi (zmienia sie!)
    
    edge *left, *right; // poczatkowo: 0, 0
    int len, add;       // poczatkowo: 1, 0
};

struct node1 { // element zbioru
    node1 *parent;
    int size, scc;
};
struct node2 { // j.w.
    node2 *parent; // poczatkowa wartosc: this
    int size;      // poczatkowa wartosc: 1
};

// Operacje na zbiorach rozlacznych
template<class T>
T *set_find(T *p) { // znajduje reprezentanta
    if (p->parent != p) p->parent = set_find(p->parent);
    return p->parent;
}
template<class T>
T *set_union(T *p1, T *p2) { // laczy zbiory
    if (p1->size < p2->size) swap(p1, p2);
    p2->parent = p1;
    p1->size += p2->size;
    return p1;
}

// Operacje na kolejkach zlaczalnych
void tree_push(edge *p) {
    p->key += p->add;
    if (p->left) p->left->add += p->add;
    if (p->right) p->right->add += p->add;
    p->add = 0;
}
edge *tree_union(edge *p1, edge *p2) { // laczy kolejki
    if (!p1) return p2;
    if (!p2) return p1;
    if (p2->key+p2->add < p1->key+p1->add) swap(p1, p2);
    tree_push(p1);
    p1->right = tree_union(p1->right, p2);
    if (!p1->left || p1->left->len < p1->right->len) swap(p1->left, p1->right);
    p1->len = p1->right ? p1->right->len+1 : 1;
    return p1;
}
edge *tree_extract(edge *p) { // usuwa z kolejki element najmniejszy
    tree_push(p);
    return tree_union(p->left, p->right);
}
void tree_add(edge *p, int x) { // dodaje x do wszystkich wartosci w kolejce
    if (p) p->add += x;
}

int n, m;         // IN: liczba wierzcholkow, liczba krawedzi
edge edges[MAXM]; // IN: tablica wszystkich krawedzi
node1 scc_set[MAXN];
node2 wcc_set[MAXN];
int upper[2*MAXN], lower[2*MAXN];
edge *adj[2*MAXN];
edge *res[2*MAXN]; // OUT: krawedz do rodzica w drzewie (korzen ma NULL)

int compute_branching() { // zwraca wage drzewa
    FOR(i,0,n) {
        scc_set[i].parent = scc_set+i;
        scc_set[i].size = 1;
        scc_set[i].scc = i;
        wcc_set[i].parent = wcc_set+i;
        wcc_set[i].size = 1;
        upper[i] = lower[i] = -1;
        adj[i] = res[i] = 0;
    }
    FOR(j,0,m) {
        edges[j].left = edges[j].right = 0;
        edges[j].len = 1;
        edges[j].add = 0;
        adj[edges[j].v] = tree_union(adj[edges[j].v], edges+j);
    }
    int scc_c=n, value=0;
    FOR(i,0,n) {
        int c = set_find(scc_set+i)->scc;
        while (adj[c] && !res[c]) {
            edge *e = adj[c];
            adj[c] = tree_extract(adj[c]);
            node1 *s1 = set_find(scc_set+e->v), *s2 = set_find(scc_set+e->u);
            if (s1==s2) continue;
            res[c] = e;
            value += e->key;
            tree_add(adj[c], -e->key);
            node2 *w1 = set_find(wcc_set+e->v), *w2 = set_find(wcc_set+e->u);
            if (w1!=w2) { set_union(w1, w2); continue; }
            upper[c] = scc_c;
            do {
                e = res[s2->scc];
                upper[s2->scc] = scc_c;
                adj[c] = tree_union(adj[c], adj[s2->scc]);
                s1 = set_union(s1, s2);
                s2 = set_find(scc_set+e->u);
            } while (s1!=s2);
            s1->scc = scc_c;
            upper[scc_c] = lower[scc_c] = -1;
            adj[scc_c] = adj[c];
            res[scc_c] = 0;
            c = scc_c++;
        }
    }
    FORD(c,scc_c,n) {
        if (lower[c]==-1)
          for (int i=res[c]->v; i!=c; i=upper[i]) lower[upper[i]] = i;
        res[lower[c]] = res[c];
    }
    return value;
}
