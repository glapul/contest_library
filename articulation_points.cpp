#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 50007;
#define FOREACH(i,c) for(__typeof((c).begin()) i = (c).begin(); i!=(c).end();i++)
vector<int> graf[MAXN];
int d [MAXN];
int low [MAXN];
bool vis [MAXN];
int parent[MAXN];
int time;
void dfs(int v, int p)
{
    vis[v]=true;
    parent[v]=p;
    d[v]=time++;
    low[v]=d[v];
    FOREACH(i, graf[v])
    {
        if(!vis[*i])
            dfs2(*i,v);
    }
    FOREACH(i,graf[v])
        if(*i!=p)
        {
            low[v]=min(low[v], low[*i]);
            if(parent[*i]==v && d[v] < low[*i]) // <= dla p. artykulacji
                printf("%d %d\n",v,*i); // most
        }
}
