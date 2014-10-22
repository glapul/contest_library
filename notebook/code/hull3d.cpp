/* WYPUKLA OTOCZKA 3D w dwoch wersjach: O(n^2) i O(n log(n)) randomizowana
   O(n^2) jest szybsza przy rownomiernie rozlozonych punktach
   Uwaga: Konstruuje wypukla otoczke tylko jezeli punkty nie sa koplanarne    */

// Bartosz Walczak

const int MAXN = 100; // maksymalna liczba punktow

struct tri;

struct edge { // krawedz
    tri *t; int i; // wskaznik na druga sciane, indeks krawedzi na tej scianie
    edge(tri *ti, int ii):t(ti), i(ii) {}
    edge() {}
};

struct tri { // trojkatna sciana
    xyz *v[3], normal; // wierzcholki, normalna skierowana na zewnatrz
    edge e[3];         // krawedzie numerowane przeciwlegle do wierzcholkow
/* Wersja O(n log(n)):
    list<pair<int, list<tri*>::iterator> > L;                                 */
    bool mark;
    tri **self;
    void compute_normal() { normal=cross(*v[1]-*v[0], *v[2]-*v[0]); }
    bool visible(const xyz &p) const { return (p-*v[0])*normal>=EPS; }
};

inline edge *rev(edge *e) { return e->t->e+e->i; }
inline edge *next(edge *e) { return e->t->e+(e->i+1)%3; }

int n;             // IN: liczba punktow
xyz pts[MAXN];     // IN: punkty
int tc;            // OUT: liczba scian
tri *tris[3*MAXN]; // OUT: wskazniki na kolejne sciany
tri buf[3*MAXN];   // bufor zawierajacy sciany (niekoniecznie po kolei!)

tri *get_tri() {
    tris[tc]->mark=false;
    tris[tc]->self = tris+tc;
    return tris[tc++];
}
void put_tri(tri *t) {
    tris[--tc]->self = t->self;
    swap(tris[tc], *t->self);
}

/* Wersja O(n log(n)):
list<tri*> vis[MAXN];
int mark[MAXN];

void add_point(tri *t, int i) {
    if (t->visible(pts[i])) t->L.PB(MP(i, vis[i].insert(vis[i].end(), t)));
}                                                                             */

const int tri_adj[4][3] = { 1, 2, 3, 0, 3, 2, 0, 1, 3, 0, 2, 1 };
const int tri_rev[4][3] = { 0, 0, 0, 0, 2, 1, 1, 2, 1, 2, 2, 1 };

int compute_3dhull() { // zwraca wymiar
    int dim=0;
    FOR(i,1,n) if ((pts[i]-pts[0]).norm()>=EPS)
      { swap(pts[i],pts[1]); ++dim; break; }
    if (dim==0) return 0;
    FOR(i,2,n) if (cross(pts[1]-pts[0], pts[i]-pts[0]).norm()>=EPS)
      { swap(pts[i],pts[2]); ++dim; break; }
    if (dim==1) return 1;
    FOR(i,3,n) if (fabs(det(pts[1]-pts[0], pts[2]-pts[0], pts[i]-pts[0]))>=EPS)
      { swap(pts[i],pts[3]); ++dim; break; }
    if (dim==2) return 2;
    if (det(pts[1]-pts[0], pts[2]-pts[0], pts[3]-pts[0])<0) swap(pts[2],pts[3]);
    FOR(i,0,3*n) tris[i] = buf+i;
    tc=0;
    FOR(i,0,4) {
        tri *t=get_tri();
        FOR(j,0,3) {
            t->v[j]=pts+tri_adj[i][j];
            t->e[j]=edge(buf+tri_adj[i][j], tri_rev[i][j]);
        }
        t->compute_normal();
/* Wersja O(n log(n)):
        FOR(j,4,n) add_point(t, j);                                           */
    }
/* Wersja O(n log(n)):
    fill_n(mark, n, 0);
    int id=1;                                                                 */
    FOR(i,4,n) {
        edge *first, *cur;
// Wersja O(n^2):
        FOR(j,0,tc) tris[j]->mark=tris[j]->visible(pts[i]);
        FOR(j,0,tc) if (tris[j]->mark) FOR(k,0,3) if (!tris[j]->e[k].t->mark)
          { first=cur=tris[j]->e+k; goto label; }
/* Wersja O(n log(n)):
        FORE(j,vis[i]) (*j)->mark=true;
        FORE(j,vis[i]) FOR(k,0,3) if (!(*j)->e[k].t->mark)
          { first=cur=(*j)->e+k; goto label; }                                */
        continue;
label:  int ti=tc;
        do {
            tri *t1=cur->t, *t2=get_tri(); int i1=cur->i;
            t2->v[0]=pts+i; t2->v[1]=t1->v[(i1+2)%3]; t2->v[2]=t1->v[(i1+1)%3];
            t2->compute_normal();
            t2->e[0]=*cur;
            cur=rev(cur);
/* Wersja O(n log(n)):
            FORE(j,t1->L) { add_point(t2, j->FI); mark[j->FI]=id; }
            FORE(j,cur->t->L) if (mark[j->FI]!=id) add_point(t2, j->FI);
            ++id;                                                             */
            do cur=next(cur); while (cur->t->mark);
            t1->e[i1]=edge(t2, 0);
        } while (cur!=first);
        tri *last=tris[tc-1];
        for (; ti<tc; ++ti) {
            last->e[1]=edge(tris[ti], 2);
            tris[ti]->e[2]=edge(last, 1);
            last=tris[ti];
        }
// Wersja O(n^2):
        FOR(j,0,tc) if (tris[j]->mark) put_tri(tris[j--]);
/* Wersja O(n log(n)):
        FORE(j,vis[i]) put_tri(*j);
        FORD(j,ti,tc) {
            FORE(k,tris[j]->L) vis[k->FI].erase(k->SE);
            tris[j]->L.clear();
        }                                                                     */
    }
    return 3;
}
