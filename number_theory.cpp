#include<cstdlib>
#include<time.h>
#include<vector>
#include<algorithm>
using namespace std;

struct NT
{
    long long gcd( long long a, long long b) // Euclidean algorithm
    {
        return b==0 ? a : gcd(b,a%b);
    }
    long long ex_gcd_x,ex_gcd_y;
    long long ex_gcd(long long a, long long b) // Extended euclidean algorithm. x and y are in ex_gcd_x and ..._y .
    {
        if (b==0)
        {
            ex_gcd_x=1;
            ex_gcd_y=0;
            return a;
        }
        else
        {
            long long d = ex_gcd(b,a%b);
            long long tmp = ex_gcd_y;
            ex_gcd_y = ex_gcd_x - (a/b)*ex_gcd_y;
            ex_gcd_x=tmp;
            return d;
        }
    }
    long long modular_inverse(long long a, long long n) // assumes that modular inverse does exist.
    {
        ex_gcd(a,n);
        ex_gcd_x%=n;
        ex_gcd_x+=n;
        ex_gcd_x%=n;
        return ex_gcd_x;
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
    //use this if 32 bit processor and you are dealing with ints only
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
    bool miller_rabin(long long n) //miller-rabin primality test, in the deterministic variant
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
    long long tab [5] = {1,-1,3,5,2}; // DO NOT TOUCH
    long long C; // DO NOT TOUCH
    long long rho (long long x, long long n) // rho function. DO NOT TOUCH
    {
        return (modular_exponentation(x,2,n)+ C+2*n)%n;
    }
    long long find_factor(long long n) // finds a factor in the pollard's rho heuristic
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
    vector<long long> rho_pollard_factor(long long n) // returns vector of primes whose product equals n. NOT SORTED.
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
    vector<long long> slow_factor(long long n) // O(sqrt(n)) factorization. Needed for pollards_rho!
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
