#include "header.h"

namespace kody { //wat?
#include "euler.cpp"

}

PII minmax(int a, int b){
    return PII(min(a,b), max(a,b));
}

main(){
	srand(time(0));
    int n,m;
    scanf("%d %d", &n, &m);
    fprintf(stderr, "#vertices: %d, #edges: %d\n", n,m);
    assert(n < kody::MAXN);
    assert(m < kody::MAXM);
    kody::n = n;

#ifdef CHECK
    map<PII,int> edges_left;
#endif

    int sum = 0;
    REP(i,m){
        int a,b;
        scanf("%d %d", &a,&b);
        a--; b--;
        sum += a; sum += b;
        kody::add_edge(a,b);
#ifdef CHECK
        edges_left[minmax(a,b)]++;
#endif
    }
    printf("%d\n", sum);
    kody::compute_cycle();
    assert(kody::cc == m);
    for(int i=0; i<m; i++) {
        int a = kody::cycle[i]->v;
        int b = kody::cycle[(i+1)%m]->v;
        printf("%d ", a);
#ifdef CHECK
        edges_left[minmax(a,b)]--;
#endif
    }
    printf("\n");
    assert(kody::cc == m);

#ifdef CHECK
    FOREACH(p, edges_left){
        assert(p->second == 0);
    }
#endif
}
