//DRZEWO SUFIKSOWE O(n)
//TABLICA SUFIKSOWA O(n)
//Maciek Wawro

const int K = 3;  // Wielkość alfabetu ([0..K-1])

struct Node{
  Node *next[K], *s;
  int leaf,L,R; // [L,R] odpowiedni zakres w wejściowym słowie
                // [-1,-1] dla roota
                // leaf -nr sufiksu, -1 dla węzłów wewnętrznych
  Node(int le, int l,int r):leaf(le),L(l),R(r){
    REP(i,K)next[i] = NULL;
  }
  ~Node(){
    REP(i,K)if(next[i])
      delete next[i];
  }
  int len(){return R-L+1;}
};

//IN: N - długość słowa
//IN: S - słowo; S[N-1]>S[i] dla i = 0,...,N-2 !
//OUT: Korzeń drzewa sufiksowego
Node* suffixTree(char* S, int N){
  Node* root = new Node(-1,-1,-1);
  root->s = root;
  Node* cur = root, *next, *temp, *added;
  int dep = 0, suf = 0, split;
  REP(i,N){
    added = NULL;
    while(suf<=i){
      while((next = cur->next[S[suf+dep]]) && next->len() + dep <= i-suf){
        cur = next; dep += next->len();
      }
      if(!next){
        cur->next[S[i]] = temp = new Node(suf,i,N);
        if(added) added->s = cur; added = NULL;
      }else if(S[split = next->L + i-suf-dep] != S[i]){
        cur->next[S[suf+dep]] = temp = new Node(-1, next->L, split - 1);
        next->L = split;        
        temp->next[S[split]] = next;
        temp->next[S[i]] = new Node(suf, i, N);
        if(added) added->s = temp; added = temp;              
      }else{
        if(added) added->s = cur;
        break;                  
      }
      if(cur != root){cur = cur->s; --dep;}      
      suf++;
    }
  }    
  return root;
}

const int MAXN = 1<<21;
int _count[1<<21];
void countSort(int* in, int* out, const int* key, int N, int M){
  fill_n(_count, M, 0);
  REP(i,N)++_count[key[in[i]]];
  FOR(i,1,M)_count[i] += _count[i-1];
  FORD(i,N,0)out[--_count[key[in[i]]]] = in[i];
}

int temp[MAXN], s0[MAXN], s12[MAXN],_rank[MAXN], recOut[MAXN];
const int* _s;
inline bool cmp(int u, int v){
  while(true){
    if(_s[u] != _s[v]) return _s[u]<_s[v];
    if((u%3) && (v%3)) return _rank[u] < _rank[v];
    ++u;++v;
  }
}

/*IN: N - długość
  IN: s - string   
  IN: K - zakres alfabetu
  OUT: out - tablica sufiksowa
 !!ZAŁOŻENIA: N>=2, 0<s[i]<K, s[N]=s[N+1]=s[N+2]=0!! */
void suffixArray(const int* s, int N, int* out, int K){
  int n0 = (N+2)/3, n1 = (N+1)/3, n12 = 0; 
  REP(i,N)if(i%3)temp[n12++] = i;

  countSort(temp, s12, s+2, n12, K);
  countSort(s12, temp, s+1, n12, K);
  countSort(temp, s12, s,   n12, K);    

  int recIn[n12+5], cnt = 2;  
  REP(i,n12){
    if(i>0 && !equal(s+s12[i-1], s+s12[i-1]+3, s+s12[i]))++cnt;
    recIn[s12[i]%3==1?s12[i]/3:s12[i]/3+n1+1] = cnt;  
  }  
  
  if(cnt != n12+1){
    REP(i,3) recIn[n12+1+i] = 0;  
    recIn[n1] = 1;    
    suffixArray(recIn, n12+1, recOut, cnt+1);
    FOR(i,1,n12+1)s12[i-1] = recOut[i]<n1? 3*recOut[i]+1 : 3*(recOut[i]-n1)-1;
  }  
  
  REP(i,n12)_rank[s12[i]] = i+1;  
  _rank[N] = 0;

  REP(i,n0)s0[i] = 3*i;
  countSort(s0,temp,_rank+1,n0,n12+2);   
  countSort(temp,s0,s,n0,K);  

  _s = s;
  merge(s12, s12+n12, s0, s0+n0, out, cmp);  
}

/*IN: sA - tablica sufiksowa
  IN: invSA - odwrotność tablicy sufiksowej
  IN: N - długość
  IN: text - string; T[N]!=T[i] dla i<N!!
  OUT: lcp */ 
void computeLCP(const int* sA, const int* invSA, int N, int* text, int* lcp){
  int cur = 0;
  REP(i,N){
    int j = invSA[i];
    if(!j)continue;
    int k = sA[j-1];
    while(text[k+cur] == text[i+cur])cur++;
    lcp[j] = cur;
    cur = max(0,cur-1);
  }
}
