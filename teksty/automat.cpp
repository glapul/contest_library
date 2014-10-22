/* Jakub Radoszewski
 * Minimalizacja automatu skoñczonego nad alfabetem unarnym
 * Z³o¿ono¶æ czasowa i pamiêciowa: O(n).
 * 
 * U¿ycie:
 * liczba_stanów_automatu stan_pocz±tkowy
 * przej¶cia (na co siê przechodzi ze stanu i-tego)
 * typy_stanów (1-akceptuj±cy, 0-nieakceptuj±cy).
 *
 * Wynik:
 * Dla ka¿dego stanu jego numer; te same numery oznaczaj± równowa¿ne stany.
 * Numer 0 oznacza stan, który nie jest osi±galny ze stanu pocz±tkowego.
 */

#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

#define MAX_N 1000000

/* Stany automatu maj± numery 0..n-1. */
int t[MAX_N]; /* tablica przej¶æ */
bool stany[MAX_N]; /* typy stanów */
int spocz; /* stan pocz±tkowy */
int n; /* liczba stanów automatu */

int wynik[MAX_N]; /* numery stanów (te same numery to stany równowa¿ne) */

int pierw; /* d³ugo¶æ pierwiastka pierwotnego s³owa na cyklu */
int pocz; /* pocz±tek cyklu */
vector<int> cykl; /* 1-akceptuj±cy, 0-nieakceptuj±cy */
int pref_suf[MAX_N]; /* warto¶ci funkcji prefiksowej */
int col[MAX_N]; /* tablica pomocnicza */

void odczyt()
{
  scanf("%d%d", &n, &spocz);
  for (int i = 0; i < n; i++)
    scanf("%d", &t[i]);
  for (int i = 0; i < n; i++)
    scanf("%d", &stany[i]);
}


/* Funkcja zwraca pocz±tek cyklu w automacie i wylicza vector cykl,
 * czyli s³owo binarne skonstruowane ze stanów cyklu. */
int poczatek_cyklu()
{
  memset(col, 0, sizeof(col));
  int poz = spocz;
  while (!col[poz])
  {
    col[poz] = 1;
    poz = t[poz];
  }
  cykl.push_back(0);
  while (col[poz] < 2)
  {
    col[poz] = 2;
    cykl.push_back(stany[poz]);
    poz = t[poz];
  }
  return poz;
}



/* Funkcja liczy funkcjê prefiksow± s³owa z cyklu i zwraca jej warto¶æ
 * na ca³ym s³owie. */
int funkcja_prefiksowa()
{
  pref_suf[0] = pref_suf[1] = 0;
  int k = 0;
  for (int q = 2; q < cykl.size(); q++)
  {
    while (k > 0 && cykl[k + 1] != cykl[q])
      k = pref_suf[k];
    if (cykl[k + 1] == cykl[q])
      k++;
    pref_suf[q] = k;
  }
  return pref_suf[cykl.size() - 1];
}


/* Numerowanie cyklu, czyli grupowanie jego stanów w stany równowa¿ne. */
void numeruj_cykl(int pocz)
{
  int dlugosc = 0;
  while (col[pocz] < 3)
  {
    wynik[pocz] = !(dlugosc % pierw) ? pierw : (dlugosc % pierw);
    dlugosc++;
    col[pocz]= 3;
    pocz = t[pocz];
  }
}


int dlugosc = 0; /* d³ugo¶æ nawiniêtej czê¶ci cyklu */

/* Funkcja rekurencyjna, która numeruje stany ogonka, dopóki siê
 * ogonek nawija na cyklu. Kiedy przestaje, zaczyna im przypisywaæ
 * unikalne numery. */
bool nawin_ogonek(int poz)
{
  if (poz == pocz)
    return true;
  /* Ju¿ poprzednio siê nie da³o nawin±æ. */
  if (!nawin_ogonek(t[poz]))
  {
    wynik[poz] = ++pierw;
    return false;
  }
  dlugosc++;
  /* Sprawdzamy, czy siê dobrze odwija. */
  if (stany[poz] != cykl[(pierw - dlugosc % pierw) % pierw])
  {
    wynik[poz] = ++pierw;
    return false;
  } else
  {
    wynik[poz] = pierw - dlugosc % pierw;
    return true;
  }
}

int main()
{
  odczyt();
  pocz = poczatek_cyklu();
  int pref = funkcja_prefiksowa(); /* pref_suf[ca³y_cykl] */
  cykl.erase(cykl.begin());
  if (cykl.size() % (cykl.size() - pref))
    pierw = cykl.size();
  else
    pierw = cykl.size() - pref;
  numeruj_cykl(pocz);
  nawin_ogonek(spocz);
  /* Wypisujemy numery. */
  for (int i = 0; i < n; i++)
    printf("%d ",wynik[i]);
  printf("\n");
  return 0;
}
