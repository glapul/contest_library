// SKOJARZENIE O MINIMALNEJ WADZE w grafie dwudzielnym O(V^3)
// Bartosz Walczak

const int MAXN = 100; // maksymalne liczby wierzcholkow po obu stronach
const int INF = 1e9;
int n1, n2;             // IN: liczby wierzcholkow po obu stronach
int weight[MAXN][MAXN]; // IN: macierz wag krawedzi (INF oznacza brak)
int mate1[MAXN], mate2[MAXN]; // OUT: wierzcholki skojarzone (-1 oznacza brak)
int old_dist1[MAXN], dist1[MAXN], dist2[MAXN], prev2[MAXN];

int compute_bwm() { // zwraca wage skojarzenia
   REP(a,n1) {
      mate1[a] = -1;
      old_dist1[a] = 0;
   }
   REP(b,n2) {
      mate2[b] = -1;
      dist2[b] = INF;
      REP(a,n1) if (weight[a][b]<dist2[b]) {
         dist2[b] = weight[a][b];
         prev2[b] = a;
      }
   }
   int res = 0;
   for (;;) {
/* Jezeli szukamy skojarzenia licznosci k o minimalnej wadze, te petle wykonac
   dokladnie k razy                                                           */
      int cur, min_dist = INF;
      REP(b,n2) if (mate2[b]==-1 && dist2[b]<min_dist) {
         cur = b;
         min_dist = dist2[b];
      }
/* Jezeli szukamy skojarzenia dowolnej licznosci o minimalnej wadze, poprawic
   ponizszy warunek na: min_dist>=0                                           */
      if (min_dist==INF) break;
      res += min_dist;
      while (cur!=-1) {
         int next = mate1[prev2[cur]];
         mate2[cur] = prev2[cur];
         mate1[prev2[cur]] = cur;
         cur = next;
      }
      REP(a,n1) dist1[a] = mate1[a]==-1 ? 0 : INF;
      REP(b,n2) dist2[b] = INF;
      for (;;) {
         min_dist = INF;
         REP(a,n1) if (dist1[a]!=INF && dist1[a]-old_dist1[a]<min_dist) {
            cur = a;
            min_dist = dist1[a]-old_dist1[a];
         }
         if (min_dist==INF) break;
         REP(b,n2) if (b!=mate1[cur] && weight[cur][b]!=INF &&
          dist1[cur]+weight[cur][b]<dist2[b]) {
            dist2[b] = dist1[cur]+weight[cur][b];
            prev2[b] = cur;
            if (mate2[b]!=-1) dist1[mate2[b]] = dist2[b]-weight[mate2[b]][b];
         }
         old_dist1[cur] = dist1[cur];
         dist1[cur] = INF;
      }
   }
   return res;
}

// ALGORYTM WĘGIERSKI O(n^3) [najdroższe skojarzenie doskonałe]
// Adam Polak

const int N = 500;
const int INF = 1e9;

int n;                  // INPUT
int w[N][N];            // INPUT
int m1[N], m2[N];       // OUTPUT
int l1[N], l2[N], p[N], slack[N];
bool blue[N];

int hungarian() {
    REP(i,n) { m1[i] = m2[i] = p[i] = -1; l1[i] = l2[i] = -INF; }
    REP(i,n) REP(j,n) {
        l1[i]=max(l1[i],w[i][j]);
        l2[j]=max(l2[j],w[i][j]);
    };
    REP(k,n) {
        REP(i,n) { slack[i] = INF; p[i] = -1; }
        REP(i,n) if (blue[i] = (m1[i]==-1))
            REP(j,n) slack[j] = min(slack[j], l1[i]+l2[j]-w[i][j]);
        int u;
        for(;;) {
            u = min_element(slack,slack+n)-slack;
            if (slack[u]) {
                int d = slack[u];
                REP(i,n) {
                    if (blue[i]) l1[i] -= d;
                    if (slack[i] == INF) l2[i] += d; else slack[i] -= d;
                }
            } else {
                REP(i,n) if (blue[i]&&w[i][u]==l1[i]+l2[u]) { p[u]=i; break; }
                slack[u]=INF;
                if (m2[u] == -1) break;
                blue[m2[u]]=true;
                REP(i,n) if (slack[i]!=INF) 
                    slack[i]=min(slack[i], l1[m2[u]]+l2[i] - w[m2[u]][i]);
            }
        }
        while(u != -1) { m2[u] = p[u]; swap(u, m1[p[u]]); }
    }
    /* Jeżeli wynik może przekroczyć 10^9 zmienić result i typ zwracany na LL */
    int result = 0;
    REP(i,n) result += w[i][m1[i]];
    return result;
}
