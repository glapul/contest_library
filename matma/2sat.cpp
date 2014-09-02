#include<vector>
#include<cstdlib>
#include<algorithm>
using namespace std;
/* Class containing the graph, and doing stuff */
class Two_SAT
{
    public:
        int neg(int x) // negation of a variable
        {
            if(x>=n)
                return x-n;
            return x+n;
        }
        void add_alt(int a, int b) // adds an alternative. For example C.add_alt(1,2) or C.add_alt(C.neg(1),2);
        {
            graph[neg(a)].push_back(b);
            graph[neg(b)].push_back(a);
        }
        void add_edge(int a, int b) // adds implication a=>b
        {
            graph[a].push_back(b);
        }
        Two_SAT(int n):n(n) // n is the number of variables, last variable is variable n-1
        {
            srand(1337);
            graph = vector<vector<int> > (2*n);
            vis = vector<bool> (2*n);
            fail=false;
        }
        bool solve() //returns true if there exists a labeling and false otherwise
        {
            vis = vector<bool> (2*n);
            vector<int> order = vector<int> (2*n);
            for(int i=0;i<2*n;i++)
                order[i]=i;
            random_shuffle(order.begin(),order.end());
            for(vector<int>::iterator i = order.begin();i!=order.end();i++)
            {
                if(vis[*i]||vis[neg(*i)])
                    continue;
                changes.clear();
                dfs(*i);
                if(fail)
                {
                    for(int j=0;j<(int)changes.size();j++)
                        vis[changes[j]]=false;
                    fail=false;
                    changes.clear();
                    dfs(neg(*i));
                    if(fail)
                        break;
                }

            }
            return !fail;
        }
        bool get_variable(int x) // true if x is true, false otherwise
        {
            return vis[x];
        }
    private:
        int n;
        bool fail;
        vector<vector<int> > graph;
        vector<bool> vis;
        vector<int> changes;
        void dfs(int v)
        {
            changes.push_back(v);
            vis[v]=true;
            if(vis[neg(v)])
                fail=true;
            for(vector<int>::iterator i=graph[v].begin();i!=graph[v].end();i++)
                if(!vis[*i])
                    dfs(*i);

        }
};
