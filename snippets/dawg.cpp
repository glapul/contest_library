namespace DAWG {
// ======== DAWG by Igor Adamski ========
// Usage:
// root = last = new node();
// add(c)...
// root reprezentuje slowo puste, trzeba recznie dbac o wszystkie node’y
// jesli sie chce zarzadzac pamiecia

const int A = 26; // rozmiar alfabetu

struct node {
  node *next[A], *suf;
  int len; // dlugosc najdluzszego slowa konczacego sie tutaj
  node(int _len=0, node *_suf=nullptr, node **_next=nullptr) : suf(_suf), len(_len) {
    if (!_next) for (int i = 0; i < A; i++) next[i] = nullptr;
    else for (int i = 0; i < A; i++) next[i] = _next[i];
  }
};
node *root, *last;
void add(int c) { // dodaje znak na koniec slowa
  node *p = last, *np = new node(last->len+1);
  for(;p && !p->next[c];p=p->suf) p->next[c] = np;
  if(!p) np->suf = root;
  else {
    node *q = p->next[c];
    if(p->len+1 == q->len) np->suf = q;
    else {
      node *nq = new node(p->len+1, q->suf, q->next);
      q->suf = np->suf = nq;
      for(;p && p->next[c] == q;p=p->suf) p->next[c] = nq;
    }
  }
  last = np;
}

}
