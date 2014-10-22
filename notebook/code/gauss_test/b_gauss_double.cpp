#define debug if(0)
#include <cstdio>
#include <cassert>
#include <map>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

#define REP(i,n) for(int i = 0; i < int(n); i++)
#define FOR(i,b,e) for(int i = int(b); i != int(e); i++)
#define FORD(i,a,b) for(int i = int(a)-1; i>=(b); i--)
#define FOREACH(i,v) for(__typeof((v).begin()) i = (v).begin(); i != (v).end(); i++)
#define pb push_back
#define mp make_pair
#define st first
#define nd second

typedef long long LL;

namespace gauss {
const int N = 110;
const int M = 110;
 
const double EPS = 1e-9;        // [R]
 
// INPUT, jest psuty! (psuty, nie pusty!)
double A[N][M], B[N];           // [R]

// OUTPUT
double X[M];    // [R]

/* Rozwiazuje rownanie AX = B
   Zwraca wymiar przestrzeni rozwiazan (-1 - brak rozwiazan) */
int gauss(int n, int m) {
    int dim=0, P[m]; REP(i,m) P[i]=i;
    REP(i,n) {
        int r=i,c=i;
        FOR(j,i,n) FOR(k,i,m) {
            if(fabs(A[j][k]) > fabs(A[r][c])) {r=j; c=k; }
        }
        dim = i+1; 
        if (r != i) { 
            REP(j,m)                        // [Zp], [Zn], [R]
                swap(A[i][j], A[r][j]); 
            swap(B[i], B[r]); 
        }
        if (c != i) { 
            REP(j,n) {
                swap(A[j][i], A[j][c]);                  // [Zp], [Zn], [R]
            }
            swap(P[i], P[c]); 
        }
        FOR(j,i+1,n) {
            double d = A[j][i] / A[i][i];                       // [R]
            FOR(k,i,m) A[j][k] = (A[j][k]-d*A[i][k]) /*%MOD*/;  // [Zp], [R]
            B[j] = (B[j]-d*B[i])                     /*%MOD*/;  // [Zp], [R]
        }
    }
    FOR(i,dim,m) X[i] = 0;
    FORD(i,dim,0) {
        FOR(j,i+1,m) {
            B[i] = (B[i]-A[i][j]*X[j]) /*%MOD*/;    // [Zp], [Zn], [R]
        }
        X[i] = B[i] / A[i][i];                                  // [R]
    }
    REP(i,m) REP(j,m) if (P[j]==i) {
        swap(P[j], P[i]);
        swap(X[j], X[i]);
        break;
    }
    return m-dim;
}
}; // ns

namespace aho {
const int maxn = 110;

int n;
int adj[maxn][2];
string word[maxn];
map<string, int> byWord;

int newState(string s) {
    adj[n][0] = adj[n][1] = -1;
    word[n] = s;
    byWord[s] = n;
    return n++;
}

int addWord(string s) {
    int i = 0;
    FOREACH (c, s) {
        int v = adj[i][*c - '0'];
        if (v == -1) v = newState(word[i] + *c);
        adj[i][*c - '0'] = v;
        i = v;
    }
    return i;
}

void init() {
    n = 0;
    newState("");
}

void generate() {
    debug {
        REP(i,n) printf("%d: %d %d\n", i, adj[i][0], adj[i][1]);
    }
    REP (i, n) REP (j, 2) if(adj[i][j] == -1) {
        string s = word[i] + char('0' + j);
        while (byWord.find(s) == byWord.end()) {
            s = s.substr(1);
        }
        adj[i][j] = byWord[s];
    }
    debug {
        REP(i,n) printf("%d: %d %d\n", i, adj[i][0], adj[i][1]);
    }
}

}; // ns

string scanWord() {
    char* buf = new char[110];
    scanf("%s", buf);
    return string(buf);
}

void equalsVarsAvg(int a, int b, int c) {
    debug printf("A%d = A%d + A%d\n", a, b, c);
    assert(b != c);
    REP (i, aho::n) gauss::A[a][i] = 0;
    gauss::A[a][a] = 1.0;
    gauss::A[a][b] += -0.5;
    gauss::A[a][c] += -0.5;
    gauss::B[a] = 0;
}

void equalsNumber(int a, long double b) {
    debug printf("A%d = %Lf\n", a, b);
    REP (i, aho::n) gauss::A[a][i] = 0;
    gauss::A[a][a] = 1.0;
    gauss::B[a] = b;
}

long double solve() {
    aho::init();
    string word1 = scanWord();
    string word2 = scanWord();
    if (word1.find(word2) != string::npos) return 0;
    if (word2.find(word1) != string::npos) return 1;

    int first = aho::addWord(word1);
    int second = aho::addWord(word2);
    aho::generate();
    //if (aho::n >= 8 && word1[0] == '1') assert(false);
    if (aho::n >= 8 && word1.length() != 1) {
        //assert(false);
    }
    REP (i, aho::n) {
        if (i == first) equalsNumber(i, 1.0);
        else if (i == second) equalsNumber(i, 0.0);
        else equalsVarsAvg(i, aho::adj[i][0], aho::adj[i][1]);
    }
    int gaussResult = gauss::gauss(aho::n, aho::n);
    debug printf("gaussReuslt %d\n", gaussResult);
    assert(gaussResult == 0);
    return gauss::X[0];
}

int main() {
    printf("%.15Lf\n", solve());
    return 0;
}
