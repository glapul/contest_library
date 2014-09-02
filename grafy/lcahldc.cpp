#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
#define FOREACH(i,c) for(__typeof((c).begin()) i = (c).begin();i!=(c).end();i++)
const int MAXN = 100007;
vector<int> graf [MAXN];
int parent[MAXN];
int skip[MAXN];
int depth[MAXN];
int size[MAXN];

int dfs(int v)
{
    size[v]=1;
    FOREACH(i,graf[v])
        if(*i!=parent[v])
        {
            parent[*i]=v;
            depth[*i]=depth[v]+1;
            size[*i] = dfs(*i);
            size[v]+=size[*i];
        }
    return size[v];
}
void skipdfs(int v)
{
    skip[v]=v;
    if(v!=0 && 2*size[v] > size[parent[v]])
        skip[v] = skip[parent[v]];
    FOREACH(i,graf[v])
        if(*i!=parent[v])
            skipdfs(*i);
}

int lca (int u, int v)
{
    int last=-1;
    while(u!=v)
    {
        if(depth[u] > depth[v])
            swap(u,v);
        if(skip[v]!=v)
        {
            last=v;
            v=skip[v];
        }
        else
        {
            last=-1;
            v=parent[v];
        }
    }
    return last == -1 ?v :last;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        graf[a].push_back(b);
        graf[b].push_back(a);
    }
    dfs(0);
    skipdfs(0);
    int q;
    scanf("%d",&q);
    for(int i =0;i<q;i++)
    {
        int a,b;
        scanf("%d %d",&a,&b);
        printf("%d\n",lca(a,b));
    }
}
