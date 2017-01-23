/*
Days of week
January 1, 1600: Saturday   January 1, 1900: Monday     June 13, 2042: Friday
January 1, 2008: Tuesday    April 1, 2008: Tuesday      April 9, 2008: Wednesday
December 31, 1999: Friday   January 1, 3000: Wednesday
*/
/* Warnsdorff's heuristic for knight's tour. At each step choose a square which
   has the least number of valid moves that the knight can make from there. */

// Fenwick Tree
int a[MAXN];
// value[n] += x
void add(int n, int x) { for (; n < MAXN; n |= n + 1) a[n] += x; }
// Returns value[0] + value[1] + ... + value[n]
int sum(int n) { int s=0; while (n>=0) { s+=a[n]; n=(n&(n+1))-1; } return s; }

/*
Clearing the lowest 1 bit: x & (x - 1), all trailing 1's: x & (x + 1)
Setting the lowest 0 bit: x | (x + 1)
Enumerating subsets of a bitmask m: x=0; do { ...; x=(x+1+~m)&m; } while (x!=0);
__builtin_ctz/__builtin_clz returns the number of trailing/leading zero bits.
__builtin_popcount(unsigned x) counts 1-bits (slower than table lookups).
For 64-bit unsigned integer type, use the sumx `ll', i.e. __builtin_popcountll.
*/
/*
Flow-shop scheduling (Johnson's problem). Schedule N jobs on 2 machines to
minimize completition time. i-th job takes a_i and b_i time to execute on 1st
and 2nd machine, respectively. Each job must be first executed on the fitrst
machine, then on second. Both machines execute all jobs in the same order.
Solution: sort jobs by key a_i < b_i ? a_i : (INF-b_i)
*/
/*
Euler's theorem. For any planar graph, V - E + F = 1 + C, where V is the number
of graph's vertices, E is the number of edges, F is the number of faces in
graph's planar drawing, and C is the number of connected components.
Corollary: V - E + F = 2 for a 3D polyhedron.
*/
/*
Matrix-tree theorem. Let matrix T = [t_ij], where t_ij is the number of
multiedges between i and j, for i != j, and t_ii = -deg_i.
Number of spanning trees of a graph is equal to the determinant of a matrix
obtained by deleting any k-th row and k-th column from T.
*/
/*
Vertex covers and independent sets.
Let M, C, I be a max matching, a min vertex cover, and a max independent set.
Then |M| <= |C| = N - |I|, with equality for bipartite graphs. Complement
of an MVC is always a MIS, and vice versa. Given a bipartite graph with
partitions (A;B), build a network: connect source to A, and B to sink with
edges of capacities, equal to the corresponding nodes' weights, or 1 in the
unweighted case. Set capacities of the original graph's edges to the
infinity. Let (S; T) be a minimum s-t cut. Then a maximum(-weighted) independent
set is I = (A * S) + (B * T), and a minimum(-weighted) vertex cover is
C = (A * T) + (B * S).
*/

// Jesli G nie ma w. izolowanych: max skojarzenie + min pokrycie krawedziowe = |V|

// W dwudzielnym |min pokrycie wierzcholkowe| = |max skojarzenie|

/*
Pick's theorem. I = A - B/2 + 1, where A is the area of a lattice polygon,
I is number of lattice points inside it, and B is number of lattice points
on the boundary. Number of lattice points minus one on a line segment
from (0; 0) and (x; y) is gcd(x; y).
*/
/*
Kryterium Eulera (kiedy a jest reszta stopnia b modulo n?): jesli gcd(a,n)=1,
to (istnieje x: x^b=a(mod n)) <=> a^(phi(n)/gcd(phi(n),b))=1(mod n)

Duze liczby pierwsze:
    27281,    27397,        32237,    32251
    40507,    40591,        60331,    60353
    130079,   130367,       438443,   438499
    2023369,  2023453,      6384211,  6384709
    11796569, 11796767,     28892183, 28892267
    66926647, 66927067                              */

/*
#!/bin/bash
# Valgrind usage:
g++ -g a.cpp -o a
valgrind --tool=cachegrind ./a < t0.in
# You should now have a file named cachegrind.out.PID where PID is a number.
cg_annotate --auto=yes cachegrind.out.PID | less */

// Maksymalny leksykograficznie sufiks (algorytm Duvala)
// Bartosz Walczak
int duval(const char *s, int n) {
    int pb=0, pl=1, rb=1, rl=0;
    while (rb+rl<n) {
        if (s[rb+rl]>s[pb+rl]) { pb=rb++; pl=1; rl=0; }
        else if (s[rb+rl]<s[pb+rl]) { rb+=rl+1; pl=rb-pb; rl=0; }
        else if (++rl==pl) { rb+=pl; rl=0; }
    }
    return pb;
}
