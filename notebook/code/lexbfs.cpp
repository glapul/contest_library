/* LEX-BFS I ZAWEZANIE PODZIALU. Rozpoznawanie grafow cieciwowych
   1. lex_bfs  - oblicza porzadek odwrotny Lex-BFS wierzcholkow
   2. test_peo - sprawdza czy obliczony porzadek to Perfect Elimination Order
                 grafu cieciwowego                                             */

// Bartosz Walczak

template<class Iter> inline Iter PREV/*NEXT*/(Iter i) { return --i/*++i*/; }

struct clas;
struct elem { // element klasy podzialu
    int v; list<clas>::iterator c; // numer elementu, iterator klasy
    elem(int vi, list<clas>::iterator ci):v(vi), c(ci) {}
};
struct clas { // klasa podzialu
    list<elem> L; int label; // lista elementow, pomocnicza etykieta
    clas(int li):label(li) {}
};

/* Zawezanie podzialu: umieszcza nowa klase elementu i przed stara
   Mozna zmienic tak, zeby umieszczal za stara                                */
void refine(list<clas> &C, list<elem>::iterator i, int lab) {
    list<clas>::iterator c=i->c;
    if (c->label!=lab) { C.insert(c/*NEXT(c)*/, clas(lab)); c->label=lab; }
    i->c = PREV(c)/*NEXT(c)*/;
    i->c->L.splice(i->c->L.end(), c->L, i);
    if (c->L.empty()) C.erase(c);
}

const int MAXN = 100; // maksymalna liczba wierzcholkow

int n;               // IN: liczba wierzcholkow
list<int> adj[MAXN]; // IN: lista sasiedztwa
int order[MAXN];     // OUT: porzadek Lex-BFS
int label[MAXN];     // OUT: pozycja wierzcholka w porzadku Lex-BFS
list<elem>::iterator iter[MAXN];

void lex_bfs() { // Lex-BFS
    fill_n(label, n, -1);
    list<clas> C; C.push_front(clas(-1));
    clas *c = &C.front();
    FOR(i,0,n) iter[i] = c->L.insert(c->L.end(), elem(i, C.begin()));
    FORD(cur,n,0) {
        c = &C.front();
        int v = c->L.front().v; c->L.pop_front();
        if (c->L.empty()) C.pop_front();
        order[cur]=v; label[v]=cur;
        FORE(i,adj[v]) if (label[*i]==-1) refine(C, iter[*i], cur);
    }
}

int par[MAXN]; // OUT: pierwszy prawy sasiad (-1 - brak)
int cnt[MAXN]; // OUT: liczba prawych sasiadow

bool test_peo() { // jesli porzadek jest PEO, zwraca true i oblicza par, cnt
    fill_n(par, n, -1);
    FOR(i,0,n) {
        int v=order[i]; par[v]=-1; cnt[v]=0;
        FORE(j,adj[v]) if (label[*j]>i) { par[*j]=v; ++cnt[v]; }
                       else if (par[*j]==-1) par[*j]=v;
        FORE(j,adj[v]) if (par[*j]==v && label[*j]<i)
          FORE(k,adj[*j]) if (label[*k]>i && par[*k]!=v) return false;
    }
    return true;
}
