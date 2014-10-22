/*
 * contains classical geometrical algorithms.
 * Works on integer point coordinates.
 */
#include<vector>
#include<algorithm>
#include<cassert>
#include<cmath>
using namespace std;
//#define int long long //uncomment this to use long long instead of int. Beware of long long overflow!
struct point
{
    //also treated like a vector. If a function uses point as a vector there is an adequate comment in its definition
    long long x,y;
    point():x(0),y(0) {}
    point(long long x, long long y): x(x),y(y){}
    point(pair<long long,long long> p) : x(p.first),y(p.second){}
    bool operator==(const point & other) const
    {
        return make_pair(this->x,this->y)==make_pair(other.x, other.y);
    }
    point operator+ (point & other)
    {
        return point(this->x+other.x,this->y+other.y);
    }
    point operator-(const point & other) const
    {
        return point(this->x-other.x,this->y-other.y);
    }
    point operator*(long long a) const
    {
        return point(x*a,y*a);
    }
    point operator/(long b) const
    {
        return point(x/b,y/b);
    }
    long long length_squared() // beware of overflow
    {
        return x*x+y*y;
    }
    bool operator< (const point & other) const
    {
        return make_pair(this->y,this->x) < make_pair(other.y,other.x);
    }
    bool operator<= (const point & other) const
    {
        return make_pair(this->y,this->x) <= make_pair(other.y,other.x);
    }
};
long long dot_product(point &a, point &b)
{
    return a.x*b.x+a.y*b.y;
}
long long vector_product(const point & a,const point & b)
{
    return a.x*b.y-b.x*a.y;
}
bool CCW(point left, point right) // checks if the shorter path from right to left is going counterclockwise
{
    return vector_product(left,right) <=0;
}
bool colinear(point &a, point &b) // (a,b) IS COLINEAR to (-a,-b)
{
    return vector_product(a,b)==0;
}
struct angle_comparer
{
    point zero;
    angle_comparer(point zero):zero(zero){}
    bool operator()(point a, point b)
    {
        return CCW(a-zero,b-zero);
    }
};
vector<point> polar_sorted_around_point(vector<point> &v, point center) //assumes that center isn't in v
{
    vector<point> upper, lower;
    for(auto &i: v)
        if(i.x>=center.x)
            upper.push_back(i);
        else
            lower.push_back(i);
    sort(upper.begin(),upper.end(),angle_comparer(center));
    sort(lower.begin(),lower.end(),angle_comparer(center));
    upper.insert(upper.end(),lower.begin(),lower.end());
    return upper;
}
bool better(point x, point y, point z)
{
    if(vector_product(z-x,y-x)<0 || (vector_product(z-x,y-x)==0 && (z-x).length_squared() > (y-x).length_squared()))
        return true;
    return false;
}
vector<point> convex_hull(vector<point> points)
{

    auto compute_partial = [&] (vector<point> & points)
    {
        vector<point> res = {points[0],points[1]};
        for(int i=2;i<points.size();i++)
        {
            while(res.size()>=2 && better(res[res.size()-2],res.back(),points[i]))
                res.pop_back();
            res.push_back(points[i]);
        }
        return res;

    };
    sort(points.begin(),points.end());
    vector<point> upper = compute_partial(points);
    reverse(points.begin(),points.end());
    vector<point> lower = compute_partial(points);
    upper.pop_back();
    lower.pop_back();
    upper.insert(upper.end(),lower.begin(),lower.end());
    return upper;
}
struct segment
{
    point first, second;
    segment():first(point()),second(point()){}
    segment(point first, point second):first(first),second(second){}
    segment(pair<point,point>p):first(p.first), second(p.second){}
    long long length_squared()
    {
        return (first-second).length_squared();
    }
    double length()
    {
        return sqrt(length_squared());
    }
};
#define st first
#define nd second
#define _ll long long
bool intersect(segment & a, segment & b)
{
    _ll bst = vector_product(a.st-b.st, a.nd-b.st),
        bnd = vector_product(a.st-b.nd, a.nd-b.nd),
        ast = vector_product(b.st-a.st, b.nd-a.st),
        anD = vector_product(b.st-a.nd, b.nd-a.nd);
    if(ast*bst!=0)
    {
        if(ast < 0 && )
    }

}



