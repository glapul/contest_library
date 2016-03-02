#include <bits/stdc++.h>

using namespace std;


namespace flow {

#define int long long
#define REP(i, n) for(int i = 0; i < (n); i++)
const int MX = 2007;
const int INF = 1LL<<60;

int d[MX], pt[MX];
bool vis[MX];
int f[MX][MX];
int flow = 0, n, source, sink;

void clear() {
  REP(i, n)
    d[i] = pt[i] = vis[i] = 0;
  REP(i, n)
    REP(j, n)
      f[i][j] = 0;
  flow = 0;
}

bool bfs()
{
    for(int i=0;i<=n;i++)
    {
        d[i]=-1;
        pt[i]=0;
    }
    queue<int> q;
    q.push(source);
    d[source]=0;
    while(!q.empty())
    {
        int akt = q.front();
        q.pop();
        auto& tmp = f[akt];
        for(int i=0;i<n;i++)
        {
            if(tmp[i] && d[i]==-1)
            {
                d[i]=d[akt]+1;
                q.push(i);
            }
        }
    }
    return d[sink]!=-1;
}
long long dfs(int v,long long cap)
{
    if(v==sink || cap==0)
        return cap;
    int sum=0;
    for(;pt[v]<n;pt[v]++)
    {
      int& cur_f = f[v][pt[v]];
        if(d[pt[v]]==d[v]+1 && cur_f)
        {
            int pushed = dfs(pt[v],min(cap,cur_f));
            cur_f-=pushed;
            f[pt[v]][v]+=pushed;
            sum+=pushed;
            cap-=pushed;
            if(cap==0)
                break;
        }
    }
    return sum;
}
long long get_max_flow()
{
    while(bfs())
        flow+=dfs(source,INF);
    return flow;
}
}
main()
{
    int z;
    scanf("%lld",&z);
    while(z--)
    {
        int  m;
        scanf("%lld %lld %lld %lld", &flow::n, &m, &flow::source, &flow::sink);
        flow::n++;
        for(int i =0 ; i<m; i++) {
          int a, b, c;
          scanf("%lld %lld %lld", &a, &b, &c);
          flow::f[a][b] += c;
        }
        printf("%lld\n",flow::get_max_flow());
        flow::clear();
    }
}
