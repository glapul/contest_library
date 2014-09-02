////////////////////////////////////////////////////////////////////////////////
// Dinic algorithm for unit capacity networks
// Usage:
//
// Create the network using the constructor:
//  UnitCapacityFlowNetwork F = UnitCapacityFlowNetwork([number of vertices],[source],[sink]);
// Remember: Indices are 0-based.
//
// Add edges:
//  F.add_edge(from, to);
//
// And compute the max flow:
// int res = F.compute_max_flow();
//
// You can add some edges after computing the max flow and compute it again - it will work (much) faster than computing it all over again.
// However, you CANNOT add vertices!
//
// This version does not allow to check how the flow looks like!

#include<vector>
#include<algorithm>
#include<queue>
using namespace std;
struct UnitCapacityFlowNetwork
{
    int n, s, t, flow;
    vector<vector<int> > graph;
    vector<int> d;
    vector<int> first_free;

    UnitCapacityFlowNetwork(int n, int s, int t):n(n),s(s),t(t)
    {
        graph = vector<vector<int> >(n);
        flow=0;
    }
    void add_edge(int u, int v)
    {
        graph[u].push_back(v);
    }
    bool bfs()
    {
        int INF = 1000000000;
        d = vector<int>(n,INF);
        d[s]=0;
        queue<int> q;
        q.push(s);
        while(!q.empty())
        {
            int akt = q.front();
            q.pop();
            for(auto i : graph[akt])
                if(d[i]==INF)
                {
                    d[i]=d[akt]+1;
                    q.push(i);
                }
        }
        return d[t]!=INF;
    }
    bool dfs(int v)
    {
        if(v==t)
            return true;
        while(first_free[v]<(int)graph[v].size())
        {
            int next = graph[v][first_free[v]];
            if(d[next]==d[v]+1 && dfs(next))
            {
                swap(graph[v][first_free[v]],graph[v].back());
                graph[v].pop_back();
                graph[next].push_back(v);
                return true;
            }
            else
                first_free[v]++;
        }
        return false;
    }
    int compute_max_flow()
    {
        while(bfs())
        {
            first_free = vector<int>(n);
            while(dfs(s))
                flow++;
        }
        return flow;
    }
};
////////////////////////////////////////////////////////////////////////////////
