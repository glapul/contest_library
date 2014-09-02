#include<algorithm>
#include<vector>
using namespace std;
class LCATree
{
    public:
        int lca(int u,int v)
        {
            if(!ready)
                compute();
            int last=-1;
            while(u!=v)
            {
                if(d[u]>d[v])
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
            return last==-1 ?v : last;
        }
        LCATree(int n, int root):n(n),root(root)
        {
            graph = vector<vector<int> > (n)
            parent = vector<int> (n)
            parent[root]=-1;
            d = vector<int> (n);
            size = vector<int> (n);
            skip = vector<int> (n);
            ready=false;
        }
        void add_edge(int u, int v)
        {
            graph[u].push_back(v);
            graph[v].push_back(u);
            ready=false;
        }
        void set_root(int newroot)
        {
            root=newroot;
            ready=false;
            parent[root]=-1;
        }
    private:
        vector<vector<int> > graph;
        vector<int> parent;
        vector<int> d;
        vector<int> size;
        vector<int> skip;
        int root,n;
        bool ready;
        int dfs(int v)
        {
            size[v]=1;
            FOREACH(i,graph[v])
                if(*i!=parent[v])
                {
                    parent[*i]=v;
                    d[*i]=d[v]+1;
                    size[*i]=dfs(*i);
                    size[v]+=size[*i];
                }
            return size[v];
        }
        void skipdfs(int v)
        {
            skip[v]=v;
            if(v!=root && 2*size[v] > size[parent[v]])
                skip[v]=skip[parent[v]];
            FOREACH(i,graf[v])
                if(*i!=parent[v])
                    skipdfs(*i);
        }
        void compute()
        {
            ready=true;
            dfs(root);
            skipdfs(root);
        }
};

