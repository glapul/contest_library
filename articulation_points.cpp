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
int root=1;
void dfs(int v, int p)
{
    vis[v]=true;
    parent[v]=p;
    d[v]=time++;
    low[v]=d[v];
    FOREACH(i,graf[v])
    {
        if(!vis[*i])
            dfs2(*i,v);
    }
    if(v==root && graf[v].size()>1)
    {
        printf("p.art. %d\n",v);
        return;
    }
    FOREACH(i,graf[v])
        if(*i!=p)
        {
            low[v]=min(low[v], low[*i]);
            /*
             * Punkty artykulacji:
             *  Korzeń jeśli ma >= 2 synów
             *  inny wierzchołek v : jeśli jakiś jego syn _w_drzewie_dfs_ w ma low[w] <= d[parent[v]]
             */
            if(parent[*i]==v && low[*i] > d[parent[v]])
                printf("p.art. %d\n",v);
            //Mosty
            // u->v
            // low[v] > d[u]
            if(parent[*i]==v && d[v] < low[*i])
                printf("most %d %d\n",v,*i); // most
        }
}
