// Para najblizszych punktow O(n lg n)
// Adam Polak

const int MAXN = 100000;

typedef long long LL;
typedef pair<int, int> Point;
#define X first
#define Y second

bool cmpY(Point p, Point q) { return p.Y < q.Y || (p.Y == q.Y && p.X < q.X); }

inline LL dist2(Point p, Point q) { LL x = p.X-q.X, y = p.Y-q.Y; return x*x + y*y; }

int n;                  // INPUT, n >= 2
Point points[MAXN];     // INPUT
LL best_dist2;          // OUTPUT
Point best_p, best_q;   // OUTPUT

Point buf[MAXN];

void closest_pair(Point *points=points, int n=n, bool root=true) {
    if (n < 2) return;
    if (root) { sort(points, points+n, cmpY); best_dist2 = 1 + 8e18; }
    int mid = n/2; int midY = points[mid].Y;
    closest_pair(points, mid, false);
    closest_pair(points+mid, n-mid, false);
    double low = midY - sqrtl(best_dist2);
    double high = midY + sqrtl(best_dist2);
    inplace_merge(points, points+mid, points+n);
    int k = 0;
    for(int i=0; i<n; i++) if (points[i].Y > low && points[i].Y < high) {
        for(int j=max(0, k-6); j<k; j++)
            if (dist2(points[i], buf[j]) < best_dist2) {
                best_dist2 = dist2(points[i], buf[j]);
                best_p = points[i]; best_q = buf[j];
            }
        buf[k++] = points[i];
    }
}
