/* Marek Cygan
 * Algorytm Aho-Corasick
 * wersja na mapie
 * Wyszukiwanie wielu wzorcow w jednym tekscie
 * tutaj dla kazdego trzeba powiedziec czy wystepuje w tekscie
 * w niektorych przypadkach tego algorytmu trzeba jeszcze 
 * miec jedna funkcje w wezle mowiaca ktore wzorce w tym momencie
 * dopasowaly
 * w zadaniu slowa skladaja sie z literek a-z oraz A-Z
 */
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
using namespace std;

typedef vector<int> VI;
typedef vector<VI> VVI;
typedef long long LL;
typedef vector<LL> VLL;
typedef vector<double> VD;
typedef vector<string> VS;
typedef pair<int,int> PII;
typedef vector<PII> VPII;
typedef istringstream ISS;

#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (i=0; i<n; ++i)
#define FOR(var,pocz,koniec) for (var=pocz; var<=koniec; ++var)
#define FORD(var,pocz,koniec) for (var=pocz; var>=koniec; --var)
#define FOREACH(it,X) for (__typeof(X.begin()) it = X.begin(); it != X.end(); ++it)
#define PB push_back
#define PF push_front
#define MP(a,b) make_pair(a,b)
#define ST first
#define ND second
#define SIZE(x) (int)x.size()

struct wezel{
  wezel *p,*parent;
  bool vis,koniec;
  char lit;
  map<char,wezel*> syn;
} *root;

const int N=200000;
int l_wzorcow;
char tekst[N];

wezel* nowy(wezel *par,char c)
{
  wezel *x;
  x=new(wezel);
  x->vis=false;
  x->koniec=false;
  x->parent=par;
  x->lit=c;
  (x->syn).clear();
  return x;
}

void trim(char *s)
{
  int i,x=strlen(s);
  REP(i,x) if (s[i]=='\n' || s[i]=='\r' || s[i]=='\t') s[i]=0;
};

wezel* konce[N];

void dodaj(char *s,int nr)
{
  int i=0,m=strlen(s);
  wezel *x;
  x=root;
  while (i<m && (x->syn.find(s[i])!=x->syn.end())) {x=x->syn[s[i++]];}
  while (i<m)
  { (x->syn[s[i]])=nowy(x,s[i]);
    x=x->syn[s[i++]];
  }
  x->koniec=true;
  konce[nr]=x;
}

void buduj()
{
  char c;
  deque<wezel*> q;
  root->p=root;
  FOREACH(it,root->syn) q.PB(it->ND);
  while (!q.empty())
  {
    wezel *x=q.front(); q.pop_front();
    FOREACH(it,x->syn) q.PB(it->ND);
    if (x->parent==root)
    {
      x->p=root;
    } else
    {
      wezel *pom=x->parent->p;
      c=x->lit;
      while (pom!=root && (pom->syn.find(c)==pom->syn.end())) pom=pom->p;
      if (pom->syn.find(c)!=pom->syn.end()) pom=pom->syn[c];
      x->p=pom;
    }
  }
}

void szukaj()
{ int i,m=strlen(tekst);
  char *s=tekst;
  wezel *pos;
  pos=root;
  REP(i,m)
  { while (pos!=root && pos->syn.find(s[i])==pos->syn.end()) pos=pos->p;
    if (pos->syn.find(s[i])!=pos->syn.end()) pos=pos->syn[s[i]];
    pos->vis=true;
  }
}

void wypisz()
{
  queue<wezel*> q;
  vector<wezel*> v;
  char c;
  FOREACH(it,root->syn) q.push(it->ND);
  while (!q.empty())
  {
    wezel *x=q.front(); q.pop();
    v.PB(x);
    FOREACH(it,x->syn) q.push(it->ND);
  }
  int i;
  FORD(i,SIZE(v)-1,0)
  if (v[i]->vis) v[i]->p->vis=true;
  REP(i,l_wzorcow) if (konce[i]->vis) printf("y\n"); else printf("n\n");
    
}

int main()
{
  int k,iii;
  char txt[N];
  fgets(txt,N-1,stdin);
  sscanf(txt,"%d",&k);
  REP(iii,k)
  {
    int i;
    fgets(tekst,N-1,stdin); trim(tekst);
    fgets(txt,N-1,stdin);
    sscanf(txt,"%d",&l_wzorcow);
    root=nowy(NULL,'0');
    REP(i,l_wzorcow)
    {
      fgets(txt,N-1,stdin); trim(txt);
      dodaj(txt,i);
    }
    buduj();
    szukaj();
    wypisz();
  }
  return 0;
}
