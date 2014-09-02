//Dinic algorithm
//Michał Glapa 2013

//USAGE:
//FlowNetwork F = FlowNetwork(n); //where n is the number of vertices
//to add edge F.add_edge(int from, int to, int capacity)
// to get max flow  use F.max_flow()
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
using namespace std;
struct Edge
{
    int to, cross_ref;
    long long f;
    Edge(){}
    Edge(int to, int cross_ref, long long f):to(to),cross_ref(cross_ref),f(f){}
};
class FlowNetwork
{
    private:
        int n, source, sink;
        long long flow;
        static const long long INF = 1000000000000000000LL;
        vector<int> d,pt;
        vector<bool> vis;
        vector<vector<Edge> > graph;
        map<pair<int,int>, int> find_edge;
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
                vector<Edge> & tmp = graph[akt];
                for(int i=0;i<(int)tmp.size();i++)
                {
                    if(tmp[i].f && d[tmp[i].to]==-1)
                    {
                        d[tmp[i].to]=d[akt]+1;
                        q.push(tmp[i].to);
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
            for(;pt[v]<(int)graph[v].size();pt[v]++)
            {
                Edge & nx = graph[v][pt[v]];
                if(d[nx.to]==d[v]+1 && nx.f)
                {
                    int pushed = dfs(nx.to,min(cap,nx.f));
                    nx.f-=pushed;
                    graph[nx.to][nx.cross_ref].f+=pushed;
                    sum+=pushed;
                    cap-=pushed;
                    if(nx.f==0)
                        break;
                }
            }
            return sum;
        }
    public:
        FlowNetwork(int n, int source, int sink): n(n),source(source),sink(sink),flow(0)
        {
            d = pt =  vector<int> (n+1);
            vis = vector<bool> (n+1);
            graph = vector<vector<Edge> > (n+1);
        }
        long long max_flow()
        {
            while(bfs())
                flow+=dfs(source,INF);
            return flow;
        }
        void add_edge(int u, int v, long long f)
        {
            if(find_edge.find(make_pair(u,v))==find_edge.end())
            {
                int us = graph[u].size(),vs = graph[v].size();
                graph[u].push_back(Edge(v,vs,f));
                graph[v].push_back(Edge(u,us,0));
                find_edge[make_pair(u,v)] = us;
                find_edge[make_pair(v,u)] = vs;
            }
            else
            {
                int uu = find_edge[make_pair(u,v)];
                graph[u][uu].f+=f;
            }
        }
};
