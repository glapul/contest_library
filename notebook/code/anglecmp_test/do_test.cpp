ostream& operator<<(ostream& out, const xy& a) { 
    out << "[" << a.x << "," << a.y << "] ";
    return out;
}

template<typename T>
void assertSorted(const T& cmp, xy* begin, xy* end) {
    for (xy* i = begin; i != end; i++) for (xy* j = begin; j != end; j++) {
        if(cmp(*i, *j) != (i < j)) {
            cout << "fail " << *i;
            cout << cmp(*i, *j) << " " << *j << endl;
            assert(false);
        }
    }
}

void doTest() {
    cout << "Testing with EPS = " << EPS <<endl;
    xy t[100];
    int n = 0;
    t[n++] = xy(1, 0);
    t[n++] = xy(2, 0);
    t[n++] = xy(1, 1);
    t[n++] = xy(2, 2);
    t[n++] = xy(-4, 1);
    t[n++] = xy(-4, 0);
    t[n++] = xy(-5, 0);
    t[n++] = xy(-5, -5);
    t[n++] = xy(0, -5);
    t[n++] = xy(3, -1);
    if (EPS > 0) REP (i, n) t[i] = t[i] * 0.01;
    xy mv(1000, 1000);
    REP (i, n) t[i] = t[i] + mv;
    AngleCmp angleCmp(mv);
    assertSorted(angleCmp, t, t + n);
    for (int i = 0; i < n; i++) {
        cout << "Testing rotation with " << t[0] << endl;
        ShiftedAngleCmp shiftedCmp(mv, t[0]);
        assertSorted(shiftedCmp, t, t + n);
        rotate(t, t + 1, t + n);
    }
}
