/*
 * Autor programu: Marek Cygan
 * data:           17.03.2005
 * Program ilustrujacy liczenie tablicy PREF.
 * Wartoscia PREF[i] jest dlugosc najdluzszego
 * prefiksu calego slowa, ktory wystepuje w slowie
 * rozpoczynajac od i-tej litery
 */

#include <iostream>
#include <string>
using namespace std;

const int N=1000000;
int PREF[N];
int n; //dlugosc slowa
string X; //slowo, dla ktorego bedziemy obliczac wartosci tablicy PREF

//funkcja ta zwraca dlugosc najdluzszego 
//prefiksu slowa X, zaczynajacego sie na
//pozycji j, zakladajac ze przed pozycja k
//prefiks jest zgodny
int pref(int j,int k)
{
  k=max(k,j);
  int i=k-j;
  while (k<=n && X[i]==X[k-1]) { i++;  k++; }
  return k-j;
}

//procedura obliczaja kolejne wartosci tablicy PREF
//w czasie liniowym
void licz_PREF()
{
  int i=1;
  PREF[1]=-1; 
  for (int j=2; j<=n; ++j)
  { int l=j-i+1;
    if (l<=PREF[i] && j+PREF[l]<i+PREF[i])
      PREF[j]=PREF[l];
    else
     { PREF[j]=pref(j,i+PREF[i]);
       i=j;
     }
  }
}

int main()
{
  cin >> X; n=X.size();
  licz_PREF(); 
  for (int i=1; i<=(int)X.size(); ++i)
    printf("PREF[%d]=%d\n",i,PREF[i]);
}
