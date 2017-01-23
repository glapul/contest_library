struct SCC
{
    int n, scc_count=0, time=0;
    vector<vector<int> > graph;
    const int NIL = -1;
    vector<int> in, low, scc;
    vector<bool> stacked;
    stack<int> s;
    SCC(int n):n(n)
    {
        graph = vector<vector<int>>(n);
        in = low =scc =vector<int>(n,NIL);
        stacked = vector<bool>(n);
    }
    void dfs(int v)
    {
        low[v] = in[v] = time++;
        s.push(v);
        stacked[v] = true;
        for(auto i : graph[v])
        {
            if(in[i]==NIL)
            {
                dfs(i);
                low[v] = min(low[v], low[i]);
            }
            else if (stacked[i])
                low[v] = min(low[v], low[i]);
        }
        if(low[v]==in[v])
        {
            while(true)
            {
                int i = s.top();
                s.pop();
                stacked[i] = false;
                scc[i] = scc_count;
                if(i == v)
                    break;
            }
            scc_count++;
        }
    }
    void compute()
    {
        for(int i=0;i<n;i++)
            if(scc[i]==NIL)
                dfs(i);
    }
    void add_edge(int from, int to)
    {
        graph[from].push_back(to);
    }
    vector<vector<int> > get_sccs()
    {
        vector<vector<int> > res(scc_count);
        for(int i = 0 ; i<n;i++)
            res[scc[i]].push_back(i);
        return res;
    }
    int get_scc(int v)
    {
        return scc[v];
    }
};

