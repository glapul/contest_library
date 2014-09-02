/////////////////////////////////////////////////////////////////////////////////
// Ford-Fulkerson max flow algorithm for unit-capacity networks
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
    vector<bool> vis;
    UnitCapacityFlowNetwork(int n, int s, int t):n(n),s(s),t(t)
    {
        graph = vector<vector<int> >(n);
        flow=0;
    }
    void add_edge(int u, int v)
    {
        graph[u].push_back(v);
    }
    bool dfs(int v)
    {
        if(v==t)
            return true;
        vis[v]=true;
        int i =0;
        while(i<(int) graph[v].size())
        {
            int next = graph[v][i];
            if(!vis[next] && dfs(next))
            {
                swap(graph[v][i],graph[v].back());
                graph[v].pop_back();
                graph[next].push_back(v);
                return true;
            }
            else
                i++;
        }
        return false;
    }
    int compute_max_flow()
    {
        vis = vector<bool>(n,false);
        while(dfs(s))
        {
            vis = vector<bool>(n,false);
            flow++;
        }
        return flow;
    }
};
/////////////////////////////////////////////////////////////////////////////////
