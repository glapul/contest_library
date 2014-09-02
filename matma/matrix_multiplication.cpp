#include<cstdio>
#include<vector>
#include<algorithm>
#include<cassert>
using namespace std;
const long long MOD = (1e9)+7;
typedef vector<long long> row;
typedef vector<row > matrix;
matrix mult(matrix & a, matrix & b)
{
    assert(a[0].size() == b.size());
    int n = a[0].size();
    matrix res;
    res.resize(a.size());
    for(auto &i : res)
        i.resize(b[0].size());
    for(int i=0;i<a.size();i++)
        for(int j = 0;j<b[0].size();j++)
            for(int k=0;k<n;k++)
            {
                res[i][j] += a[i][k]*b[k][j];
                res[i][j] %= MOD;
            }
    return res;
}
matrix square_unit_matrix(int n)
{
    matrix res;
    res.resize(n);
    for(auto &i: res)
        i.resize(n);
    for(int i=0;i<n;i++)
        res[i][i]=1;
    return res;
}
matrix pow(matrix a, long long k)
{
    assert(a.size()==a[0].size());
    matrix res = square_unit_matrix(a.size());
    while(k)
    {
        if(k%2)
            res = mult(res,a);
        a=mult(a,a);
        k/=2;
    }
    return res;
}
