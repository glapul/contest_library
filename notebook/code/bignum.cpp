/* ARYTMETYKA DUZYCH LICZB I FFT
   Funkcje operuja na przedzialach [b,e) w tablicy intow, gdzie b to najmniej
   znaczaca cyfa. Wynik zapisywany w przedziale (r,R), gdzie r to zwykle
   ostatni argument funkcji, R to wynik funkcji.                              
*/

// Arkadiusz Pawlik, Bartosz Walczak

const int BASE = 1000000000; // podstawa systemu pozycyjnego: FFT -> 100000
const int MAXSIZE = 100000;  // maksymalny rozmiar liczby

// Usuwanie wiodacych zer
inline int *strip(int *b, int *e) {
    while (e>b && !e[-1]) --e;
    return e;
}

int *input(int *r) { // UWAGA: funkcje i/o zaleza od bazy!
    static char buf[MAXSIZE*10];
    scanf("%s", buf);
    int len = strlen(buf), *r0=r;
    while (len) {
        int st = max(0, len-9/*liczba cyfr*/);
        int a=0;
        FOR(i,st,len) a = a*10+(buf[i]-'0');
        *r++ = a;
        len = st;
    }
    return strip(r0, r); // potrzebne, zeby dobrze wczytywalo zero
}
void output(int *b, int *e) {
    if (b==e) { printf("0"); return; }
    printf("%d", *--e);
    while (e-->b) printf("%09d", *e); // dostosowac liczbe cyfr
}

// Dodawanie malej liczby s>=0. Moze byc r=b1
inline int *add(int *b1, int *e1, int s, int *r) {
    while (b1!=e1) {
        s += *b1++;
        int t = (s>=BASE); *r++ = s-(BASE&-t); s=t;
    }
    if (s) *r++ = s;
    return r;
}

// Dodawanie. Moze byc r=b1 lub r=b2
inline int *add(int *b1, int *e1, int *b2, int *e2, int *r) {
    int s=0;
    while (b1!=e1 && b2!=e2) {
        s += *b1++ + *b2++;
        int t = (s>=BASE); *r++ = s-(BASE&-t); s=t;
    }
    if (b1!=e1) return add(b1, e1, s, r);
    else return add(b2, e2, s, r);
}

// Odejmowanie malej liczby s>=0. Zalozenie: a>=s. Moze byc r=b1
inline int *sub(int *b1, int *e1, int s, int *r) {
    int *r0=r; s=1-s;
    while (b1!=e1) {
        s += *b1++ + (BASE-1);
        int t = (s>=BASE); *r++ = s-(BASE&-t); s=t;
    }
    return strip(r0, r);
}

/* Odejmowanie. Zalozenie: n1>=n2. Moze byc r=b1 lub r=b2
   Uwaga: n2 nie moze miec wiodacych zer                                      */
inline int *sub(int *b1, int *e1, int *b2, int *e2, int *r) {
    int *r0=r, s=1;
    while (b2!=e2) {
        s += *b1++ + (BASE-1) - *b2++;
        int t = (s>=BASE); *r++ = s-(BASE&-t); s=t;
    }
    if (!s) {
        for (; !*b1; ++b1) *r++ = BASE-1;
        *r++ = *b1++ - 1;    
    }
    return strip(r0, copy(b1, e1, r));
}

/* Porownanie. Uwaga: n1 i n2 nie moga miec wiodacych zer
   Wynik: <0 jesli n1<n2, >0 jesli n1>n2, 0 jesli n1==n2                      */
inline int cmp(int *b1, int *e1, int *b2, int *e2) {
    if (e1-b1!=e2-b2) return (e1-b1)-(e2-b2);
    while (b1!=e1) if (*--e1 != *--e2) return *e1-*e2;
    return 0;
}

// Mnozenie przez mala liczbe O(n). Moze byc r=b1
inline int *mul(int *b1, int *e1, int v, int *r) {
    int *r0=r, s=0;
    while (b1!=e1) {
        long long tmp = s + 1LL*v**b1++;
        *r++ = (int)(tmp%BASE); s = (int)(tmp/BASE);
    }
    if (s) *r++ = s;
    return strip(r0, r);
}

// Mnozenie O(n^2), O(n) dzielen
const long long MAXS = 4000000000000000000LL; /* 4*10^18  Niepotrzebna, jesli
       MAXSIZE*BASE^2 miesci sie w long longu, wtedy mozna usunac t i kod (*) */
inline int *mul(int *b1, int *e1, int *b2, int *e2, int *r) {
    if (b1==e1 || b2==e2) return r;
    long long s=0, t=0; // t,s przechowuje wartosci do MAXSIZE*BASE^2
    for (int j=0; j<(e1-b1)+(e2-b2)-1; ++j) {
        for (int *i1 = min(b1+j, e1-1), *i2 = b2+j-(i1-b1); i1>=b1 && i2<e2;) {
            s += 1LL**i1--**i2++;
            if (s>=MAXS) { s -= MAXS; t += MAXS/BASE; } // <- (*)
        }
        *r++ = (int)(s%BASE); s/=BASE;
        s+=t; t=0; // <- (*)
    }
    while (s) { *r++ = (int)(s%BASE); s/=BASE; }
    return r;
}

// Dzielenie przez mala liczbe. W q umieszczana jest reszta
inline int *div(int *b1, int *e1, int d, int &q, int *r) {
    int *pos = e1; q=0;
    while (--pos >= b1) {
        long long tmp = 1LL*q*BASE + *pos;
        r[pos-b1] = (int)(tmp/d); q = (int)(tmp%d);
    }
    return strip(r, r+(e1-b1));
}

// Dzielenie. Uwaga: w [b1, e1) umieszczana jest reszta
int *div(int *b1, int *&e1, int *b2, int *e2, int *r) {
    static int divbuf[MAXSIZE];
    if (e1-b1<e2-b2) return r;
    int *pos = e1-(e2-b2), *last = r+((e1-b1)-(e2-b2)+1);
    do {
        int q1=0, q2=BASE, *e=divbuf;
        do {
            int q = q1+q2>>1;
            e = mul(b2, e2, q, divbuf);
            if (cmp(divbuf, e, pos, strip(pos, e1)) <= 0) q1=q;
            else q2=q;
        } while (q2-q1>1);
        r[pos-b1] = q1;
        e1 = sub(pos, e1, divbuf, mul(b2, e2, q1, divbuf), pos);
    } while (--pos>=b1);
    return strip(r, last);
}

// FFT, obliczanie splotu i szybkie mnozenie
typedef double K;

const int MAXN = 2*MAXSIZE;	/* potega dwojki, o jeden wyzsza od
                               zaokraglenia nA, nB w gore do najblizszej      */
const K EPS = 1e-8;

int nA, nB; // IN: liczba wspolczynnikow wielomianow A i B 
int nC;     // OUT: liczba wspolczynnikow wielomianu C
int n;      // Uwaga: zmienna pomocnicza

K A[MAXN]; // IN: wielomian A, A[0] - wyraz wolny
K B[MAXN]; // IN: wielomian B, B[0] - wyraz wolny
K C[MAXN]; // OUT: wielomian C, C[0] - wyraz wolny

complex<K> e[MAXN];
complex<K> tab1[MAXN];
complex<K> tab2[MAXN];

// Obliczanie FFT
void FFT(complex<K> tab[]) {
    FOR(i,0,n) {
        int j=0;
        for (int k=1; k<n; k<<=1, j<<=1) if (k&i) j++;
        j>>=1;
        if (i<j) swap(tab[i], tab[j]);
    }
    int step=1, n_step=0;
    while ((1<<n_step)<n) n_step++;
    for (int step=1; step<n; step<<=1) {
        --n_step;
        for (int i=0; i<n; i+=2*step) FOR(j,0,step) {
            complex<K> u=tab[i+j], v=tab[i+j+step];
            tab[i+j] = u+v*e[j<<n_step];
            tab[i+j+step] = u-v*e[j<<n_step];
        }
    }
}

// Obliczanie splotu wielomianow
void convolution() {
    n=1;
    while (n<nA || n<nB) n<<=1;
    n<<=1;
    FOR(i,0,n) {
        tab1[i] = complex<K>(0.0, 0.0);
        tab2[i] = complex<K>(0.0, 0.0);
        e[i] = complex<K>(cos(2*M_PI*i/n), -sin(2*M_PI*i/n));
    }
    FOR(i,0,nA) tab1[i] = complex<K>(A[i], 0.0);
    FOR(i,0,nB) tab2[i] = complex<K>(B[i], 0.0);
    FFT(tab1); FFT(tab2);
    K s = 1.0/n;
    FOR(i,0,n) {
        tab1[i] *= tab2[i]*s;
        e[i] = complex<K>(cos(2*M_PI*i/n), sin(2*M_PI*i/n));
    }
    FFT(tab1);
    FOR(i,0,n) C[i] = real(tab1[i]);
    FORD(i,n,0) if (abs(C[i])>EPS) { nC=i+1; break; }
}

// Mnozenie FFT O(n log(n))
int *fastmul(int *b1, int *e1, int *b2, int *e2, int *r) {
    nA=nB=0;
    for (int *p=b1; p!=e1; ++p) A[nA++] = (K)(*p);
    for (int *p=b2; p!=e2; ++p) B[nB++] = (K)(*p);
    convolution();
    long long s=0;
    FOR(i,0,nC) {
        s += (long long)(C[i]+0.5);
        r[i] = (int)(s%BASE); s/=BASE;
    }
    while (s) { r[nC++] = s%BASE; s/=BASE; }
    return strip(r, r+nC);
}

// Konwersje reprezentacji pozycyjnych O(n^2)
void mul5(char *a) {
    static char b1[1024]; // Uwaga: wpisac maksymalna dlugosc liczby
    char *a1=a, *b=b1;
    int d=0;
    while (*a) { d = d+(*a++-'0')*5; *b++ = d%10+'0'; d/=10; }
    while (d) { *b++ = d%10+'0'; d/=10; }
    *b=0;
    strcpy(a1, b1);
}
void d2b(char *a, char *b) { // dziesietne na binarne (w stringu)
    char *b1=b;
    reverse(a, a+strlen(a));
    while (*a) { mul5(a); *b++ = (*a++=='5')+'0'; }
    *b=0;
    reverse(b1, b);
}
void b2d(char *a, char *b) { // binarne na dziesietne (w stringu)
    *b=0;
    while (*a) {
        char *p=b; int d = *a=='1';
        while (*p) { d += (*p-'0')*2; *p++ = d%10+'0'; d/=10; }
        while (d) { *p++ = d%10+'0'; d/=10; }
        *p=0; ++a;
    }
    reverse(b, b+strlen(b));
}
