namespace RMQ {

  typedef int T; // zmienić
  const int _LOG = 20;
  int LOG = 20;
  inline T compose (const T& a, const T& b) {
    return a < b ? a : b;
  }
  T NEUTRAL = 1<<30;


  T dbf[_LOG][1<<_LOG];
  void init(int n) {
    for (int i = 1, LOG = 0; i < 2 * n; LOG++, i<<=1);

    for (int i = 0; i < (1 << LOG); i++)
      for (int j = 0; j < LOG; j++)
      dbf[j][i] = NEUTRAL;
  }
  void build() {
    for (int l = 1; l < LOG; l++) {
      int pl = 1 << (l - 1);
      for (int j = 0; j < (1 << LOG); j++)
        dbf[l][j] = compose(dbf[l - 1][j], (j + pl < (1<<LOG)) ? dbf[l - 1][ j + pl] : NEUTRAL);
    }
  }

  inline int getlvl(int len) {
    int lvl = 63 - __builtin_clzll(len);
    return lvl;
  }

  T query(int pos, int len) {
    int lvl = getlvl(len);
    //cerr << pos << " " << len << " " << lvl << endl;
    T a = dbf[lvl][pos];
    int pos2 = pos + len - (1<<lvl);
    T b = (pos2 < (1<<LOG)) ? dbf[lvl][pos2] : NEUTRAL;
    return compose(a, b);
  }

}
