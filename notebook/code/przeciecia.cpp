// ZNAJDOWANIE PARY PRZECINAJACYCH SIE ODCINKOW
// NIE UWZGLEDNIA WSPOLNYCH KONCOW
// Robert Obryk

bool on_segment(const P&p, const segment &s) // (*)
  { return min(s.a.x, s.b.x)<p.x-EPS && p.x<max(s.a.x, s.b.x)-EPS &&
           min(s.a.y, s.b.y)<p.y-EPS && p.y<max(s.a.y, s.b.y)-EPS; }
// Czy dwa odcinki maja wspolny punkt?
bool intersect(const segment &s1, const segment &s2) {
    K d1 = det(s2.b-s2.a, s1.a-s2.a), d2 = det(s2.b-s2.a, s1.b-s2.a),
      d3 = det(s1.b-s1.a, s2.a-s1.a), d4 = det(s1.b-s1.a, s2.b-s1.a);
    return (d1>EPS && d2<-EPS || d1<-EPS && d2>EPS) &&
           (d3>EPS && d4<-EPS || d3<-EPS && d4>EPS) ||
           fabs(d1)<=EPS && on_segment(s1.a, s2) ||
           fabs(d2)<=EPS && on_segment(s1.b, s2) ||
           fabs(d3)<=EPS && on_segment(s2.a, s1) ||
           fabs(d4)<=EPS && on_segment(s2.b, s1);
}
 
struct event {
    xy pkt;
    int idx;
    bool begin;
    event(xy _pkt, int _idx, bool _begin) : pkt(_pkt), idx(_idx), begin(_begin) {}
};

bool operator<(const event&a, const event&b) {
    if (a.pkt.x != b.pkt.x)
        return a.pkt.x < b.pkt.x;
    if (a.pkt.y != b.pkt.y)
        return a.pkt.y < b.pkt.y;
    return a.begin && !b.begin;
}

struct idx_segment {
    segment s;
    int idx;
    idx_segment(segment _s, int _idx) : s(_s), idx(_idx) {}
};

bool operator<(const idx_segment& a, const idx_segment& b)
{
    if (intersect(a.s, b.s) && a.idx != b.idx)
        throw make_pair(a.idx, b.idx);
    if (a.idx == b.idx)
        return false;
    K d1 = det(b.s.b-b.s.a, a.s.a-b.s.a);
    K d2 = det(b.s.b-b.s.a, a.s.b-b.s.a);
    if (d1 <= 0 && d2 <= 0)
        return true;
    if (d1 >= 0 && d2 >= 0)
        return false;
    return !(b < a);
}

bool do_cross(vector<segment>& segments, pair<int, int>& which)
{
    vector<event> events;
    for(int i=0;i<segments.size();i++) {
        segment &seg = segments[i];
        if (seg.b.x < seg.a.x || (seg.b.x == seg.a.x && seg.b.y < seg.a.y))
            swap(seg.a, seg.b);
        events.push_back(event(seg.a, i, true));
        events.push_back(event(seg.b, i, false));
    }
    sort(events.begin(), events.end());
    try {
        set<idx_segment> s;
        for(vector<event>::iterator eit = events.begin(); eit != events.end(); ++eit) {
            if (!eit->begin) {
                set<idx_segment>::iterator it, jt, kt;
                it = s.find(idx_segment(segments[eit->idx], eit->idx));
                if (it != s.begin()) {
                    jt = it; jt--;
                    kt = it; kt++;
                    if (kt != s.end())
                        (void)(*kt < *jt);
                }
                s.erase(idx_segment(segments[eit->idx], eit->idx));
            } else
                s.insert(idx_segment(segments[eit->idx], eit->idx));
        }
    } catch (pair<int,int>& c) {
        which = c;
        return true;
    }
    return false;
}
