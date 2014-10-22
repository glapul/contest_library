// Porzadek katowy na punktach gdzie "root" to punkt wokol ktorego krecimy. Zaczynamy
// od punktow lezacych bezposrednio na prawo od "root", potem idziemy przeciwnie do 
// ruchu wskazowek zegara, najpierw krotsze wektory. Grzegorz Guspiel

// const K EPS = 0; // jezeli K jest typem calkowitoliczbowym

struct AngleCmp {
    xy root;
    AngleCmp(const xy& root_ = xy(0, 0)): root(root_) {}
    void makeSure(const xy& a) const { 
        assert(a.x > EPS || a.x < -EPS || a.y > EPS || a.y < -EPS);
    }
    int hp(const xy& a) const { 
        return a.y < -EPS || (a.y <= EPS && a.x < -EPS);
    }
    bool operator()(xy a, xy b) const {
        a = a - root; makeSure(a);
        b = b - root; makeSure(b);
        int cmpHP = hp(a) - hp(b);
        if (cmpHP) return cmpHP < 0;
        K d = det(a, b);
        if (d > EPS || d < -EPS) return d > 0;
        return a.norm() < b.norm() - EPS;
    }
};

// Przesuniecie cykliczne poprzedniego porzadku gdzie "root" to poczatek a "first" to
// koniec wektora, ktory jest elementem najmniejszym porzadku.

struct ShiftedAngleCmp {
    AngleCmp cmp;
    xy first;
    ShiftedAngleCmp(const xy& root_, const xy& first_): 
        cmp(AngleCmp(root_)), first(first_) {}
    bool operator()(const xy& a, const xy& b) const {
        int cmpFirst = int(cmp(a, first)) - cmp(b, first);
        if (cmpFirst) return cmpFirst < 0;
        return cmp(a, b);
    }
};
