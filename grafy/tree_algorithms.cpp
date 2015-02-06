#include<bits/stdc++.h>
using namespace std;

class fenwick_tree {
    vector<int> tp;
    public:
    fenwick_tree(int n = 0) {
        tp = vector<int>(n+1);
    }
    void add(int x, int v) {
        for(;x < tp.size(); x+=x&-x)
            tp[x] += v;
    }
    int sum_prefix(int x) {
        int res = 0;
        for(;x > 0; x-=x&-x)
            res +=tp[x];
        return res;
    }
    int sum_interval(pair<int,int> range) {
        return sum_prefix(range.second) - sum_prefix(range.first - 1);
    }
};
typedef int _EDGE_COST;
class tree_node;
class tree_edge {
    public:
    int to;
    _EDGE_COST cost;
    tree_edge(){}
    tree_edge(int to, _EDGE_COST cost = 1)
        : to(to), cost(cost){}
};
class tree_node {
    public:
    int parent;
    int name;
    int depth, subtree_size, preorder_time, postorder_time;
    _EDGE_COST dist_from_root;
    vector<tree_edge> edges;
    tree_node():parent(-1), depth(-1), subtree_size(-1), preorder_time(-1), postorder_time(-1), dist_from_root(-1) {}
    tree_node(int name, int parent = -1)
        :parent(parent), name(name), depth(-1), subtree_size(-1), preorder_time(-1), postorder_time(-1), dist_from_root(-1){}
};
//zalozenia : wierzcholki to liczby od 0 do n-1, nie ma multikrawedzi. Krawedzie mozna podac albo jako skierowane, albo jako nieskierowane
class tree {
    public:
    int tree_size;
    vector<tree_node> nodes;
    int root;
    fenwick_tree F;

    tree():tree_size(0), root(-1){}

    tree(int n):tree_size(n), nodes(vector<tree_node>(n)), root(-1){}

    void insert_undirected_edge(int a, int b, _EDGE_COST cost = 1) {
        nodes[a].edges.push_back(tree_edge(b, cost));
        nodes[b].edges.push_back(tree_edge(a, cost));
    }
    void insert_directed_edge(int from, int to, _EDGE_COST cost = 1) {
        nodes[from].edges.push_back(tree_edge(to, cost));
        assert(nodes[from].parent == -1);
        nodes[to].parent = from;
    }
    void set_root(int rt){
        root = rt;
        nodes[root].depth = 0;
    }
    void prepare() {
        int t1 = 1, t2 = 1;
        assert("You must set root!" && root != -1);
        initial_dfs(root, -1, t1, t2);
    }
    void initial_dfs(int v, int p, int & preorder_timer, int & postortder_timer) {
        auto & V = nodes[v];
        V.preorder_time = preorder_timer++;
        V.subtree_size = 1;
        for(auto i : V.edges)
            if(i.to != p) {
                auto & son = nodes[i.to];
                son.depth = V.depth + 1;
                son.dist_from_root = V.dist_from_root + i.cost;

                initial_dfs(i.to, v, preorder_timer, postortder_timer);

                V.subtree_size += son.subtree_size;
            }
        V.postorder_time = postortder_timer++;
    }
    inline pair<int,int> interval_structure_subtree_range(int rt) {
        return make_pair(nodes[rt].preorder_time, nodes[rt].preorder_time + nodes[rt].subtree_size - 1);
    }
    void initialize_fenwick() {
        F = fenwick_tree(tree_size);
    }
    void fenwick_add_at_vertex(int v, int val = 1) {
        F.add(interval_structure_subtree_range(v).first, val);
    }
    int fenwick_query_subtree(int v) {
        return F.sum_interval(interval_structure_subtree_range(v));
    }
    int find_any_leaf() {
        for(int i = 0; i < tree_size; i++)
            if(nodes[i].edges.size() == 1)
                return i;
    }
    int find_any_non_leaf() {
        for(int i = 0; i < tree_size;i++)
            if(nodes[i].edges.size() != 1)
                return i;
        throw("Every node is a leaf.");
    }
    bool is_ancestor(int anc, int desc) {
        return nodes[anc].preorder_time <= nodes[desc].preorder_time && nodes[desc].postorder_time <= nodes[anc].postorder_time;
    }
};
