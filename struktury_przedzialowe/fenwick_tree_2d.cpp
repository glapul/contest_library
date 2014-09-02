#include<cstdio>
using namespace std;

const int MX = 1000;
int tp[MX][MX];
void update(int x, int y, int v)
{
    for(;x<MX;x+=x&-x)
        for(int yy=y;yy<MX;yy+=yy&-yy)
            tp[x][yy]+=v;
}
int query(int x, int y)
{
    int res=0;
    for(;x>0;x-=x&-x)
        for(int yy=y;yy>0;yy-=yy&-yy)
            res+=tp[x][yy];
    return res;
}
int rect_query(int x1, int x2, int y1, int y2) //x1>=x2, y1>=y2
{
    return query(x1,y1)-query(x2-1,y1)-query(x1,y2-1)+query(x2-1,y2-1);
}
