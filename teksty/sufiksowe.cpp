/* Marek Cygan
 * Budowanie drzewa sufiksowego, tablic SUF, SUF-odwrotnej i LCP
 * wraz z kodem testujacym i demonstrujacym dzialanie procedur
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>
#include <iterator>
#include <map>
#include <string>
#include <vector>
using namespace std;

#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)

struct STedge;
struct STvertex{
  map<char,STedge> g; //krawedzie do synow
  STvertex *f; //suffix link
  int numer; //numer sufiksu (0 to cale slowo, -1 oznacza ze wierzcholek nie jest lisciem)
};
struct STedge{
  int l,r; //x[l]..x[r] to fragment tekstu reprezentujacy krawedz
  STvertex *v;
};

STvertex *rOOT;
const char *tEKST;
int lISCIE; //liczba utworzonych lisci

inline void Canonize(STedge &kraw, const char *x){
  if (kraw.l <= kraw.r){
    STedge e = kraw.v->g[x[kraw.l]];
    while (e.r - e.l <= kraw.r - kraw.l){
      kraw.l += e.r - e.l + 1;
      kraw.v = e.v;
      if (kraw.l <= kraw.r) e = kraw.v->g[x[kraw.l]];
    }
  }
}

inline bool Test_and_split(STvertex* &w, const STedge &kraw){
  w = kraw.v;
  if (kraw.l <= kraw.r){
    char c = tEKST[kraw.l];
    STedge e = kraw.v->g[c];
    if (tEKST[kraw.r + 1] == tEKST[e.l + kraw.r - kraw.l + 1]) return true;
    w = new STvertex; w->numer = -1;
    kraw.v->g[c].r = e.l + kraw.r - kraw.l;
    kraw.v->g[c].v = w;
    e.l += kraw.r - kraw.l + 1;
    w -> g[tEKST[e.l]] = e;
    return false;
  } 
  return kraw.v->g.find(tEKST[kraw.l]) != kraw.v->g.end();
}

void Update(STedge &kraw, int n){
  STvertex *oldr = rOOT, *w;
  while (!Test_and_split(w, kraw)){
    STedge e;
    e.v = new STvertex; e.l = kraw.r + 1; e.r = n - 1;
    e.v->numer = lISCIE++;
    w->g[tEKST[kraw.r + 1]] = e;
    if (oldr != rOOT) oldr->f = w;
    oldr = w;
    kraw.v = kraw.v->f;
    Canonize(kraw, tEKST);
  }
  if (oldr != rOOT) oldr->f = kraw.v;
}

STvertex* Create_suffix_tree(const char *x, int n){
  STvertex *top; //pinezka
  STedge e;
  top = new STvertex; rOOT = new STvertex; tEKST = x;
  top->numer = rOOT->numer = -1;
  e.v = rOOT; lISCIE = 0;
  for (int i=0; i<n; ++i){
    e.r = -i; e.l = -i; top->g[x[i]] = e;
  }
  rOOT->f = top;
  e.l = 0; e.v = rOOT;
  REP(i,n){
    e.r = i - 1; Update(e, n); 
    e.r++; Canonize(e, x);
  }
  return rOOT;
}

void STDelete(STvertex *w){
  FOREACH(it,w->g) STDelete(it->second.v);
  delete w;
}

// Wyliczanie tablicy SUF
int Create_suftab(STvertex *w, int *suftab){
  if (w->numer != -1){*suftab = w->numer; return 1;}
  int acc = 0; FOREACH(it, w->g) acc += Create_suftab(it->second.v, suftab + acc);
  return acc;
}

// Wyliczanie tablic: SUF, SUF-odwrotnej i LCP
void Create_suffix_arrays(STvertex *root, const char *x, int *suftab, int *revsuf, int *lcp){
  int n = Create_suftab(root, suftab), acc = 0;
  REP(i,n) revsuf[suftab[i]] = i;
  lcp[0] = 0;
  REP(i,n){
    if (acc > 0) acc--;
    if (revsuf[i] == 0) acc = 0; else { 
      int pos = revsuf[i];
      while (x[i + acc] == x[suftab[pos - 1] + acc]) acc++;
    }
    lcp[revsuf[i]] = acc; 
  }
}

// Funkcja sprawdza, czy slowo s jest podslowem slowa x, ktorego drzewem sufiksowym
// jest r.
bool Find(const char *s, STvertex *r, const char *x){
  int i=0, n=strlen(s);
  while (i<n){
    if (r->g.find(s[i]) == r->g.end()) return false;
    STedge e = r->g[s[i]];
    for (int j = e.l; j <= e.r; ++j){
     if (i == n) return true;
     if (s[i++] != x[j]) return false;
    }
    r = e.v;
  }
  return true;
}

#define N 200000

// Funkcja main z kodem testujacym i prezentujacym dzialanie
int main(){
  string x; //napis dla ktorego budujemy drzewo sufiksowe
  int n, suftab[N], revsuf[N], lcp[N];
  x = "abcabcaabbcc~";
  n = x.size();
  STvertex *r = Create_suffix_tree(x.c_str(), n);

  printf("%d %d %d\n", Find("abcaa", r, x.c_str()), Find("abcd", r, x.c_str()), Find("abcabcaabbcc", r, x.c_str()));
  
  Create_suffix_arrays(r, x.c_str(), suftab, revsuf, lcp);
  REP(i,n) printf("i = %d, suftab[i] = %d, lcp[i] = %d, revsuf[i] = %d\n", i, suftab[i], lcp[i], revsuf[i]);
  STDelete(r);
  return 0;
}
