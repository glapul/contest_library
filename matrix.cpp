#include<iostream>
#include<set>
#include<map>
#include<algorithm>
#include<vector>
#include<string>
using namespace std;



struct Exception
{
    string s;
    Exception(){}
    Exception(string s) : s(s){}
};
class modularInt
{
    public:
        long long x;
        modularInt(int val =0)
        {
            x = val%P;
            if(x<0)
                x+=P;
        }
        static modularInt zero ()
        {
            return modularInt();
        }
        static modularInt one()
        {
            return modularInt(1);
        }
        modularInt operator + (modularInt & other)
        {
            return modularInt(this->x+other.x);
        }
        modularInt operator - (modularInt & other)
        {
           return modularInt(this->x-other.x);
        }
        modularInt operator *(modularInt & other)
        {
            return modularInt(this->x*other.x);
        }
        modularInt inverse()
        {
            if((*this)==zero())
                throw(Exception("0 has no inverse!"));
            else
                return pow(P-2);
        }
        modularInt operator/(modularInt & other)
        {
            if(other == zero())
                throw(Exception("Division by 0"));
            return  (*this)* other.inverse();
        }
        static void setP (long long v)
        {
            P=v;
        }
    private:
        static long long P;
        modularInt pow (long long n)
        {
            modularInt res = one(), a = (*this);
            while(n)
            {
                if(n & 1)
                    res*=a;
                n/=2;
                a*=a;
            }
            return res;
        }

};
template <typename T>
class Matrix
{
    /*
     * T must be an element of a field, i.e. must provide operators ==,+, *, /(for Gauss elimination related issues), method inverse()
     * and static methods zero() and one()
     */

};

int main()
{
    modularInt::P=29;

}
