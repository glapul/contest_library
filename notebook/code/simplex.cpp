/* SIMPLEX
   Minimalizuje CX przy ograniczeniach AX=B, X>=0
   Zalozenie: B>=0
   Uwaga: Ograniczenia w postaci nierownosci mozna zamienic na rownania 
          przez wprowadzenie dodatkowych zmiennych
*/
// Bartosz Walczak

const int MAXM = 100, MAXN = 100; // maksymalna liczba ograniczen i zmiennych

typedef double K;
const K EPS = 1e-9;

int m, n;               // IN: liczba ograniczen i liczba zmiennych
K A[MAXM+1][MAXN+MAXM]; // IN: A[m x n] Uwaga: A i B zmieniaja sie!
K B[MAXM+1];            // IN: B[m]     Dodatkowe pola tablic A i B nie maja
K C[MAXN];              // IN: C[n]     znaczenia na wejsciu, ale sa uzywane
K X[MAXN];              // OUT: X[n]    w algorytmie
int base[MAXM];

bool optimize(int last) {
    for (;;) {
        int curj=last;
        FOR(j,0,last) if (A[m][j]<=-EPS) { curj=j; break; }
        if (curj==last) return true; // znaleziono rozwiazanie
        int curi;
        K tmp=INFINITY;
        FOR(i,0,m) {
            if (base[i]>=last && fabs(A[i][curj])>=EPS)
              { curi=i; tmp=0.0; break; }
            else if (A[i][curj]>=EPS) {
                K r=B[i]/A[i][curj];
                if (r<tmp) { curi=i; tmp=r; }
            }
        }
        if (tmp==INFINITY) return false; // rozwiazanie nieograniczone
        base[curi]=curj;
        tmp=A[curi][curj];
        FOR(j,0,last) A[curi][j]/=tmp;
        B[curi]/=tmp;
        FOR(i,0,m+1) if (i!=curi) {
            tmp=A[i][curj];
            FOR(j,0,last) A[i][j]-=A[curi][j]*tmp;
            B[i]-=B[curi]*tmp;
        }
    }
}

K simplex() { // zwraca optymalna wartosc
    FOR(i,0,m+1) { fill_n(A[i]+n, m, 0.0); A[i][n+i]=1.0; base[i]=n+i; }
    fill_n(A[m], n+m, 0.0);
    FOR(i,0,m) FOR(j,0,n) A[m][j]-=A[i][j];
    optimize(m+n); // powinno zawsze zwrocic true
    FOR(i,0,m) if (base[i]>=n && B[i]>=EPS) return INFINITY; // brak rozwiazan
    copy(C, C+n, A[m]);
    FOR(i,0,m) if (base[i]<n)
      { K tmp=A[m][base[i]]; FOR(j,0,n) A[m][j]-=A[i][j]*tmp; }
    if (!optimize(n)) return -INFINITY; // rozwiazanie nieograniczone
    fill_n(X, n, 0.0);
    K res=0.0;
    FOR(i,0,m) if (base[i]<n) { X[base[i]]=B[i]; res+=C[base[i]]*B[i]; }
    return res;
}
