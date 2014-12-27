//Michał Glapa
#include<bits/stdc++.h>
using namespace std;
#define FOR(i,j,k) for(int i=j;i<=k;i++)
#define REP(i,n) for(int i=0;i<n;i++)
#define FORD(i,j,k) for(int i=j;i>=k;i--)
#define ll long long
//Make sure no overflow problems
#define int long long
#define pb push_back
#define mp make_pair
#define x first
#define y second
#define all(x) x.begin(),x.end()
#define ld long double
#define mini(x,y) x=min(x,y)
#define maxi(x,y) x=max(x,y)
#define CLR(a,x) memset(a,x,sizeof(a))
#define SIZE(x) ((int)x.size())
const int INF = 1000000009;
const long long INFLL = (ll)INF * (ll)INF;
const ld EPS = 10e-9;
typedef vector<int> vi;
typedef pair<int,int> pii;

//reading and printing
template<typename T>
void read(T & a) {cin >> a;}
template<typename T>
void read(vector<T> & v, int n) {int tmp; REP(i,n){read(tmp); v.pb(tmp);};}
template<typename T, typename V>
void read(pair<T,V> & p) {read(p.x); read(p.y);}
template<typename T>
void print(T & a) {cout << a << "\n";}
void print(char * s) {printf("%s\n",s);}
template<typename T>
void print_(T & a) {cout << a <<" ";}
template<typename T>
void print(vector<T> &v) {for(auto &i : v) print_(i); cout<<"\n";}
template<typename T,typename V>
void print(pair<T,V> &p) {print_(p.x);print(p.y);}
template<typename T,typename V>
void print_(pair<T,V> &p) {print_(p.x);print_(p.y);}

//useful funcs
template<typename T>
void unique(vector<T> & v) {v.resize(unique(v.begin(),v.end())-v.begin());}
vi range (int a, int b) {vi res; FOR(i,a,b-1) res.pb(i); return res;}
vector<pii> zip(vi &a, vi & b) {vector<pii> res; REP(i,SIZE(a)) res.pb(mp(a[i],b[i])); return res;}
vector<pii> zip(vi a, vi  b) {vector<pii> res; REP(i,SIZE(b)) res.pb(mp(a[i],b[i])); return res;}

///////////////////////////////////////////////////////////////
main()
{

}
