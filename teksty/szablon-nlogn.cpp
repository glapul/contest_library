/* ZADANIE: SZABLON
 * autor programu: MAREK CYGAN
 * data: 10.06.2004
 *
 * Rozwi±zanie wzorcowe:
 * 
 * Rozwi±zanie o z³o¿ono¶ci O(n * lg n),
 * wyszukiwanie wzorca za pomoc± algorytmu KMP.
 * Ze zbioru wszystkich prefikso-sufiksów usuwamy te,
 * które na pewno nie zostan± szablonami
 * i do sprawdzenia pozostaje co najwy¿ej lg n
 * prefikso-sufiksów.
 */
#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

const int MAX_LEN = 500000; // maksymalna d³ugo¶æ napisu

string napis; // wczytywany napis 
int dlugosc; // d³ugo¶æ napisu
int p[MAX_LEN + 1]; // tablica z warto¶ciami funkcji prefiksowej

/* Wczytywanie danych. */
void czytaj_dane()
{
	char s[MAX_LEN + 2];
	fgets(s, MAX_LEN + 2, stdin); // wczytanie napisu ze standardowego wej¶cia
	napis = s;
	dlugosc = napis.size() - 1; // nie liczymy znaku koñca stringa
} /* czytaj_dane */

/* Obliczanie funkcji prefiksowej dla napisu. */
void licz_funkcje_prefiksowa()
{
	int t = 0;
	p[0] = p[1] = 0;
	for (int i = 2; i <= dlugosc; ++i)
	{
		while (t > 0 && napis[t] != napis[i - 1])
      t = p[t];
		if (napis[t] == napis[i - 1])
      t++;
		p[i] = t;
	} /* for */
} /* licz_funkcje_prefiksowa */

/* Obliczanie d³ugo¶ci wszystkich prefiksów napisu,
które s± jednocze¶nie jego sufiksami. */
void licz_prefikso_sufiksy(vector<int> & kandydaci)
{
	int i = dlugosc;
	kandydaci.clear();
	while (i > 0) 
	{
    kandydaci.push_back(i);
    i = p[i];
  } /* while */
} /* licz_prefikso_sufiksy */

/* Usuwanie tych d³ugo¶ci, które na pewno nie
pos³u¿± jako najkrótszy szablon. */
void usun_zbedne(vector<int> & kandydaci)
{
	vector<int> nowe_dlugosci; 
	for (int i = 1; i < (int) kandydaci.size(); ++i)
	  if (2 * kandydaci[i] < kandydaci[i - 1])
			// je¿eli krótszy kandydat na szablon nie pokrywa d³u¿szego
			nowe_dlugosci.push_back(kandydaci[i - 1]);		
	nowe_dlugosci.push_back(kandydaci[kandydaci.size() - 1]);
	kandydaci = nowe_dlugosci;
} /* usun_zbedne */

/* Sprawdzenie czy prefikso-sufiks wej¶ciowego napisu o d³ugo¶ci n
mo¿e pos³u¿yæ jako szablon. */
bool dobry(int n)
{
	int i = 0, j = 0;
	int last = -1; // last to numer pozycji ostatniego znaku
							   // w ostatnio znalezionym wyst±pieniu szablonu
	while (i + n - 1 < dlugosc)
	{
		if (last + 1 < i)
		  // "dziura" miêdzy kolejnymi wyst±pieniami szablonu
      return false;  
		while (j < n && napis[j] == napis[i + j])
      j++;
		if (j == n) // znale¼li¶my kolejne wyst±pienie szablonu
			last = i + n - 1;
		i += max(1, j - p[j]);
    j = p[j];
	} /* while */
	return true; // ca³y napis zosta³ pokryty
} /* dobry */

int rozwiaz()
{
	vector<int> kandydaci;
	licz_funkcje_prefiksowa();
	licz_prefikso_sufiksy(kandydaci);
	usun_zbedne(kandydaci);
	int i = kandydaci.size();
	// sprawdzamy d³ugo¶ci kandydatów na szablony, zaczynaj±c od najkrótszych
	// oraz koñcz±c na pierwszym znalezionym szablonie
	while (!dobry(kandydaci[--i]))
    ; // ta pêtla musi siê zatrzymaæ, gdy¿ ca³y napis jest dobrym szablonem
	return kandydaci[i];
} /* rozwiaz */

int main()
{
	czytaj_dane();
	printf("%d\n", rozwiaz());
	return 0;
} /* main */
