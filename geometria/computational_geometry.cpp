#include<cstdio>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;

#define TYPE int //typ zmiennej, w której mieszczą się współrzędne (int, ll, double)
#define EPS 0

struct point // również wektor
{
    TYPE x,y;
    point (){}
    point (TYPE x, TYPE y) : x(x),y(y)
    {}
    bool operator== (const point & other) const
    {
        return abs(this->x-other.x)<=EPS && abs(this->y-other.y)<=EPS;
    }
    point operator+ (const point & other)const
    {
        return point(this->x+other.x,this->y+other.y);
    }
    point operator- (const point & other)const
    {
        return point(this->x-other.x,this->y-other.y);
    }
    TYPE operator* (const point & other) const
    {
        return this->x*other.x+this->y*other.y;
    }
    bool operator< (const point & other) const
    {
        return make_pair(this->y,this->x) < make_pair(other.y,other.x)
    }
    TYPE len2()
    {
        return x*x+y*y;
    }

};

bool equal(TYPE a, TYPE b)
{
    return abs(a-b)<=EPS;
}

TYPE vp (point a, point b)
{
    return a.x*b.y-a.y*b.x;
}

bool anglecmp(point a, point b)
{
    return make_pair(vp(a,b),a.len2()) < make_pair(0,b.len2());
}

point point_in_infinity = point(999399999.0,999993999.0); //punkt w nieskończoności

struct line
{
    point a,b;
    line (point a, point b) : a(a),b(b)
    {}
};

point line_intersection(line p, line q) // zwraca point_in_infinity jesli rownolegle
{

}

vector<point> convex_hull (vector<point> & sequence)
{
    vector<point>::iterator min = sequence.begin(), last = --sequence.end();
    for(vector<point>::iterator i = sequence.begin(); i!=sequence.end(),i++)
        if(*i < *min)
            min=i;
    point min_p = *min;
    swap(min,last);
    sequence.pop_back();
    for(vector<point>::iterator i=sequence.begin(); i!=sequence.end();i++)
        *i-=min_p;
    sort(sequence.begin(),sequence.end(),anglecmp);
    for(vector<point>::iterator i=sequence.begin(); i!=sequence.end();i++)
        *i+=min_p;
    vector <point> ch;

}

struct circle
{

};
