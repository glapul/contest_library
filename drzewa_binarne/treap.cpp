#include<cstdio>
#include<vector>
#include<cstdlib>
#include<algorithm>
using namespace std;

struct node
{
    int val, weight,sz;
    node *left, * right;
    node(){}
    node(int val):val(val)
    {
        weight = rand();
        sz=0;
    }
};
void update(node * u)
{
    if(u==NULL)
        return;
    u->sz = (u->left!=NULL ? u->left->sz : 0) + (u->right !=NULL ? u->right->sz : 0);
    //here place custom updates
}

node  * merge(node *u, node*v)
{
    if(u==NULL)
        return v;
    if(v==NULL)
        return u;
    if(u->weight > v->weight)
    {
        u->right = merge(u->right,v);
        update(u);
        return u;
    }
    else
    {
        v->left = merge(u,v->left);
        update(v);
        return v;
    }
}

pair<node*,node*> split_after(node *u, int val)
{
    if(u==NULL)
        return make_pair((node*) NULL,(node*) NULL);
    if(u->val < val)
    {
        pair<node*,node*> t = split_after(u->right,val);
        u->right = t.first;
        update(u);
        update(t.second);
        return make_pair(u,t.second);
    }
    else
    {
        pair<node*,node*> t = split_after(u->left,val);
        u->left = t.second;
        update(t.first);
        update(u);
        return make_pair(t.first,u);
    }

}

node * insert(node * root, int val) //returns new root
{
    if(root==NULL)
        return new node(val);
    auto tmp = split_after(root,val);
    auto x = merge(tmp.first,new node(val));
    return merge(x,tmp.second);
}
void insert_wrapper(node* & root, int val)
{
    root = insert(root,val);

}
node * find(node * v, int val)
{
    if(v==NULL)
        return NULL;
    if(v->val==val)
        return v;
    if(v->val > val)
        return find(v->left,val);
    return find(v->right,val);
}
void print(node * v)
{
    if(v==NULL)
        return;
    print(v->left);
    printf("%d ", v->val);
    print(v->right);
}
node * find_kth(node * u, int k)
{
    if(u==NULL)
        return NULL;
    int lsz = u->left!=NULL ? u->left->sz : 0;
    if(k <lsz)
        return find_kth(u->left,k);
    if(k==lsz)
        return u;
    return find_kth(u->right,k-lsz-1);
}

int main()
{
    node * root =NULL;
    int v;
    while(scanf("%d",&v))
    {
        insert_wrapper(root,v);
        print(root);
    }
}



