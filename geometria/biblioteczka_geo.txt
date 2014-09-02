Biblioteczka geometryczna Jakuba Onufrego Wojtaszczyka

// V 1.04, 8.VI
// ** Zasady korzystania **
//    - nie wykorzystujemy na konkursach, gdzie kod musi byc autorski (np. TopCoder)
//    - nie linkujemy bez mojej (Onufrego) wiedzy
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <cassert>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <vector>
#include <cmath>
using namespace std;
typedef long long LL;
typedef long double ld;
typedef pair<int,int> PII;
typedef vector<int> VI;
#define MP make_pair
#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) (int)x.size()
#define ALL(c) c.begin(),c.end()

#define PI (2 * asinl(1))
#define EPS 0.00000001

#define X s[0]
#define Y s[1]
#define DIM 2
#define SQR(x) ((x)*(x))

typedef long double ld;
inline ld gd(ld &x) {scanf("%Lf",&x); return x;}
inline void pd(ld x) {printf("%Lf",x);}

inline int iszero(ld x) {
  return (x < EPS) && (x > -EPS);
}

typedef struct {
  ld s[DIM];
} pt; // Point - punkt


typedef struct {
  pt O;
  pt dir;
} lin; // Line - prosta

typedef struct {
  pt A;
  pt B;
} seg; // Segment - odcinek

typedef struct {
  pt O;
  ld R;
} circ; // Circle - okrag

inline pt operator+ (const pt &A, const pt &B) {
  pt res;
  res.X = A.X + B.X;
  res.Y = A.Y + B.Y;
  return res;
}

inline pt operator- (const pt &A, const pt &B) {
  pt res;
  res.X = A.X - B.X;
  res.Y = A.Y - B.Y;
  return res;
}

inline pt operator* (const ld &lam, const pt &A) {
  pt res;
  res.X = lam * A.X;
  res.Y = lam * A.Y;
  return res;
}

inline bool operator== (const pt &A, const pt &B) {
  REP (i, DIM) if (!iszero(A.s[i] - B.s[i])) return 0;
  return 1; 
}

inline void ppt (const pt &A) {pd(A.X);printf(" ");pd(A.Y);printf(" ");}
inline void pptn (const pt &A) {ppt(A); printf("\n");}
inline void plin (const lin &A) {printf("["); ppt(A.O); printf(", "); ppt(A.O + A.dir); printf("] ");}
inline void plinn (const lin &A) {plin(A); printf("\n");}
inline void pcirc (const circ &C) {printf("[("); ppt(C.O); printf(") "); printf("%Lf] ", C.R);}
inline void pcircn (const circ &C) {pcirc(C); printf("\n");}

inline pt mpt (ld x, ld y) {
  pt res;
  res.X = x;
  res.Y = y;
  return res;
}

inline lin mlin (const pt &A, const pt &B) {
  lin res;
  res.O = A;
  res.dir = B - A;
  return res;
}

inline seg mseg (const pt &A, const pt &B) {
  seg res;
  res.A = A;
  res.B = B;
  return res;
}

inline circ mcirc (const pt &A, ld R) {
  circ res;
  res.O = A;
  res.R = R;
  return res;
}

inline ld cp (const pt &A, const pt &B) { // 2D
  return A.X * B.Y - A.Y * B.X;
}

// 1 - punkt na prawo od prostej, losowo kiedy punkt na prostej
inline int na_prawo (const pt &A, const lin &L) {
  if (cp(A-L.O, L.dir) > 0.) return 1; return 0;
}

inline ld is (const pt &A, const pt &B) {
  return A.X * B.X + A.Y * B.Y;
}

/* Przeciecie dwoch prostych - algorytm Malcina 
   Skala to stosunek pola trojkata do pola czworokata 
   Dla pokrywajacych sie prostych zwraca "nie" */

int intersect_lin_lin (const lin &K, const lin &L, pt &res) { // 2D
  if (abs(cp(K.dir, L.dir)) < EPS) return 0; 
  ld s = cp(K.dir, K.O - L.O) / cp (K.dir, L.dir);
  res = L.O + s * L.dir;
  return 1;
}

/*
int main() {
  pt res;
  lin K = mlin(mpt(1,3), mpt(2,5));
  lin L = mlin(mpt(5,4), mpt(1,10));
  printf("%d ", intersect_lin_lin(K,L,res));
  pptn(res);
  return 0;
}
*/

// Sprawdza nierownosc trojkata dla trzech liczb
// -1: nie zachodzi, 0: zachodzi rownosc (punkty wspolliniowe), 1: zachodzi ostra.
int triangle (ld x, ld y, ld z) {
  if (x < y) {ld t; t=x; x=y; y=t;}
  if (z < x) {ld t; t=x; x=z; z=t;}
  if (iszero(z-x-y)) return 0;
  if (z-x-y < 0) return 1;
  return -1;
}

/* Obrot wzgledem (0,0) przeciwny do wskazowek zegara */
pt rotate_origin (ld theta, const pt &A) { 
  pt res;
  ld si = sinl(theta);
  ld co = cosl(theta);
  res.X = A.X * co - A.Y * si;
  res.Y = A.X * si + A.Y * co;
  return res;
}

/* Dowolny obrot */
pt rotate (ld theta, const pt &A, const pt &O) { 
  return O + rotate_origin(theta, A-O);
}

/* Obrot o 90 wzgledem srodka, przeciwnie do wskazowek */
inline pt rotate_90_origin (const pt &A) {
  return mpt(-A.Y, A.X);
}

/* Obrot o 90 stopni, dla wydajnosci i dokladnosci, przeciwnie do wskazowek */
pt rotate_90 (const pt &A, const pt &O) {
  return rotate_90_origin(A-O) + O;
}

/* int main() {
  pt O = mpt(2,3);
  pt A = mpt(2,6);
  A = rotate(PI / 6.0, A, O);
  pptn(A);
  return 0;
} */

// Kat <AOB skierowany przeciwnie do wskazowek, w [0,2PI]
ld angle (const pt &A, const pt &O, const pt &B) {
  ld res = atan2l((B-O).Y, (B-O).X) - atan2l((A-O).Y, (A-O).X);
  if (res < 0) res += 2.*PI;
  return res;
}

// Kat skierowany miedzy prostymi skierowanymi
ld angle (const lin &K, const lin &L) {
  return angle(K.dir, mpt(0,0), L.dir);
}


// Rzut punktu na prosta
pt rzut (const pt &A, const lin &L) {
  return (is(A - L.O,L.dir) / is(L.dir,L.dir)) * L.dir + L.O;
}

/*
int main () {
  pt A = mpt(2.5,1.5);
  lin L = mlin(mpt(0,0), mpt(2,8));
  pptn(rzut(A,L));
  return 0;
}
*/

// Rownoleglosc wektorow
int parallel (const pt &A, const pt &B) {
  return iszero(cp(A,B));
}

// Rownoleglosc prostych
int parallel (const lin &K, const lin &L) {
  return parallel(K.dir, L.dir);
}

// Prosta prostopadla do wektora przez dany punkt 
lin perp (const pt &A, const pt &D) {
  return mlin(A, A + mpt(D.Y, -D.X));
}

// Lezy pomiedzy, i na tej samej prostej.
int between (const pt &A, const pt &M, const pt &B) {
  if (!parallel(M-A,B-A)) return 0;
  return (is(M-A,M-B) < EPS);
}

// Przeciecie punktu z odcinkiem
// Zwraca "nie" dla odcinka pokrywajacego sie z prosta, w tym jednopunktowego
int intersect_lin_seg (const lin &L, const seg &I, pt &W) {
  if (!intersect_lin_lin(L, mlin(I.A,I.B),W)) return 0;
  if (between(I.A,W,I.B)) return 1; return 0;
}

/*
int main() {
  lin L = mlin(mpt(1,2), mpt(2,3));
  seg I[4];
  I[0] = mseg(mpt(2,0), mpt(0,2));
  I[1] = mseg(mpt(0,0), mpt(3,0));
  I[2] = mseg(mpt(0,5), mpt(9,5));
  I[3] = mseg(mpt(3,4), mpt(7,7));
  pt W;
  REP (i, 4) {
    int r;
    printf("%d ", r = intersect_lin_seg(L, I[i], W));
    if (r) pptn(W); else printf("\n");
  }
  return 0;
}
*/

// Przeciecie dwoch odcinkow
// Zastrzezenia jak przy lin_seg
int intersect_seg_seg (const seg &I, const seg &J, pt &W) {
  if (!intersect_lin_lin(mlin(I.A,I.B), mlin(J.A,J.B), W)) return 0;
  if (between(I.A,W,I.B) && between(J.A,W,J.B)) return 1; return 0;
}

// Punkt na prostej
int online (const lin &L, const pt &A) {
  return (is(A-L.O,A-L.O) < EPS) || parallel(L.dir, A-L.O);
}

ld lgt (pt A) {
  return sqrt(is(A,A));
}

ld dist (pt A, pt B) {
  return lgt(A-B);
}

/* Funkcje na kolach */

inline int on_circ(const pt &A, const circ &C) {
  return (iszero(dist(A,C.O) - C.R));
}

// zapewnia is(K.dir, W1-W2) >= 0) jeÅ?li zwraca dwa punkty
int intersect_lin_circ (const lin &K, const circ &C, pt &W1, pt &W2) {
  pt M = rzut(C.O, K);
	if (on_circ(M, C)) {W1 = M; return 1;}
  ld dao = dist(M,C.O);
  if (dao > C.R) return 0;
  if (dao < EPS) {
    W1 = C.O + (C.R / lgt(K.dir)) * K.dir;
    W2 = C.O - (C.R / lgt(K.dir)) * K.dir;
    return 2;
  }
  ld theta = acosl(dao / C.R);
  M = (C.R / dao) * (M - C.O) + C.O;
  W1 = rotate(theta,M,C.O);
  W2 = rotate(-theta,M,C.O);
	if (is(K.dir, W2-W1) < -EPS) {M = W1; W1 = W2; W2 = M;}
  return 2;
}

/*
int main() {
  circ O = mcirc(mpt(2,1), 5);
  lin L = mlin(mpt(0,4), mpt(1,4));
  pt R1, R2;
  printf("%d: ", intersect_lin_circ(L, O, R1, R2));
  ppt(R1);
  pptn(R2);
  return 0;
}
*/

// Styczne do okregu przez dany punkt
// W1 i W2 to punkty stycznosci, kat W1 O W2 jest skierowany przeciwnie do wskazowek zegara.
int tangent_point (const pt &A, const circ &C, lin &W1, lin &W2) { 
  if (on_circ(A,C)) { // Styczna przez punkt na okregu jest styczna w tym punkcie
    W1 = perp(A, C.O - A);
    return 1;
  }
  ld dao = dist(A,C.O);
  if (dao <= C.R) return 0;
  ld theta = asinl(C.R / dao);
  pt temp = (sqrt(SQR(dao) - SQR(C.R)) / dao) * (C.O - A) + A;
  W2 = mlin(A, rotate(theta, temp, A));
  W1 = mlin(A, rotate(-theta, temp, A));
  return 2;
}

/*
int main() {
  circ C = mcirc(mpt(0,0),20);
  pt P = mpt(0,25);
  lin R1, R2;
  int r = tangent_point(P,C,R1,R2);
  printf("%d", r);
  if (r) plin(R1);
  if (r>1) plin(R2);
  printf("\n");
  return 0;
}
*/

// Przeciecie dwoch okregow
// Supportuje okregi styczne, zwraca liczbe punktow w wyniku
// Luk W2 C1.O W1 (przeciw wskazowkom zegara) jest zawarty w kole C2.
// Zwraca -1, kiedy koÅ?a siÄ? pokrywajÄ?.
int intersect_circ_circ (const circ &C1, const circ &C2, pt &W1, pt &W2) {
  ld doo = dist(C1.O, C2.O);
  if (triangle(doo, C1.R, C2.R) == -1) return 0;
	if (doo < EPS) return -1;
  if (triangle(doo, C1.R, C2.R) == 0 ) { // P.p. okr. stycznych na prostej laczacej srodki
    intersect_lin_circ(mlin(C1.O, C2.O), C1, W1, W2);
    if (on_circ(W2,C2)) W1 = W2;
    return 1;
  }
	// Teraz tw. cosinusow dla trojkata C1.O, C2.O i punktu przeciecia
  ld alpha = acos((SQR(C1.R) - SQR(C2.R) + SQR(doo)) / (2.0 * C1.R * doo)); 
  pt start = C1.O + (C1.R / doo) * (C2.O - C1.O);
  W1 = rotate(alpha, start, C1.O);
  W2 = rotate(-alpha, start, C1.O);
  return 2;
}

/*
int main() {
  circ B = mcirc(mpt(0,0),5);
  circ A = mcirc(mpt(0,4),3);
  pt R1, R2;
  intersect_circ_circ(A,B,R1,R2);
  ppt(R1); pptn(R2);
}
*/

// Pole odcinka kola na lewo od zadanej prostej
// Nieskierowane!
ld circ_segment_area(const circ &C, const lin &L) {
	pt A, B;
	if (intersect_lin_circ(L,C,A,B) < 2) {
		if (na_prawo(C.O, L)) return 0.; 
		return PI * C.R * C.R;
	}
	return (angle(A, C.O, B) * SQR(C.R) - cp(A-C.O,B-C.O)) / 2.;
}

// Pole przeciecia dwoch kol
// Nieskierowane!
ld circ_circ_area(const circ &C1, const circ &C2) {
	ld dao = dist(C1.O, C2.O);
	if (C1.R + C2.R < dao + EPS) return 0.;
	if (C1.R + dao < C2.R + EPS) return PI * SQR(C1.R);
	if (C2.R + dao < C1.R + EPS) return PI * SQR(C2.R);
	pt A, B;
	assert(intersect_circ_circ(C1,C2,A,B) == 2);
	return circ_segment_area(C1, mlin(B,A)) + circ_segment_area(C2, mlin(A,B));
}

// Okrag z trzech punktow
int three_points (const pt &A, const pt &B, const pt &C, circ &R) {
  if (!intersect_lin_lin(perp(0.5 * (A+B), B-A), perp(0.5 * (A+C), C-A), R.O)) 
    return 0;
  R.R = dist(R.O, A);
  return 1;
}

// Styczna wewnetrzna do dwoch okregow
// Zwraca proste styczne
// Wywala sie jak oba okregi sa zdegenerowane
int internal_tangent(const circ &C1, const circ &C2, lin &W1, lin &W2) {
  pt mid = (C1.R / (C1.R + C2.R)) * C2.O + (C2.R / (C1.R + C2.R)) * C1.O;
  return tangent_point(mid, C1, W1, W2);
}

// Styczne zewnetrzne do okregow
// Zwraca proste styczne
// Zwraca zero, gdy okregi sie nakladaja
int external_tangent(const circ &C1, const circ &C2, lin &W1, lin &W2) {
  if (iszero(C1.R - C2.R)) {
    if (iszero(dist(C1.O,C2.O))) return 0;
    pt start = C1.O + ((C1.R / dist(C1.O,C2.O)) * rotate_90_origin(C2.O - C1.O));
    W1 = mlin(start, start + C2.O - C1.O);
    W2 = mlin(C1.O + C1.O - start, C1.O + C2.O - start);
    return 2;
  }
  pt start = (C2.R / (C2.R - C1.R)) * C1.O - (C1.R / (C2.R - C1.R)) * C2.O;
  return tangent_point(start, C1, W1, W2);
}

/*
int main() {
  circ C1 = mcirc(mpt(10,10),10);
  circ C2 = mcirc(mpt(1,1),1);
  lin W1, W2;
  printf("%d ", internal_tangent(C1, C2, W1, W2));
  plin(W1); plinn(W2);
  printf("%d ", external_tangent(C1, C2, W1, W2));
  plin(W1); plinn(W2);
  return 0;
}
*/

/* Inwersja */
// Zakladam, ze wszystkie inwersje sa o promieniu 1

// Inwersja wzgledem (0,0) // kwadrat dlugosci pisze explicite dla wydajnosci
pt invert_origin (const pt &A) {
  return (1. / (SQR(A.X) + SQR(A.Y))) * A;
}

pt invert (const pt &A, const pt &O) {
  return invert_origin(A-O) + O;
}

// Unia prostej i okregu - na uzytek inwersji duzo prosciej jest utozsamiac
// proste i okregi
typedef struct {
  int typ; // 0 - prosta, 1 - okrag
  union {
    lin L;
    circ C;
  } V;
} lincirc;

lincirc mlincirc (const lin &L) {
  lincirc res;
  res.typ = 0;
  res.V.L = L;
  return res;
}

lincirc mlincirc (const circ &C) {
  lincirc res;
  res.typ = 1;
  res.V.C = C;
  return res;
}

void plc (const lincirc &LC) {
  if (LC.typ == 0) plin(LC.V.L);
  else pcirc(LC.V.C);
}

void plcn (const lincirc &LC) {
  plc(LC);
  printf("\n");
}

lincirc invert (const lin &L, const pt &O) {
  lincirc res;
  if (online(L,O)) {
    res.typ = 0;
    res.V.L = L;
    return res;
  }
  res.typ = 1;
  three_points(invert(L.O,O), invert(L.O + L.dir,O), O, res.V.C);
  return res;
}

lincirc invert (const circ &C, const pt &O) {
  lincirc res;
  if (iszero(dist(O, C.O) - C.R)) {
    res.typ = 0;
    pt A = rotate_90(O, C.O);
    pt B = rotate_90(A, C.O);
    res.V.L = mlin(invert(A,O),invert(B,O));
    return res;
  }
  res.typ = 1;
  pt A = C.O; A.X += C.R; // Losowy punkt na okregu
  pt B = rotate_90(A,C.O);
  pt D = rotate_90(B,C.O);
  three_points(invert(A,O), invert(B,O), invert(D,O), res.V.C);
  return res;
}

lincirc invert (const lincirc &LC, const pt &O) {
  if (LC.typ == 0) return invert(LC.V.L, O);
  return invert(LC.V.C, O);
}

/*
int main() {
  pt O = mpt(1,1);
  circ C = mcirc(mpt(0,0), 2);
  lincirc R;
  R.typ = 1;
  R.V.C = C;
  plcn(invert(R,O));
  plcn(invert(invert(R,O),O));
  
  R.typ = 0;
  R.V.L = mlin(mpt(3,4), mpt(4,5));
  plcn(invert(R,O));
  plcn(invert(invert(R,O),O));
  return 0;
}
*/

///////////// TODO OD TUTAJ

// Liczy okregi/proste styczne do danego okregu/prostej przez dane dwa punkty
// Zwraca vector wynikow

// Zwraca styczna do lincirca przez punkt
vector<lin> tangent_lincirc (const lincirc &LC, const pt &P) {
  vector<lin> res;
  if (LC.typ == 0) { // Prosta rownolegla do danej przez dany punkt
    res.PB(mlin(P,P + LC.V.L.dir));
    return res;
  }
  res.resize(2);
  int nres = tangent_point(P, LC.V.C, res[0], res[1]);
  res.resize(nres);
  return res;
}

// Liczy styczne do danego kola/okregu przez dane dwa punkty. Tego jest dwa,
// jeden lub zero.
vector<lincirc> lincirc_point_point (const lincirc &LC, const pt &P1, const pt &P2) {
  pt IP = invert(P2, P1);
  lincirc IC = invert(LC, P1);
  vector<lin> tangs = tangent_lincirc(IC, IP);
  vector<lincirc> res;
  REP (i, SIZE(tangs)) res.PB(invert(tangs[i], P1));
  return res;
}

/*
int main() {
  pt P1, P2;
  lincirc LC;
  circ C;
  lin L;
  P1 = mpt(0,0);
  P2 = mpt(2,2);
  C = mcirc(mpt(1,4),1);
  LC.typ = 1;
  LC.V.C = C;
  vector<lincirc> res = lincirc_point_point(LC,P1,P2);
  REP (i, SIZE(res)) plcn(res[i]);
  return 0;
}
*/

// Styczne do dwoch okregow/prostych przez dany punkt
// Funkcja ma problem, jesli zarowno LC1 jak i LC2 przechodza przez P - wtedy
// rozwiazania sa zle okreslone. Funkcja w kazdym takim przypadku zwraca jedno
// rozwiazanie - okrag o srodku w P i promieniu zero
vector<lincirc> lincirc_lincirc_point (const lincirc &LC1, const lincirc &LC2, const pt &P) {
  vector<lincirc> res;
  lincirc ILC1, ILC2;
  lin W1, W2;
  int nw;

  ILC1 = invert(LC1, P);
  if (ILC1.typ == 0) {
    ILC2 = ILC1;
    ILC1 = invert(LC2, P);
  } else ILC2 = invert(LC2, P); // Zapewniam, ze ILC1 jest okregiem
  if (ILC1.typ == 0) {res.PB(mlincirc(mcirc(P,0))); return res;}
  if (ILC2.typ == 0) {
    pt MV = (ILC1.V.C.R / lgt(ILC2.V.L.dir)) * rotate_90_origin(ILC2.V.L.dir);
    res.PB(invert(mlin(ILC1.V.C.O + MV, ILC1.V.C.O + MV + ILC2.V.L.dir),P));
    res.PB(invert(mlin(ILC1.V.C.O - MV, ILC1.V.C.O - MV + ILC2.V.L.dir),P));
    return res;
  }
  nw = internal_tangent(ILC1.V.C, ILC2.V.C, W1, W2);
  if (nw) res.PB(invert(W1, P));
  if (nw > 1) res.PB(invert(W2, P));
  nw = external_tangent(ILC1.V.C, ILC2.V.C, W1, W2);
  if (nw) res.PB(invert(W1, P));
  if (nw > 1) res.PB(invert(W2, P));
  return res;
}

/*
int main() {
  pt P1;
  circ C1, C2;
  P1 = mpt(0,0);
  C1 = mcirc(mpt(2,0),1);
  C2 = mcirc(mpt(0,2),1);
  vector<lincirc> res = lincirc_lincirc_point(mlincirc(C1), mlincirc(C2), P1);
  REP (i, SIZE(res)) plcn(res[i]);
  return 0;
}
*/

vector<pt> make_candidates(circ C[3], int P[3]) {
  vector<pt> res;
  if (iszero(C[2].R)) {
    circ T;
    if (three_points(C[0].O, C[1].O, C[2].O, T)) res.PB(T.O);
    return res;
  }
  vector<lincirc> LCs;
  if (iszero(C[1].R)) LCs = lincirc_point_point(mlincirc(C[2]), C[1].O, C[0].O);
  else LCs = lincirc_lincirc_point(mlincirc(C[2]), mlincirc(C[1]), C[0].O);
  REP (i, SIZE(LCs)) if (LCs[i].typ == 1) res.PB(LCs[i].V.C.O);
  return res;
}

int check_pt_circles (circ C[3], int P[3], const pt &CP, circ &CR) {
  ld Rs[3];
  REP (i, 3) if(P[i]) Rs[i] = C[i].R - dist(C[i].O, CP);
             else     Rs[i] = dist(C[i].O, CP) - C[i].R;
  REP (i, 2) if (!iszero(Rs[i] - Rs[2])) return 0;
  if (Rs[2] < -EPS) return 0;
  CR.O = CP;
  CR.R = Rs[0];
  return 1;
}

// Zmienne P1,P2,P3 okreslaja pozadany typ stycznosci - 0 to zewnetrzna, a 1 to wewnetrzna
vector<circ> three_circles (const circ &C1, const int &P1, const circ &C2, const int &P2, const circ &C3, const int &P3) {
  if (C1.R > C2.R) return three_circles(C2,P2,C1,P1,C3,P3);
  if (C1.R > C3.R) return three_circles(C3,P3,C1,P1,C2,P2); // C1 ma min promien
  if (C2.R > C3.R) return three_circles(C1,P1,C3,P3,C2,P2); // C2 -- drugi mozliwy
  circ C[3];
  int P[3];
  C[0] = C1; C[1] = C2; C[2] = C3; P[0] = P1; P[1] = P2; P[2] = P3;
  ld mr = P[0] ? -C[0].R : C[0].R;
  REP (i, 3) C[i].R += (P[i] ? mr : -mr);
  vector<pt> candidates = make_candidates(C,P);
  REP (i, 3) C[i].R -= (P[i] ? mr : -mr);
  vector<circ> res;
  circ CR;
  REP (i, SIZE(candidates)) if (check_pt_circles(C,P,candidates[i],CR)) res.PB(CR);
  return res; 
}

// SPIS FUNKCJI
//   ld gd(ld &x) // get_double
//   void pd(ld x) // print_double
//   iszero (ld x)
//   operator+, operator-, operator== (pt A, pt B)
//   operator* (ld lambda, pt A)
//   ppt, pptn, plin, plinn, pcirc, pcircn, plc, plcn - printfy
//   mpt (ld x, ld y), mlin (pt A, pt B), mseg (pt A, pt B), 
//     mcirc (pt O, ld R), mlincirc(lin L), mlincirc(circ C) - kreatory
//   ld cp(pt A, pt B) = A.X * B.Y - A.Y * B.X // iloczyn wektorowy
//   ld is(pt A, pt B) // iloczyn skalarny
//   ld na_prawo (pt A, lin L) // punkt na prawo od prostej skierowanej
//   ld lgt (pt A) // dlugosc
//   ld dist (pt A, pt B) // odleglosc
//   int intersect_lin_lin (lin K, lin L, pt &res) // przeciecie prostych
//   int triangle (ld a, ld b, ld c) // nier. trojkata, -1 - nie, 0 - rownosc, 1 - tak
// ** Wszystkie orientacje katow przeciwnie do wskazowek zegara
//   pt rotate_origin(ld theta, pt A) // obrot wokol (0,0)
//   pt rotate(ld theta, pt A, pt O) // obrot A wokol O
//   pt rotate_90_origin i rotate_90 (theta = 90)
//   ld angle (pt A, pt O, pt B) // Kat <AOB skierowany przeciwnie do wskazowek zegara, z [0,2PI)
//   ld angle (lin K, lin L) // Kat skierowany przeciwnie do wskazowek miedzy prostymi skierowanymi
//   pt rzut (pt A, lin L) // rzut A na L
//   int parallel (pt A, pt B) i int parallel (lin K, lin L) // rownoleglosc
//   lin perp (pt A, pt D) // prostopadla do D przez A
//   int between (A,M,B) // pomiedzy, 1 przy A = M lub B = M
//   int intersect_lin_seg(lin L, seg I, pt &W) // nie jesli I || L, nawet jesli jednopunktowe
//   int intersect_seg_seg(seg I, seg J, pt &W) // nie jesli I || J, nawet jesli tna sie w jednym punkcie
//   ld circ_segment_area (circ C, lin L) // Pole odcinka kolowego na lewo od prostej skierowanej, nieskierowane, zwraca 0 lub 2PI jesli C nie przecina L (w zaleznosci od tego, po ktorej stronie L lezy C)
//   ld circ_circ_area (circ C1, circ C2) // Pole przeciecia dwoch kol
//   int online (lin L, pt A) // punkt A na prostej L
//   int on_circ (pt A, circ C) // punkt A na okregu C
//   int intersect_lin_circ (lin K, circ C, pt &W1, pt &W2) // przeciecie prosta/okrag
//   int tangent_point (pt A, circ C, lin &W1, lin &W2) // proste styczne do C przez A
//   int intersect_circ_circ (circ C1, circ C2, pt &W1, pt &W2) // przeciecie okrag/okrag
//   int three_points(pt A, pt B, pt C, circ &R) // okrag z trzech punktow, zwraca zero, jesli dwa sie pokrywaja
//   int internal_tangent (circ C1, circ C2, lin &W1, lin &W2) // styczne wewnetrzne do C1 i C2. Wywala sie dla C1.R = C2.R = 0
//   int external_tangent (circ C1, circ C2, lin &W1, lin &W2) // styczne zewnetrzne do C1 i C2. Zwraca 0, gdy sie pokrywaja
// ** Inwersje punktow generalnie bez zabezpieczen przed dzieleniem przez zero
// ** Wszystkie inwersje o promieniu 1
//   pt invert_origin (pt A) // inwersja wzgledem (0,0)
//   pt invert(pt A, pt O) // inwersja A wzgledem O
//   lincirc invert (lin L, pt O) // inwersja L wzgledem O
//   lincirc invert (circ C, pt O) // inwersja C wzgledem O
//   lincirc invert (lincirc LC, pt O) // inwersja LC wzgledem O
//   vector<lin> tangent_lincirc (lincirc LC, pt P) // styczne do LC przez P (ew. rownolegle do LC przez P)
//   vector<lincirc> lincirc_point_point (lincirc LC, pt P1, pt P2) // styczne do LC przez P1 i P2
//   vector<lincirc> lincirc_lincirc_point (lincirc LC1, lincirc LC2, pt P) // styczne do LC1 i LC2 przez P
//   vector<circ> three_circles (circ C1, int P1, circ C2, int P2, circ C3, int P3) // styczne do trzech kol, 0 - zewnetrzne, 1 - wewnetrzne


// Wersja 1.01 (18.X)
//   - bugfix: lincirc_lincirc_point
//   - bugfix: three_circles
//   - add: na_prawo, angle
//   - add: lista funkcji

// Wersja 1.02 (24.IV.2010)
//   - bugfix: triangle (i funkcje pochodne, np. intersect_circ_circ)

// Wersja 1.03 (7.VI.2010)
//   - feature: uporzadkowalem kolejnosci zwracanych punktow w przecieciach z okregiem i stycznych
//   		(zmiany w intersect_lin_circ, intersect_circ_circ i tangent_point)
//   - add: circ_segment_area, circ_circ_area
//   (uwaga - nowa wersja tangent_point jest malo testowana. Nowe i_l_c, i_c_c, c_s_a oraz c_c_a dostaly accepta na zadaniu D z GCJ 2010, R2.)