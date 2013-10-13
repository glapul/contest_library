
#include<vector>
#include<complex>
#include<cmath>
using namespace std;
struct FFT
{
    vector<complex<double> > org, res, tmp,e;
    int n;
    vector<complex<double> > compute_inverse( vector<complex<double> > x)
    {
        // x's length must be a power of 2
        org=x;
        n=x.size();
        res =vector<complex<double > > (n);
        tmp =vector<complex<double > > (n);
        e =vector<complex<double > > (n);
        for (int i=0;i<n;i++)
            e[i] = exp((2*M_PI*i*complex<double> (0,1))/(double)n);
        fft(n);
        for(int i=0;i<n;i++)
            res[i]/=n;
        return res;
    }
    vector<complex<double> > poly_mult(vector<complex<double> > u, vector<complex < double > > v)
    {
        int s = u.size()+v.size();
        u.resize(s);
        v.resize(s);
        while((((int)u.size())&((-(int)u.size()))) != (int)u.size())
        {
            u.push_back(0);
            v.push_back(0);
        }
        vector<complex<double> > dftu = compute(u), dftv = compute(v),res;
        for(int i=0;i<(int)dftu.size();i++)
            res.push_back(dftu[i]*dftv[i]);
        return compute_inverse(res);
    }
    vector<complex<double> > compute( vector<complex<double> > x)
    {
        // x's length must be a power of 2
        org=x;
        n=x.size();
        res =vector<complex<double > > (n);
        tmp =vector<complex<double > > (n);
        e =vector<complex<double > > (n);
        for (int i=0;i<n;i++)
            e[i] = exp(-(2*M_PI*i*complex<double> (0,1))/(double)n);
        fft(n);
        return res;
    }

    void fft(int l, int p=0,int s=1,int q=0)
    {
        if(l==1)
        {
            res[q]=org[p];
            return;
        }
        int pt = 0;
        fft(l/2,p,2*s,q);
        fft(l/2,p+s,2*s,q+l/2);
        for(int i=0;i<l/2;i++)
        {
            tmp[i] = res[q+i]+e[pt]*res[q+l/2+i];
            tmp[i+l/2] = res[q+i] - e[pt]*res[q+l/2+i];
            pt+=s;
            pt%=n;
        }
        for(int i=0;i<l;i++)
            res[q+i]=tmp[i];
    }
};

