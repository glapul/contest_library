// TEST RABINA MILLERA
// + MNOZENIE MODULO 64bit LICZB
// Maciek Wawro

typedef unsigned long long ULL;
const int _k = 16;
const ULL _mask = (1<<_k)-1;
//   Zalozenia: b, MOD < 2^(64-_k) 
ULL mul(ULL a, ULL b, ULL MOD){
    ULL result = 0;
    while(a){
        ULL temp = (b*(a&_mask)) % MOD;
        result = (result+temp) % MOD;
        a >>= _k;
        b = (b<<_k) % MOD;
    }
    return result;
}

/* inline ULL mul(ULL a, ULL b, ULL MOD) { return (a*b) % MOD; } */

ULL pow(ULL a, ULL w, ULL MOD) {
    ULL res = 1;
    while(w){
        if (w&1) res = mul(res, a, MOD);
        a = mul(a, a, MOD);
        w >>= 1; 
    }
    return res;
}

bool primeTest(ULL N, int a) {
    if(a > N-1) return true;
    ULL d = N-1;
    int s = 0;
    while(!(d&1)){
        d >>= 1;
        s++;
    }
    ULL x = pow(a, d, N);
    if((x==1)||(x==N-1)) return true;
    REP(i,s-1){
        x = mul(x, x, N);
        if(x == 1) return false;
        if(x == N-1) return true;    
    }
    return false;
}

/*  Dla N<2^32 testujemy 2, 7, 61
 *  Dla N<2^48 testujemy pierwsze z [2,17] 
 *  Dla N<2^64 testujemy 2, 325, 9375, 28178, 
        450775, 9780504, 1795265022             */
        
bool isPrime(ULL N) {
    if(N<4) return N>1;  
    bool prime = N%2;
    prime = prime && primeTest(N, 2);
    prime = prime && primeTest(N, 7);  
    prime = prime && primeTest(N, 61);  
    return prime;
}

/*  Test mozna przyspieszyc, sprawdzajac najpierw podzielnosc przez
 *  pierwsze kilkanascie liczb pierwszych. */
