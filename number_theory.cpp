#include<cstdio>
#include<cstdlib>
#include<time.h>
#include<vector>
#include<algorithm>
using namespace std;

struct NumberTheory
{
    long long gcd( long long a, long long b)
    {
        return b==0 ? a : gcd(b,a%b);
    }
    long long modular_exponentation(long long a, long long k, long long mod)
    {
        long long r=1;
        while(k>0)
        {
            if(k&1)
                r=mul(r,a,mod);
            a=mul(a,a,mod);
            k/=2;
        }
        return (r+mod)%mod;
    }
    /*
    inline long long mul(long long a, long long b, long long c)
    {
        return ((a*b)%c+c)%c;
    }
*/
    //use this if 32bit processor and big numbers
    /*
    long long mul(long long a, long long b, long long c)
    {
        long long res=0;
        while(b)
        {
            if(b&1LL)
            {
                res+=a;
                res%=c;
            }
            a<<=1;
            if(a>=c)
                a-=c;
        }
        return res;
    }
    */
    //use this on 64bit processor
    long long mul(long long a, long long b, long long p) // piob mowi, ze dziala
    {
        long long res;
        asm( "mulq %%rbx ;" "divq %%rcx ;" : "=d"(res) : "a"(a), "b"(b), "c"(p) );
        return res <0 ? res+p : res;
    }
    bool miller_rabin(long long n)
    {

        int a [11] = {2,3,5,7,11,13,17,19,23,29,31};
        if(n<32)
        {
            for(int i=0;i<11;i++)
                if(a[i]==n)
                    return true;
            return false;
        }
        if(n%2==0)
            return 0;
        long long s = (n-1)&(-(n-1));
        long long d = (n-1)/s;
        for(int k=0;k<11;k++)
        {
            long long x = modular_exponentation(a[k],d,n);
            if(gcd(x,n)!=1)
                return 0;
            if(x!=1 && x!=n-1)
            {
                int i=0;
                for(;1LL<<i <s;i++)
                {
                    x=mul(x,x,n);
                    if(x==1 || x==0)
                        return 0;
                    if(x==n-1)
                        break;
                }
                if(1LL<<i==s && x!=n-1)
                    return 0;
            }
        }
        return 1;
    }
    long long tab [5] = {1,-1,3,5,2};
    long long C;
    long long rho (long long x, long long n)
    {
        return (modular_exponentation(x,2,n)+ C+2*n)%n;
    }
    long long find_factor(long long n)
    {
        C=tab[rand()%5];
        long long x=2, y=2,d=1;
        while(d==1)
        {
            x = rho(rho(x,n),n);
            y = rho(y,n);
            d = gcd(abs(x-y),n);
        }
        if(d==n)
            return -1;
        return d;
    }
    vector<long long> rho_pollard_factor(long long n)
    {
        srand(time(NULL));
        if(miller_rabin(n))
        {
            vector<long long> res;
            res.push_back(n);
            return res;
        }
        if(n<100)
            return slow_factor(n);
        vector<long long> res,res2;
        long long d = find_factor(n);
        while(d==-1)
            d=find_factor(n);
        res  =rho_pollard_factor(d);
        res2=rho_pollard_factor(n/d);
        res.insert(res.end(),res2.begin(),res2.end());
        return res;
    }
    vector<long long> slow_factor(long long n)
    {
        long long d=n;
        vector<long long > res;
        for(int i=2;i*i<=d;i++)
        {
            while(n%i==0)
            {
                res.push_back(i);
                n/=i;
            }
        }
        if(n>1)
            res.push_back(n);
        return res;
    }
};
int main()
{
    NumberTheory x;
    for(int i=2;i<500;i++)
        if(x.miller_rabin(i))
            printf("%d ",i);
    printf("\n");
    for(long long i=1000000000000000000LL;i<1000000000000000099LL;i++)
    {
        vector<long long> tmp = x.rho_pollard_factor(i);
        sort(tmp.begin(),tmp.end());
            printf("%lld = ",i);
            for(int j=0;j<tmp.size();j++)
                printf("%lld ",tmp[j]);
            printf("\n");
    }
}
