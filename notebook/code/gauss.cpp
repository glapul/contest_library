// Eliminacja Gaussa O(nm^2)
// Linie oznaczone [Z2], [Zp], [Zn], [R] sa specyficzne dla
// poszczegolnych cial/pierscieni.
// Adam Polak
// Jezeli jestesmy w ciele liczb rzeczywistych, przepisujemy:
// [R] oraz [R-nieosobl] jezeli wiemy ze uklad ma jednoznaczne rozwiazanie,
// [R] oraz [R-osobl] jezeli tego nie wiemy.
const int N = 100;
const int M = 100;

typedef unsigned long long ULL; // [Z2]
const double EPS = 1e-9;        // [R-osobl]

// INPUT, jest psuty! (psuty, nie pusty!)
int A[N][M], B[N];              // [Zp], [Zn]
ULL A[N][(M+63)/64]; bool B[N]; // [Z2]
double A[N][M], B[N];           // [R]

int MOD;                        // [Zp], [Zn]

// OUTPUT
int X[M];       // [Zp], [Zn]
bool X[M];      // [Z2]
double X[M];    // [R]

/* Rozwiazuje rownanie AX = B
   Zwraca wymiar przestrzeni rozwiazan (-1 - brak rozwiazan) */
int gauss(int n, int m) {
    int dim=0, P[m]; REP(i,m) P[i]=i;
    REP(i,n) {
        int r=i,c=i;
        FOR(j,i,n) FOR(k,i,m) {
            if (A[j][k]!=0) { r=j; c=k; goto found; }             // [Zp], [Zn]
            if (fabs(A[j][k]) > EPS) { r=j; c=k; goto found; }          // [R-osobl]
            if (fabs(A[j][k]) > fabs(A[r][c])) { r=j; c=k; }            // [R-nieosobl]
            if (A[j][k/64]&(1ULL<<(k&63))) { r=j; c=k; goto found; }    // [Z2]
        }
        break;                    // [Zp], [Zn], [Z2], [R-osobl]
        found:                    // [Zp], [Zn], [Z2], [R-osobl]
        dim = i+1;
        if (r != i) {
            REP(j,m)                        // [Zp], [Zn], [R]
            REP(j,(m+63)/64)                // [Z2]
                swap(A[i][j], A[r][j]);
            swap(B[i], B[r]);
        }
        if (c != i) {
            REP(j,n) {
                swap(A[j][i], A[j][c]);                  // [Zp], [Zn], [R]
                if ((((A[j][i/64]&(1ULL<<(i&63)))>>(i&63))) !=      // [Z2]
                        ((A[j][c/64]&(1ULL<<(c&63)))>>(c&63))) {    // [Z2]
                    A[j][i/64] ^= (1ULL<<(i&63));                   // [Z2]
                    A[j][c/64] ^= (1ULL<<(c&63));                   // [Z2]
                }                                                   // [Z2]
            }
            swap(P[i], P[c]);
        }
        FOR(j,i+1,n) {
            if (A[j][i/64]&(1ULL<<(i&63))) {            // [Z2]
                REP(k,(m+63)/64) A[j][k] ^= A[i][k];    // [Z2]
                if (B[i]) B[j] ^= 1   ;                 // [Z2]
            }                                           // [Z2]
            int d = (A[j][i] * inverse(A[i][i],MOD)) % MOD;     // [Zp]
            double d = A[j][i] / A[i][i];                       // [R]
            FOR(k,i,m) A[j][k] = (A[j][k]-d*A[i][k]) /*%MOD*/;  // [Zp], [R]
            B[j] = (B[j]-d*B[i])                     /*%MOD*/;  // [Zp], [R]
            while(A[j][i] != 0) {                               // [Zn]
                int d = A[j][i] / A[i][i];                      // [Zn]
                FOR(k,i,m) {                                    // [Zn]
                    A[j][k] = (A[j][k]-d*A[i][k]) % MOD;        // [Zn]
                    swap(A[j][k], A[i][k]);                     // [Zn]
                }                                               // [Zn]
                B[j] = (B[j]-d*B[i]) % MOD;                     // [Zn]
                swap(B[i], B[j]);                               // [Zn]
            }                                                   // [Zn]
        }
    }
    FOR(i,dim,n) if (B[i]!=0) return -1;    // [Z2], [Zp], [Zn]
    FOR(i,dim,n) if (fabs(B[i]) > EPS) return -1;       // [R-osobl]
    FOR(i,dim,m) X[i] = 0;
    FORD(i,dim,0) {
        FOR(j,i+1,m) {
            B[i] = (B[i]-A[i][j]*X[j]) /*%MOD*/;    // [Zp], [Zn], [R]
            B[i] ^= (X[j] && (A[i][j/64]&(1ULL<<(j&63))));      // [Z2]
        }
        X[i] = B[i];                                            // [Z2]
        X[i] = (inverse(A[i][i], MOD) * B[i]) % MOD;            // [Zp]
        int D = GCD(A[i][i], MOD);                              // [Zn]
        if (B[i] % D != 0) return -1;                           // [Zn]
        X[i] = (inverse(A[i][i]/D, MOD/D) * (B[i]/D)) % MOD;    // [Zn]
        X[i] = B[i] / A[i][i];                                  // [R]
    }
    REP(i,m) REP(j,m) if (P[j]==i) {
        swap(P[j], P[i]);
        swap(X[j], X[i]);
        break;
    }
    return m-dim;
}
