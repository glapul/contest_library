// AUTOMAT SKONCZONY dla wielu wzorcow O(n SIGMA)
// Bartosz Walczak

const int SIGMA = 2;    // licznosc alfabetu
const int MAXBUF = 100; // maksymalna liczba wezlow + 1

inline int alpha(char c) { return c-'0'; } // numer znaku w alfabecie

// Algorytm zwraca nastepujaca strukture
struct node {
    node *prefix, *next[SIGMA]; // funkcja prefiksowa, funkcja przejsc
    const char *end;            // wzorzec, ktorego koncem jest dany stan
    node *accept;               // nastepnik na liscie stanow akceptujacych
/* Uwaga: Tablice next mozna zmienic na mape. Wtedy potrzebna jest funkcja:
    node *get_next(int a) {
        node *v = this;
        while (!v->next.count(a)) v = v->prefix;
        return v->next[a];
    }                                                                         */
    node *get_accept() { return end ? this : accept; }
    void evaluate(int a, queue<node*> &Q) { // mapa: zmienic funkcje tak, aby
        if (next[a]) {        // przyjmowala iterator, i wpisac tylko tresc ifa
            next[a]->prefix = prefix->next[a]; // mapa: prefix->get_next(i->FI)
            next[a]->accept = next[a]->prefix->get_accept();
            Q.push(next[a]);
        }
        else next[a] = prefix->next[a]; // mapa: pominac
    }
};

node buf[MAXBUF]; // mapa: po zakonczeniu wyczyscic wszystkie nexty
int bufc;         // przed konstrukcja automatu wyzerowac!

node *get_node() { // pobiera nowy wezel z bufora
  FOR(a,0,SIGMA) buf[bufc].next[a] = 0; // mapa: pominac
  buf[bufc].end = 0;
  buf[bufc].accept = 0;
  return buf+bufc++;
}

// Dodawanie wzorca do struktury automatu
void add_str(node *root, const char *str) { // na poczatku root = get_node()
    for (int i=0; str[i]; ++i) {
        int a = alpha(str[i]);
        if (!root->next[a]) root->next[a] = get_node(); // mapa: zmienic warunek
        root = root->next[a];                         // na !root->next.count(a)
    }
    root->end = str;
}

// Obliczenie funkcji prefiksowej i przejsc po dodaniu wszystkich wzorcow
void evaluate(node *root) {
    root->prefix = get_node();
    FOR(a,0,SIGMA) root->prefix->next[a] = root;
    queue<node*> Q; Q.push(root);
    while (!Q.empty()) {
        node *cur = Q.front(); Q.pop();
        FOR(a,0,SIGMA) cur->evaluate(a, Q); // mapa: FORE(i,cur->next)
    }                                       //         cur->evaluate(i, Q);
}

// Generowanie listy wzorcow akceptowanych w stanie v
for (node *u=v; u; u=u->accept) if (u->end) { /*znaleziono wzorzec u->end*/ }
