typedef LL node_size_t; //suma wszystkich node_size() powinna sie miescic!

template<typename T>
struct SplayTree {
#define _subtree_size(x) ((x)?(x)->subtree : 0)
    struct Node{
        T val;

        Node* left_, *right_, *p_; //tych (i dalszych) pol nie dotykac bezposrednio
        Node(const T& v):
                val(v), left_(NULL), right_(NULL), p_(NULL), everted_(false){
            resize();
        }
        void set_left(Node *x){
            push();     /* EVERT */
            left_ = x; if(x) x->p_ = this; resize(); }
        void set_right(Node *x){
            push();     /* EVERT */
            right_ = x; if(x) x->p_ = this; resize();}

        //template<> node_size_t SplayTree<KTH_TEST>::Node::node_size(){ ... }
        node_size_t node_size(){return 1;}
        node_size_t subtree;

        void resize(){
            subtree = _subtree_size(left_) + _subtree_size(right_) + node_size();
        }

        bool everted_;                             /* EVERT */
        void evert() { everted_ = !everted_; }     /* EVERT */
        void push() {                              /* EVERT */
            if (everted_) {                        /* EVERT */
                if (left_) left_->evert();         /* EVERT */
                if (right_) right_->evert();       /* EVERT */
                std::swap(left_, right_);          /* EVERT */
                everted_ = false;                  /* EVERT */
            }                                      /* EVERT */
        }                                          /* EVERT */

        void rotate() {
            Node *parent = p_;
            this->p_ = parent->p_;
            if(parent->p_) {
                if (parent==parent->p_->left_) parent->p_->set_left(this);
                else parent->p_->set_right(this);
            }

            if (this==parent->left_) {
                parent->set_left(this->right_);
                set_right(parent);
            } else {
                parent->set_right(this->left_);
                set_left(parent);
            }
        }

        void dump_inorder_(vector<T>&out){              /* DUMP */
            push();                                     /* DUMP, EVERT */
            if(left_) left_->dump_inorder_(out);        /* DUMP */
            out.push_back(val);                         /* DUMP */
            if(right_) right_->dump_inorder_(out);      /* DUMP */
        }                                               /* DUMP */

        void clear_(){                                      /* CLEAR */
            if(left_) {left_->clear_(); delete left_;}      /* CLEAR */
            if(right_) {right_->clear_(); delete right_;}   /* CLEAR */
        }                                                   /* CLEAR */
    } *root;

    void dump_inorder(vector<T>&out){           /* DUMP */
        if(root) root->dump_inorder_(out);      /* DUMP */
    }                                           /* DUMP */

    SplayTree():root(NULL){}
    //UWAGA - piszac deepcopy pamietaj o pushowaniu
    SplayTree(const SplayTree<T>& rh); //XXX - konstruktor bez definicji!
    void operator = (const SplayTree<T>& rh); //XXX - j.w.
    ~SplayTree(){ clear(); }    /* CLEAR */
    void swap(SplayTree<T>& rh){ std::swap(root, rh.root); } /* SWAP */

    void clear(){           /* CLEAR */
        if(!root) return;   /* CLEAR */
        root->clear_();     /* CLEAR */
        delete root;        /* CLEAR */
        root = NULL;        /* CLEAR */
    }

    Node* splay(Node *v) { //uwaga, zmienia korzen drzewa
        while(v->p_) {
            if (v->p_->p_) v->p_->p_->push();       /* EVERT */
            v->p_->push();                          /* EVERT */
            v->push();                              /* EVERT */
            if (v->p_->p_ && ((v==v->p_->left_) == (v->p_==v->p_->p_->left_)))
                v->p_->rotate();
            v->rotate();
        }
        return root = v;
    }

    /* MULTISET */

    Node* lower_bound(const T &x){ //zmienia korzen, NIEKONIECZNIE na wynik!
        Node *v = root, *res = NULL, *prev = NULL;
        while(v){
            prev = v;
            if(v->val < x) v = v->right_;
            else {
                res = v;
                v = v->left_;
            }
        }
        if(prev) splay(prev); //XXX czy na pewno tak chcemy ?
        return res;
    }

    Node* insert(const T& x){
        Node *v = new Node(x);
        while(root){
            if(x < root->val){
                if(root->left_) root = root->left_;
                else { root->set_left(v); break; }
            } else {
                if(root->right_) root = root->right_;
                else { root->set_right(v); break; }
            }
        }
        return splay(v);
    };

    /* PATH */

    // Pierwszy wierzcholek taki ze suma rozmiarow wierzcholkow w porzadku
    // inorder do tego wierzcholka wlacznie jest > k. Jesli rozmiary sa = 1,
    // to jest to k-ty wierzcholek w porzadku inorder. (Liczac od 0)
    Node *splay_kth(node_size_t k){
        Node *v = root;
        if (_subtree_size(v) <= k) return NULL;
        for(;;) {
            if(!v) return NULL;
            v->push();      /* EVERT */
            if (_subtree_size(v->left_) <= k &&
                    _subtree_size(v->left_) + v->node_size()>k){
                return splay(v);
            }
            if (_subtree_size(v->left_) <= k) {
                k -= (v->node_size()+_subtree_size(v->left_));
                v = v->right_;
            } else v = v->left_;
        }
    }

    void reverse(){ if(root) root->evert(); }

    void append_(Node* nw){
        if(!nw) return;
        Node *v = root;
        while(v){
            v->push();  /* EVERT */
            if(v->right_) v = v->right_;
            else break;
        }

        if(v) v->set_right(nw);
        splay(nw);
    }

    void append(const T& val){ append_(new Node(val)); }

    void insert_at(node_size_t k, const T& val){ //val bedzie na ktej pozycji
        // (od zera). UWAGA - Jesli k jest duze, to val bedzie appendowane.
        // Jesli rozmiary wezlow nie sa jednostkowe, to val zostanie wsadzone
        // na najdalsza pozycje taka, ze suma elementow przed nia jest <= k
        if(!root){
            append(val);
            return;
        }
        SplayTree st = split_from(k);
        append(val);
        extend(st);
    }

    SplayTree split_from(node_size_t k){ //odrywa podsciezke o ind. [k, k+1, ...]
        SplayTree res;
        if(!splay_kth(k)) return res;

        Node *left_ = root->left_;
        root->set_left(NULL);
        root->resize();
        if(left_) left_->p_ = NULL;

        res.root = root;
        root = left_;

        return res;
    }

    void extend(SplayTree<T> &rh){ //wchlania sciezke rh (dokleja na koniec)
        assert(this != &rh);
        if(!rh.root) return;
        if(!root) root = rh.root;
        else append_(rh.root);
        rh.root = NULL;
    }
};
