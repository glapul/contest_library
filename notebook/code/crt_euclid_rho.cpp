// CHINSKIE TWIERDZENIE O RESZTACH
// + ALGORYTM EUKLIDESA
// Adam Polak
// + FAKTORYZACJA RHO POLLARDA
// Robet Obryk

/*  Poniższe kody operują od początku do końca na liczbach nieujemnych. */

typedef unsigned long long T;

T GCD(T a, T b) {
    while(b) { a%=b; swap(a,b); }
    return a;
}

/* gcd = ax - by; x,y >= 0 */
T eGCD(T a, T b, T &x, T &y) {
    if (!b) { x=1; y=0; return a; }
    T d = eGCD(b,a%b,y,x);
    y = a-x*(a/b)-y;
    x = b-x;
    return d;
}

T inverse(T a, T p) { T x,y; eGCD(a,p,x,y); return x % p; }

/*  x = a mod m, x = b mod n,  0 <= x < LCM(n,m)
 *  Jeśli n <= m, to w żadnym miejscu obliczenia nie wykraczają poza 
 *      max(LCM(n,m), 2n)                                                 */
T CRT(T a, T m, T b, T n) { 
    b = (b+n-(a%n))%n;
    T d = GCD(m,n);
    if (b%d) throw 0;
    return (((b/d)*inverse(m/d,n/d))%(n/d))*m+a;
}

T RHO(T n) {
    if (n%2 == 0) return 2;
    T x = 2, y = 2;
    do {
        x = (x*x+1)%n; // uzyj __uint128_t jesli n > 10^9
        y = (y*y+1)%n; // uzyj __uint128_t jesli n > 10^9
        y = (y*y+1)%n; // uzyj __uint128_t jesli n > 10^9
    } while (GCD(x+n-y, n) == 1);
    return GCD(x+n-y, n);
}
