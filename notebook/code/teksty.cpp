// ALGORYTMY TEKSTOWE
// Adam Polak

// Funkcja prefikso-sufiksowa
void pref_suf(const char *w, int n, int *p) {
    p[0] = 0;
    for(int i=1;i<n;i++) {
        p[i] = p[i-1];
        while(p[i] > 0 && w[i] != w[p[i]]) p[i] = p[p[i]-1];
        if (w[i] == w[p[i]]) p[i]++;
    }
}

// Funkcja prefikso-prefiksowa
void pref_pref(const char *w, int n, int *p) {
    int g = 0;
    p[0] = 0;
    for(int i=1;i<n;i++) {
        p[i] = max(min(p[i-g], p[g]+g-i), 0);
        while(i+p[i] < n && w[p[i]] == w[i+p[i]]) p[i]++;
        if (p[i]+i > p[g]+g) g=i;
    }
}

// Promienie palindromiczne (algorytm Manachera)
// sh = 0 dla palindromow nieparzystych, 1 dla parzystych
int manacher(const char *w, int n, int *p, int sh) {
    int g = 0;
    p[0] = 1-sh;
    for(int i=1;i<n;i++) {
        if (2*g-i>=0) p[i] = max(min(p[2*g-i], p[g]+g-i),0);
        else p[i] = 0;
        while(i-p[i]-sh >= 0 && i+p[i] < n && w[i+p[i]] == w[i-p[i]-sh]) 
            p[i]++;
        if (p[i]+i > p[g]+g) g=i;
    }
}

// Slownik podslow bazowych (KMR)
int dbf[16][1<<16]; // OUTPUT
void kmr(const char *w, int n) {
    REP(i,n) dbf[0][i] = w[i];
    pair<pair<int,int>,int> h[n];
    int k, l;
    for(l=k=1; l<n; l<<=1, k++) {
        REP(i,n) h[i]=make_pair(
                make_pair(dbf[k-1][i], (i+l<n)?dbf[k-1][i+l]:0),i);
        sort(h,h+n);
        int count = 1;
        REP(i,n) {
            if (i>0 && h[i].first!=h[i-1].first) count++;
            dbf[k][h[i].second] = count;
        }
    }
}

// Rownowaznosc cykliczna
#define cyc(x) (x)<n?(x):(x-n)
bool cyc_equiv(char *w, char *u, int n) {
    int i=0,j=0,k;
    while(i<n && j<n) {
        for(k=0;k<n;k++) if (w[cyc(i+k)]!=u[cyc(j+k)]) break;
        if (k==n) return true;
        if (w[cyc(i+k)] < u[cyc(j+k)]) i+=k+1; else j+=k+1;
    }
    return false;
}
