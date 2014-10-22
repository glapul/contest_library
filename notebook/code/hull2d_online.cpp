// WYPUKŁA OTOCZKA 2D ONLINE O(log n) / query
// + SPRAWDZANIE NAJDALEJ WYSUNIĘTEGO PUNKTU O(log^2 |H|)
// Maciek Wawro

typedef int T; const T EPS = 0;
//typedef double T; const T EPS = 1e-9;
typedef pair<T,T> Point;

inline bool ccw(Point a, Point b, Point c){
    return (a.st - b.st) * (b.nd-c.nd) - (a.nd-b.nd) * (b.st-c.st) > EPS; 
};  

template <typename Set, typename It>
bool checkAndRemove(Set& hull, It it) {
    It next = it, prev = it;
    if (it == hull.begin() || (++next) == hull.end()) return false;
    --prev;
    if (ccw(*prev,*it,*next)) return false;
    hull.erase(it);
    return true;
}

template <typename Set>
void insert(Set& hull, Point a) {
    typedef typename Set::iterator It;
    It it = hull.insert(a).first, prev, next;    
    if (checkAndRemove(hull, it)) return;
    while (it != hull.begin() && checkAndRemove(hull, --(prev=it)));
    while (++(next=it) != hull.end() && checkAndRemove(hull, next));
}

set<Point, greater<Point> > upperHull; // Górna (+ prawa) otoczka od prawej do lewej
set<Point> lowerHull; // Dolna (+lewa) otoczka od lewej do prawej
void insert(Point a) {
    insert(upperHull, a);
    insert(lowerHull, a);
}

// Zeby uzyc maximizeDot, zastapic deklaracje upperHull, lowerHull przez:

inline T dot(Point a, Point b) {
    return a.first * b.first + a.second * b.second;
}

bool bitonic = false;

struct UComparator { bool operator()(Point a, Point b); }; 
set<Point, UComparator> upperHull;

bool UComparator :: operator()(Point a, Point b) {
    if (!bitonic) return a > b;
    bitonic = false;        
    set<Point>::iterator it = ++upperHull.find(a);
    bitonic = true;    
    return it != upperHull.end() && dot(*it, b) >= dot(a, b);
}

struct LComparator { bool operator()(Point a, Point b); }; 
set<Point, LComparator > lowerHull;

bool LComparator :: operator()(Point a, Point b) {
    if (!bitonic) return a < b;
    bitonic = false;        
    set<Point>::iterator it = ++lowerHull.find(a);
    bitonic = true;    
    return it != lowerHull.end() && dot(*it, b) >= dot(a, b);
}

// Dziala w czasie O(log^2 |hull|)
Point maximizeDot(Point v) {
    bitonic = true;
    Point result = v.second >= 0 ? *upperHull.lower_bound(v)
                                 : *lowerHull.lower_bound(v);
    bitonic = false;
    return result;
}
