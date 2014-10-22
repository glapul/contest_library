/* Jakub Radoszewski
 * Algorytm Manachera - obliczanie promieni palindromów
 * parzystych (Manacher1) i nieparzystych (Manacher2)
 */

#include<algorithm>
#include<vector>
#include<string>
using namespace std;

//Palindromy parzyste
vector<int> Manacher1(string s)
{
  string x("$"); x += s; x += '#'; // '$' i '#' - specjalne znaki
  vector<int> R;
  R.push_back(0);
  int i = 1, j = 0;
  while (i <= x.size() - 1)
  {
    while (x[i - j] == x[i + j + 1])
      j++;
    R.push_back(j);
    int k = 1;
    while (R[i - k] != R[i] - k && k <= j)
    {
      R.push_back(min(R[i - k], R[i] - k));
      k++;
    }
    j=max(j - k, 0); i += k;
  }
  return R;
}

//Palindromy nieparzyste
vector<int> Manacher2(string s)
{
  string x("$"); x += s; x += '#'; // '$' i '#' - specjalne znaki
  vector<int> R;
  R.push_back(0);
  int i = 1, j = 0;
  while (i <= x.size() - 1)
  {
    while (x[i - j - 1] == x[i + j + 1])
      j++;
    R.push_back(j);
    int k = 1;
    while (R[i - k] != R[i] - k && k <= j)
    {
      R.push_back(min(R[i - k], R[i] - k)); k++;
    }
    j=max(j - k, 0); i += k;
  }
  return R;
}
