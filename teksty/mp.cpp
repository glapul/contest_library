/* Jakub Radoszewski
 * Algorytm Morrisa-Pratta - wersja z tablic± Bord
 */
#include<algorithm>
#include<vector>
#include<string>
using namespace std;


vector<int> compute(string P)
{
  vector<int> p;
  int m = P.size() - 1;
  p.PB(0); p.PB(0);
  int k = 0;
  for (int q = 2; q <= m; q++)
  {
    while (k > 0 && P[k + 1] != P[q])
      k = p[k];
    if (P[k + 1] == P[q])
      k++;
    p.push_back(k);
  }
  return p;
}

//to MP wymaga, by s³owa siê rozpoczyna³y od indeksu 1
void mp(string T,string P)
{
  int m = P.size() - 1, n = T.size() - 1;
  vector<int> p(compute(P));
  int q = 0;
  for(int i = 1; i <= n; i++)
  {
    while (q > 0 && P[q + 1] != T[i])
      q = p[q];
    if (P[q + 1] == T[i])
      q++;
    if (q == m)
    {
      printf("Wystapienie: %d\n",i-m);
      q = p[q];
    }
  }
}
