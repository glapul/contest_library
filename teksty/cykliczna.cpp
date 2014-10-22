/* Jakub Radoszewski
 * Sprawdzanie równowa¿no¶ci cyklicznej dwóch s³ów
 * sprytnym algorytmem liniowym
 */

#include<algorithm>
#include<vector>
#include<string>
using namespace std;

//Sprawdzanie równowa¿no¶ci cyklicznej
bool cykl(string u,string w)
{
  string x(u), y(w);
  x += u; x += '$'; y += w; y += '#';
  int i = -1, j = -1, k = 1;
  while (i < u.size() - 1 && i < w.size() - 1 && k <= u.size())
  {
    k = 1;
    while (x[i + k] == y[j + k])
      k++;
    if (k <= u.size())
    {
      if (x[i + k] > y[j + k])
        i += k;
      else
        j += k;
    }
  }
  return k > u.size();
}
