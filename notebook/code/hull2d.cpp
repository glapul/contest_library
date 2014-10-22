// WYPUKŁA OTOCZKA 2D
// Maciek Wawro

typedef int T; const T EPS = 0;
//typedef double T; const T EPS = 1e-9;
typedef pair<T,T> Point;
//class Point:public pair<T,T>{public: int id;}; 

const int MAXN = 100000;

int N;                //IN: Liczba punktów
Point points[MAXN];   //IN: Punkty - psute! (sort)
int H;                //OUT:Wielkość otoczki
Point hull[MAXN+5];   //OUT:Kolejne punkty w kolejności CCW

inline bool ccw(Point& a, Point& b, Point& c){
  T A[] = {a.st-b.st,a.nd-b.nd,b.st-c.st,b.nd-c.nd};
  T det = A[0]*A[3] - A[1]*A[2];  //Dla T=int -> uwzględnić rozmiar (LL)!
  T cro = A[0]*A[2] + A[1]*A[3];  //Dla T=int -> uwzględnić rozmiar (LL)!
  return (det > EPS) || ((det>=-EPS) && (cro < -EPS));
}; //Zamienić na det>=-EPS dla "słabej" wypłuczki (uwaga na wszystkie współliniowe!)

inline void addPoint(int i){
  while((H > 1) && (!ccw(hull[H-2], hull[H-1], points[i])))H--;
  hull[H++] = points[i];  
}
void computeHull(){
  int d = 0;
  sort(points, points+N);
  //N = unique(points, points+N)-points;// Potrzebne TYLKO jeśli N>1 i wszystkie równe
                                        //     (można obsłużyć inaczej)
  H = 0;                                       
  REP(i,N)addPoint(i);
  if(N<2)return;
  FORD(i,N-1,0)addPoint(i);  
  H--;
}
