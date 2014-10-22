#include "header.h"
#define debug if(1)

#define show(x) debug cout << #x << ": " << x << endl
#define trace() debug cout << "__trace__ " << __LINE__ << ": " << __func__ << endl
#define dprint(x) debug cout << x << endl
#define ALL(v) (v).begin(),(v).end()
#define dendl() debug cout << endl

template<typename T>
ostream& operator<<(ostream &o, const vector<T>&v){
    o << "[";
    FOREACH(x, v){
        if(x!=v.begin()) o << ", ";
        o << *x;
    }
    o << "]";
    return o;
}

namespace kody {
#include "splay_new.cpp"
};
using namespace kody;

void test1(){
    trace();
    SplayTree<int>T;

    VI orig;
    REP(i,1000000){
        orig.push_back(rand()%1000);
        //orig.push_back(i);
    }

    FOREACH(x, orig){
        T.insert(*x);
    }


    VI v;
    T.dump_inorder(v);

    sort(ALL(orig));
    assert(v==orig); // */

    T.clear();
    assert(T.root == NULL);
}

void test_lower_bound(){
    trace();
    SplayTree<int>T;
    multiset<int>S;

    REP(i,10000000){
        int x = rand()%100000;
        if(rand()%2==0){
            T.insert(x);
            S.insert(x);
        } else {
            int expected = -1;
            {
                multiset<int>::iterator it = S.lower_bound(x);
                if(it != S.end()) expected = *it;
            }

            int received = -1;
            {
                SplayTree<int>::Node *ptr = T.lower_bound(x);
                if(ptr) received = ptr->val;
            }

            assert(expected == received);
        }
    }

    T.clear();
    assert(T.root == NULL);
}

struct Path{
    vector<int>elems;

    int size(){
        return elems.size();
    }

    void reverse(){
        std::reverse(elems.begin(), elems.end());
    }

    Path split_from(int k){
        int nsiz = elems.size();
        Path res;

        for(int i=k; i<(int)elems.size(); i++){
            nsiz--;
            res.elems.push_back(elems[i]);
        }

        elems.resize(nsiz);

        return res;
    }

    void extend(Path &rh){
        FOREACH(x, rh.elems) elems.push_back(*x);
        rh.elems.clear();
    }

    void append(int x){
        elems.push_back(x);
    }

    int sum(){
        int res = 0;
        FOREACH(x, elems) res+= *x;
        return res;
    }

    int kth(int k){
        return elems[k];

        int sum = 0;
        FOREACH(x, elems){
            if(sum + *x > k) return *x;
            sum += *x;
        }
        return -1;
    }

    bool equal(SplayTree<int>&S){
        vector<int>tmp;
        S.dump_inorder(tmp);
        //show(tmp);
        //show(elems);
        return tmp == elems;
    }

    void insert_at(int k, int x){
        //show(k);
        //show(elems.size());
        elems.insert(elems.begin()+k, x);
        //show("OK\n");
    }

};

template<typename T>
T mx(T a, T b){
    if(a>b) return a;
    return b;
}

void test_path(){
    trace();
    SplayTree<int>S;
    Path P;

    REP(i_, 20000){
        int op = rand()%6;
        if(op==0){
            //dprint("APPEND");
            int x = rand()%100;

            P.append(x);
            S.append(x);
        }

        if(op==1){
            //dprint("REV");
            P.reverse();
            S.reverse();
        }

        if(op==2 && P.size()>=1){
            //dprint("KTH");
            int k = rand() % (P.size());
            //show(k);

            int exp = P.kth(k);
            int act = S.splay_kth(k)->val;
            //show(exp);
            //show(act);
            assert(exp == act);
        }

        if(op==3 && P.size()>0){
            //dprint("ROT");
            int k = rand() % P.size();
            //show(k);

            Path P2 = P.split_from(k);
            P2.extend(P);
            P = P2;

            SplayTree<int> S2 = S.split_from(k);

            //vector<int> S2v; S2.dump_inorder(S2v); show(S2v);

            S2.extend(S);
            S.swap(S2);
        }

        if(op==4){
            //dprint("INSERT AT");
            int x = rand()%100;
            int k = rand()%(P.size()+1);
            //show(k);

            P.insert_at(k,x);
            S.insert_at(k,x);
        }

        if(op==5){
            Path new_p;
            SplayTree<int> new_st;

            int siz = rand()%5;
            REP(i,siz){
                int x = rand()%1000;
                new_p.append(x);
                new_st.append(x);
            }

            if(rand()%2){
                S.swap(new_st);
                swap(P,new_p);
            }
            S.extend(new_st);
            P.extend(new_p); //*/
        }

        //dendl();

        assert(P.equal(S));
    }

    S.clear();
    assert(S.root == NULL);
}

struct KTH_TEST{
    LL val,siz;
    KTH_TEST(int v, int s):val(v), siz(s){}
    bool operator == (const KTH_TEST& rh) const {
        return val==rh.val && siz==rh.siz;
    }
};

namespace kody{
    template<>
        node_size_t SplayTree<KTH_TEST>::Node::node_size(){
            return this->val.siz;
        }
}

int randint(int a, int b){
    return a + rand()%(b-a+1);
}

void insert_at(vector<KTH_TEST>&v, LL k, KTH_TEST nw){
    bool inserted = false;

    vector<KTH_TEST> tmp;
    tmp.swap(v);

    LL sum = 0;
    FOREACH(x ,tmp){
        if(!inserted && sum + x->siz > k){
            v.push_back(nw);
            inserted = true;
        }
        v.push_back(*x);
        sum += x->siz;
    }
    if(!inserted){
        v.push_back(nw);
    }
}

ostream& operator << (ostream &o, const KTH_TEST& rh){
    o << "KTH(" << rh.siz << ", " << rh.val << ")";
    return o;
}

LL randLL(){
    LL res = rand();
    res <<= 32;
    res |= rand();
    assert(res>=0);
    return res;
}

void test_kth(LL max_siz){
    trace();
    show(max_siz);

    SplayTree<KTH_TEST>S;
    LL sum = 0;

    vector<KTH_TEST>v;
    REP(i,30000){
        int val = randLL()%10000;
        LL siz = randLL()%max_siz;
        assert(siz>=0);

        KTH_TEST nw(val,siz);
        LL k = randLL()%(sum+1000);

        insert_at(v, k, nw);
        S.insert_at(k, nw);

        sum+=siz;

    }
    assert(sum > 0);

    REP(i_, 2*v.size()){
    //REP(i_,sum+10){
        LL which = randLL()%sum;
        assert(which>=0 && which<sum);
        //LL which = i_;

        unsigned i = 0;
        LL act_sum = 0;
        while(i < v.size() && act_sum+v[i].siz <= which){act_sum += v[i].siz; i++;}

        SplayTree<KTH_TEST>::Node* ptr = S.splay_kth(which);
        if(ptr==NULL) {
            assert(i==v.size());
        } else {
            KTH_TEST res = ptr->val;
            assert(res == v[i]);
        }
    }
}

int main(){
    srand(time(0));
    REP(i,10){
        test_kth(100000000000014);
        test_kth(3);
        test_path();
        test1();
        test_lower_bound();
    }
}
