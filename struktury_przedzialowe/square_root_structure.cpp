#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;

const int MX = 100007;
const int SQ = 330;
int a[MX];
int n;
struct block
{
    int p,q;
    int added_value, sum;
    block(){}
    block(int p, int q):p(p),q(q)
    {
        added_value=sum=0;
        for(int i=p;i<=q;i++)
            sum+=a[i];
    }
    void rebuild()
    {
        if(added_value)
            for(int i=p;i<=q;i++)
                a[i]+=added_value;
        sum=added_value=0;
        for(int i=p;i<=q;i++)
            sum+=a[i];
    }
    void add(int qp, int qq, int v)
    {
				if(qp > q || qq < p)
					return;
        if(qp<=p && qq>=q)
        {
            added_value+=v;
            sum+=(q-p+1)*v;
        }
        else
        {
            rebuild();
            int tp = max(p,qp), tq = min(q,qq);
            for(int i=tp;i<=tq;i++)
            {
                sum+=v;
                a[i]+=v;
            }
        }

    }
    int query(int qp, int qq)
    {
				if(qp > q || qq < p)
					return 0;
        if(qp<=p && qq>=q)
        {
            return sum;
        }
        else
        {
            rebuild();
            int res=0;
            int tp = max(p,qp), tq = min(q,qq);
            for(int i=tp;i<=tq;i++)
                res+=a[i];
            return res;
        }

    }

};
vector<block> blocks;
int query(int p, int q)
{
    int res=0;
    for(auto &i : blocks)
        res+=i.query(p,q);
    return res;
}
void add(int p, int q,int v)
{
    for(auto &i:blocks)
        i.add(p,q,v);
}
void construct()
{
    int last=0;
    for(int i=0;i<n;i++)
        if(i-last>=SQ)
        {
            blocks.push_back(block(last,i));
            last=i+1;
        }
    if(last!=n)
        blocks.push_back(block(last,n-1));
}
main()
{

}
