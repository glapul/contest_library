#include<cstdio>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
template<typename T>
struct node
{
    T val;
    node* s[2];
    node* p;
    int sz;
    node(T val):val(val)
    {
        s[0]=s[1]=p=NULL;
        sz=1;
    }
    void update()
    {
        sz=1+(s[0]!=NULL ? s[0]->sz : 0) + (s[1]!=NULL ? s[1]->sz : 0);
    }
    int direction()
    {
        if(p==NULL)
            return -1;
        return p->s[0]==this ?  0 : 1;
    }
    bool isroot()
    {
        return p==NULL;
    }
    void attach(node *son, int dir)
    {
        s[dir]=son;
        if(son!=NULL)
            son->p=this;
        update();
    }
    void rotate()
    {
        if(isroot())
            return;
        node *g = p->p;
        int dir = direction(), gdir = p->direction();
        p->attach(s[1-dir],dir);
        attach(p,1-dir);
        if(g!=NULL)
            g->attach(this, gdir);
        else
            p=NULL;
    }
    node* splay() // returns this - new root;
    {
        while(!isroot())
        {
            if(p->isroot()) rotate();
            else
            {
                if(direction() == p->direction()) p->rotate();
                else rotate();
                rotate();
            }
        }
        return this;
    }
    ~node()
    {
        delete s[0];
        delete s[1];
    }
};
template<typename T>
struct Splay
{
    Splay() {
        root=NULL;
    }
    Splay(node<T>* rt):root(rt) {
        if(root!=NULL)
            root->p=NULL;
    }
    node<T>* root;
    node<T>* find_no_splay(T v)
    {
        node<T> *akt= root,
        *prev=NULL;
        while(true)
        {
            if(akt==NULL)
                return prev;
            prev=akt;
            if(akt->val==v)
                return akt;
            akt = akt->val > v ? akt->s[0] : akt->s[1];
        }
        return akt;
    }
    node<T>* find(T v)
    {
        node<T> * akt = find_no_splay(v);
        root=akt->splay();
        return akt->val == v ? akt : NULL;
    }
    node<T>* get(int k)
    {
        node<T>* akt=root;
        while(true)
        {
            if(akt==NULL)
                throw("Get : Index too big\n");
            if(akt->s[0]!=NULL)
            {
                if(akt->s[0]->sz > k)
                {
                    akt=akt->s[0];continue;
                }
                else
                    k-=akt->s[0]->sz;
            }
            if(k==0)
                break;
            else
            {
                k--;
                akt=akt->s[1];
            }
        }
        root=akt->splay();
        return akt;
    }
    void insert_node(node<T> * nnew)
    {
        if(root==NULL)
        {
            root=nnew;
            return;
        }
        node<T> * wh = find_no_splay(nnew->val);
        wh->attach(nnew, nnew->val<wh->val ? 0 :1);
        root=nnew->splay();
    }
    void splay_dir(int dir)
    {
        get(dir ==1 ? root->sz-1 : 0);
    }
    Splay cutoff_dir(int dir)
    {
        Splay r = Splay(root->s[dir]);
        root->attach(NULL,dir);
        return r;
    }
    void extend(Splay & other)
    {
        splay_dir(1);
        root->attach(other.root,1);
        other.root=NULL;
    }
    void remove_node(node<T> *v)
    {
        root=v->splay();
        Splay rt = cutoff_dir(1);
        pop_dir(1);
        extend(rt);
    }
    void push_dir_node(node<T> * v, int dir)
    {
        if(root==NULL)
        {
            root=v;
            return;
        }
        splay_dir(dir);
        root->attach(v,dir);
    }
    void pop_dir(int dir)
    {
        splay_dir(dir);
        node<T>* del = root;
        root=root->s[1-dir];
        root->p=NULL;
        delete del;
    }
    void insert(T v)
    {
        node<T> * tmp = new node <T>(v);
        insert_node(tmp);
    }
    void remove(T v)
    {
        node<T> * akt= find_no_splay(v);
        if(akt->val !=v)
            throw("Remove failed : no element\n");
        remove_node(akt);
    }
    int less_than(T v)
    {
        find(v);
        return root->s[0]!=NULL ? root->s[0]->sz : 0;
    }
    void insert_node_at_position(node<T> * v,int pos)
    {
        if(pos==0)
        {
            Splay tmp;
            tmp.insert_node(v);
            tmp.extend(*this);
            root=tmp.root;
            tmp.root=NULL;
        }
        else
        {
            get(pos-1);
            Splay rt = cutoff_dir(1);
            Splay tmp;
            tmp.insert_node(v);
            extend(tmp);
            extend(rt);
        }
    }
    void insert_at_position(T v, int pos)
    {
        node<T>* tmp = new node<T>(v);
        insert_node_at_position(tmp,pos);
    }
    ~Splay()
    {
        delete root;
    }
};
/*
template<typename T >
void show(node<T> * akt, FILE * f )
{
    if(akt==NULL)return;
    for(int i=0;i<2;i++)
        if(akt->s[i]!=NULL)
        {
            fprintf(f,"%d -> %d;\n",akt->val,akt->s[i]->val);
            show(akt->s[i],f);
        }
        else
            fprintf(f,"%d -> NULL%d;\n",akt->val,akt->val);
    fprintf(f,"%d [label=\" %d %d \"]\n",akt->val,akt->val,akt->sz);
}
int timer=0;
template<typename T>
void save(node<int>* rt)
{
    char s [20];
    sprintf(s,"vis%d",timer++);
    FILE *f = fopen(s,"w");
    fprintf(f,"digraph G {\n");
    show(rt,f);
    fprintf(f,"}\n");
    fclose(f);
}*/
