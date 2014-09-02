#include<vector>
#include<cstdio>
#include<iostream>
#include<algorithm>
const int MAXN = 1000007;
using namespace std;
const long long P = (long long)1000000009 * 1000000009;
const long long x = 137;
long long potP [MAXN];
long long mul(long long a, long long b, long long p)
{
    long long r=0;
    while(b>0)
    {
        if(b&1)
        {
            r+=a;
            if(r>=p)
                r-=p;
        }
        a<<=1;
        if(a>=p) a-=p;
        b>>=1;
    }
    return r;
}
struct hashword
{
    vector<long long> prefixes;
    hashword(){}
    hashword(string & s)
    {
        long long tmp = 0;
        for(int i=0;i<s.length();i++)
        {
            if(potP[i]==0)
                potP[i]= i==0 ? 1 : mul(potP[i-1],x,P);
            tmp+= s[i];
            tmp %=P;
            prefixes.push_back(tmp);
            tmp = mul(tmp,x,P);
        }
    }
    long long get_hash(int i, int j)
    {
        return (prefixes[j] - (i==0 ? 0 : mul(prefixes[i-1],potP[j-i+1],P)) + P) %P;
    }
};

int main()
{
    string word;
    cin >> word;
    hashword h = hashword(word);
    cout << h.get_hash(0,7) << " " << h.get_hash(8,15);
}

