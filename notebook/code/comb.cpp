/* ALGORYTMY KOMBINATORYCZNE. Schemat generowania kolejnych obiektow:
   1. Inicjalizacja zmiennych i tablic pierwszym obiektem
   2. Generowanie nastepnych obiektow funkcja next_*, poki zwraca true         */

// Bartosz Walczak

const int MAXN = 100;

typedef int T; // typ, ktory miesci liczbe wszystkich obiektow

/* Generowanie i zliczanie podzbiorow k-elementowych zbioru {0,...,n-1} w
   porzadku leksykograficznym: od {0,...,k-1} do {n-k,...,n-1}                */

int n, k;
int elem[MAXN];  // elementy podzbioru w porzadku rosnacym
bool used[MAXN]; // czy element jest w podzbiorze? (nieuzywana w algorytmach)

bool next_subset() { // nastepny podzbior. Zwraca false, jesli wrocil do
    int cur=1;       // pierwszego. Czas zamortyzowany O(1)
    while (cur<=k && elem[k-cur]==n-cur) used[n-cur++]=false;
    if (cur>k) {
        FOR(i,0,k) { elem[i]=i; used[i]=true; }
        return false;
    }
    int pos=elem[k-cur]; used[pos++]=false;
    FOR(i,0,cur) { elem[k-cur+i]=pos+i; used[pos+i]=true; }
    return true;
}

T newton[MAXN+1][MAXN+1]; // newton[n][k] - symbol Newtona n po k

void init_subset() { // wypelnia tablice newton
    newton[0][0]=1;
    FOR(j,1,n+1) newton[0][j]=0;
    FOR(i,1,n+1) {
        newton[i][0]=newton[i-1][0];
        FOR(j,1,n+1) newton[i][j]=newton[i-1][j-1]+newton[i-1][j];
    }
}
T count_subset() { // zwraca numer podzbioru. Czas O(k)
    T res=0; int first=0;
    FOR(i,0,k) {
        res+=newton[n-first][k-i]-newton[n-elem[i]][k-i];
        first=elem[i]+1;
    }
    return res;
}
void gen_subset(T no) { // generuje podzbior o podanym numerze. Czas O(n)
    fill_n(used, n, false);
    int first=0, pos=0;
    FOR(i,0,k) {
        while (no>=newton[n-first][k-i]-newton[n-pos-1][k-i]) ++pos;
        no-=newton[n-first][k-i]-newton[n-pos][k-i];
        elem[i]=pos; used[pos]=true;
        first=++pos;
    }
}

/* Generowanie i zliczanie podzialow liczby n na sume dodatnich skladnikow w
   porzadku antyleksykograficznym: od n do 1+1+...+1                          */

int n, k;                  // k - liczba roznych skladnikow, k=O(sqrt(n))
int elem[MAXN], cnt[MAXN]; // elem - skladnik, cnt - ile razy?

bool next_partition1() { // nastepny podzial. Zwraca false, jesli wrocil do
    int sum=0;           // pierwszego. Czas O(1)
    if (elem[k-1]==1) sum+=cnt[--k];
    if (!k) { elem[k]=sum; cnt[k++]=1; return false; }
    sum+=elem[k-1];
    if (--cnt[k-1]) { elem[k]=elem[k-1]-1; ++k; }
    else --elem[k-1];
    cnt[k-1]=sum/elem[k-1]; sum%=elem[k-1];
    if (sum) { elem[k]=sum; cnt[k++]=1; }
    return true;
}

T pcnt[MAXN+1][MAXN+1]; // pcnt[n][k] - liczba podzialow liczby n o najwiekszym
                        // skladniku <=k == liczba podzialow na <=k skladnikow
void init_partition1() { // wypelnia tablice pcnt
    FOR(j,0,n+1) pcnt[0][j]=1;
    FOR(i,1,n+1) {
        pcnt[i][0]=0;
        FOR(j,1,i+1) pcnt[i][j]=pcnt[i][j-1]+pcnt[i-j][j];
        FOR(j,i+1,n+1) pcnt[i][j]=pcnt[i][i];
    }
}
T count_partition1() { // zwraca numer podzialu. Czas O(k)
    T res=0; int sum=n, first=n;
    FOR(i,0,k) {
        res+=pcnt[sum][first]-pcnt[sum][elem[i]];
        sum-=elem[i]*cnt[i]; first=elem[i];
    }
    return res;
}
void gen_partition1(T no) { // generuje podzial o podanym numerze. Czas O(n)
    k=0; int sum=n, first=n, cur=n;
    while (sum) {
        while (no>=pcnt[sum][first]-pcnt[sum][cur-1]) --cur;
        no-=pcnt[sum][first]-pcnt[sum][cur];
        elem[k]=cur; cnt[k++]=1;
        sum-=first=cur;
        while (no<pcnt[sum][cur]-pcnt[sum][cur-1]) { ++cnt[k-1]; sum-=cur; }
    }
}

/* Generowanie i zliczanie podzialow zbioru {0,...,n-1} na niepuste podzbiory
   w porzadku leksykograficznym: od {0,...,n-1} do {0},...,{n-1}
   Uwaga: Klasy podzialu sa numerowane w porzadku leksykograficznym elementow.
   W szczegolnosci element 0 zawsze nalezy do klasy 0.                        */

int n, cnt;     // cnt - liczba klas podzialu
int size[MAXN]; // rozmiar klasy podzialu
int pos[MAXN];  // numer klasy elementu. Ta tablica wyznacza porzadek podzialow

bool next_partition2() { // nastepny podzial. Zwraca false, jesli wrocil do
    FORD(i,n,1) {        // pierwszego. Czas zamortyzowany O(1)
        if (pos[i]==cnt-1) {
            if (size[cnt-1]==1) { pos[i]=0; ++size[0]; --cnt; continue; }
            size[cnt++]=0;
        }
        --size[pos[i]]; ++pos[i]; ++size[pos[i]];
        return true;
    }
    return false;
}

T pcnt[MAXN+1][MAXN+1]; // pcnt[n][0] - liczba podzialow zbioru n-elementowego

void init_partition2() { // wypelnia tablice pcnt
    FOR(j,0,n+1) pcnt[0][j]=1;
    FOR(i,1,n+1) FOR(j,0,n+1) pcnt[i][j]=j*pcnt[i-1][j]+pcnt[i-1][j+1];
}
T count_partition2() { // zwraca numer podzialu. Czas O(n)
    T res=0; int wd=0;
    FOR(i,0,n) {
        res+=pos[i]*pcnt[n-i-1][wd];
        if (pos[i]==wd) ++wd;
    }
    return res;
}
void gen_partition2(T no) { // generuje podzial o podanym numerze. Czas O(n)
    cnt=0;
    FOR(i,0,n) {
        int p=min(cnt, no/pcnt[n-i-1][cnt]);
        no-=p*pcnt[n-i-1][cnt];
        if (p==cnt) size[cnt++]=0;
        pos[i]=p; ++size[p];
    }
}

// Arkadiusz Pawlik

/* Kod Gray'a: gray(0),...,gray(2^n-1) - permutacja liczb 0,...,2^n-1, w ktorej
   kazde dwie kolejne oraz ostatnia z pierwsza roznia sie tylko na 1 bicie    */
unsigned gray(unsigned n) { return n^n>>1; }
unsigned igray(unsigned n) { // funkcja odwrotna do gray
    n^=n>>1; n^=n>>2; n^=n>>4; n^=n>>8; n^=n>>16;
    return n;
}

// Odwrocenie kolejnosci bitow (operuje na n najmniej znaczacych bitach)
unsigned rev(unsigned v, unsigned n) {
    v = (v & 0xffff0000)>>16 | (v & 0x0000ffff)<<16;
    v = (v & 0xff00ff00)>>8  | (v & 0x00ff00ff)<<8;
    v = (v & 0xf0f0f0f0)>>4  | (v & 0x0f0f0f0f)<<4;
    v = (v & 0xcccccccc)>>2  | (v & 0x33333333)<<2;
    v = (v & 0xaaaaaaaa)>>1  | (v & 0x55555555)<<1;
    return v >> 32-n;
}

// Liczba niezerowych bitow
unsigned bitcount(unsigned v) {
    v = ((v & 0xaaaaaaaa)>>1)  + (v & 0x55555555);
    v = ((v & 0xcccccccc)>>2)  + (v & 0x33333333);
    v = ((v & 0xf0f0f0f0)>>4)  + (v & 0x0f0f0f0f);
    v = ((v & 0xff00ff00)>>8)  + (v & 0x00ff00ff);
    v = ((v & 0xffff0000)>>16) + (v & 0x0000ffff);
    return v;
}
