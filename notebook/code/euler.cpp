// CYKL EULERA w grafie eulerowskim O(V+E)

const int MAXN = 1100000, MAXM = 11000000; // max liczba wierzcholkow i krawedzi

struct edge {
    int v;
    int back_idx; //TYLKO DLA NIESKIEROWANYCH
    
    bool vis;     //TYLKO DLA NIESKIEROWANYCH
    edge(int vi):v(vi){
        vis = false; //TYLKO DLA NIESKIEROWANYCH
    }
};

int n;                // IN: liczba wierzcholkow
vector<edge> adj[MAXN]; // IN: lista sasiedztwa (dla skierowanych: do przodu)
int cc;               // OUT: dlugosc cyklu Eulera
edge *cycle[MAXM];    // OUT: kolejne krawedzie na cyklu Eulera
int cur[MAXN];

stack<edge*>e_stack_;

// aby znalezc sciezke Eulera: dodaj krawedz miedzy
// wierzcholkami o nieparzystym stopniu, znajdz cykl i
// potem usun ta krawedz
void search(int v) {
    while(true){
        if(cur[v] == adj[v].size()) {
            if (!e_stack_.empty()) {
                cycle[cc++] = e_stack_.top();
                e_stack_.pop();
            }
        } else {
            edge *e = &adj[v][cur[v]++];
            if (!e->vis) {                          //TYLKO DLA NIESKIEROWANYCH
                adj[e->v][e->back_idx].vis = true;  //TYLKO DLA NIESKIEROWANYCH
                e_stack_.push(e);                   //TO ZOSTAJE ZAWSZE
            }                                       //TYLKO DLA NIESKIEROWANYCH
        }
        if (e_stack_.empty()) break;
        v = e_stack_.top()->v;
    }
}

void compute_cycle() {
    REP(v,n) cur[v] = 0;
    cc = 0;
    REP(v,n) search(v);
}

void add_edge(int a, int b){
    adj[a].push_back(edge(b));
    adj[b].push_back(edge(a));                   //TYLKO DLA NIESKIEROWANYCH
    adj[a].back().back_idx = adj[b].size()-1;    //TYLKO DLA NIESKIEROWANYCH
    adj[b].back().back_idx = adj[a].size()-1;    //TYLKO DLA NIESKIEROWANYCH
}
