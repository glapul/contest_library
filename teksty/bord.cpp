/* Marek Cygan
 * Wyliczanie warto¶ci tablic Bord i StBord
 */

/*ponizsza procedura oblicza wartosci tablicy Bord,
 czyli dlugosci najdluzszych prefikso-sufiksow*/
void licz_Bord(char *x, int n)
{
  int t;
  Bord[0] = t = - 1;
  for (int j = 1; j <= n; ++j)
  {
    while (t >= 0 && x[t]!=x[j-1]) 
      t = Bord[t];
    Bord[j] = ++t;
  } 
}

/* Procedura ta oblicza wartosci tablicy SBord*/
void licz_SBord(char *x, int n)
{
  int t;
  SBord[0] = t = -1;
  for (int j = 1; j <= n; ++j) { //t=Bord[j-1]
    while (t >= 0 && x[t] != x[j])
        t = SBord[t];
    t++;
    SBord[j] = (j == n || x[t] != x[j] ? t : SBord[t]);
  }
}

/*Alternatywna metoda korzystajaca z tablicy PREF*/
void licz_SBord2(char *x, int n)
{
  for (int j = 0; j <= n; ++j) 
    SBord[j] = -1;
  
  for (int j = n; j >= 1; --j)
    SBord[j + PREF[j] - 1] = PREF[j];

  Bord[1]=0; Bord[n] = SBord[n];
  for (int j = n-1; j >= 2; --j)
    Bord[j] = max(Bord[i + 1] - 1, Sbord[i]);
}
