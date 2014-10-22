/* Marek Cygan
 * Tymczasowa (nieprzetestowana dok³adnie) wersja programu konstruuj¹cego
 * graf pods³ów dla danego s³owa on-line.
 */
#include <cstdio>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;

#define REP(i,n) for (int i=0; i<n; ++i)
#define FOREACH(it,X) for (__typeof(X.begin()) it = (X.begin()); it != X.end(); ++it)
#define PB push_back
#define SIZE(x) (int)x.size()

struct edge{
  int v;
  bool solid;
  edge (){}
  edge (int a, bool b){
    v = a; solid = b;
  }
};

struct vertex{
  map<char, edge> son; //etykieta krawedzi, (numer wierzcholka, czy gruba krawedz)
  int suf; //suf
};

//tworzenie grafu podslow
vector<vertex> create_dawg(const char *s, int n){
  vector<vertex> dawg;
  dawg.reserve(2*n);
  dawg.PB(vertex());
  int root = 0, sink = 0;
  dawg[0].suf = -1; //NULL
  REP(i,n){
    char a = s[i];
    int new_sink = SIZE(dawg);
    dawg.PB(vertex());
    dawg[sink].son[a] = edge(new_sink, true);
    int w = dawg[sink].suf;
    while (w>=0 && dawg[w].son.find(a) == dawg[w].son.end()){
      dawg[w].son[a] = edge(new_sink, false); w = dawg[w].suf;
    }
    if (w == -1) dawg[new_sink].suf = root;
    else{
      edge e = dawg[w].son[a];
      int v = e.v;
      if (e.solid) dawg[new_sink].suf = v;
      else{
        int new_node = SIZE(dawg);
        dawg.PB(dawg[v]);
        FOREACH(it, dawg[new_node].son) it->second.solid = false;
        dawg[w].son[a] = edge(new_node, true);
        dawg[new_sink].suf = new_node;
        dawg[new_node].suf = dawg[v].suf;
        dawg[v].suf = new_node;
        w = dawg[w].suf;
        while (w >= 0 && !dawg[w].son[a].solid){
          dawg[w].son[a].v = new_node;
          w = dawg[w].suf;
        }
      }
    }
    sink = new_sink;
  }
  return dawg;
}

bool find(vector<vertex> &g, const char *s, int n){
  int v = 0;
  REP(i,n){
    if (g[v].son.count(s[i])) v=g[v].son[s[i]].v;
    else return false;
  }
  return true;
}

int main(){
  char s[2000000], wzor[1000];
  int d;
  scanf("%d",&d);
  while (d--){
    scanf("%s",s);
    vector<vertex> graf(create_dawg(s,strlen(s)));
    int q; scanf("%d",&q);
    while (q--){
      scanf("%s",wzor);
      printf("%s\n",find(graf,wzor,strlen(wzor))?"y":"n");
    }
  }
  return 0;
}
