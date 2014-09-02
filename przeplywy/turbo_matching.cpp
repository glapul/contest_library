//Maximum matching in bipartite graphs
//Warning : this code DOES NOT check if the graph given is bipartite!
//Complexity : very fast, usually works as fast as O(ElogE)
//Copyright Michał Glapa 2013
//USAGE
// first create an instance : MatchingGraph g = MatchingGraph(n); where n is number of verices
// then add edges : g.add_edge(u,v);
//  to get max matching g.max_matching();
//  you can check who is matched to vertex i by g.match[i]; (-1 if unmatched)
#include<vector>
using namespace std;
class MatchingGraph
{
    private:
        int n,res;
        vector<vector<int> > graph;
        vector<bool> vis;
        bool dfs(int v)
        {
            vis[v]=true;
            for(int i=0;i<(int)graph[v].size();i++)
            {
                int nx = graph[v][i];
                if(match[nx]==-1 || (!vis[match[nx]] && dfs(match[nx])))
                {
                    match[v]=nx;
                    match[nx]=v;
                    return true;
                }
            }
            return false;
        }
        bool matching()
        {
            for(int i=0;i<n;i++)
                vis[i]=false;
            bool changed=false;
            for(int i=0;i<n;i++)
                if(match[i]==-1 && !vis[i] && dfs(i))
                {
                    res++;
                    changed=true;
                }
            return changed;
        }
    public:
        vector<int> match;
        MatchingGraph(int n) : n(n),res(0)
        {
            vis = vector<bool>(n);
            match = vector<int>(n);
            graph=vector<vector<int> > (n);
            for(int i=0;i<n;i++)
                match[i]=-1;
        }
        void add_edge(int u, int v)
        {
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        int max_matching()
        {
            while(matching());
            return res;
        }
};
