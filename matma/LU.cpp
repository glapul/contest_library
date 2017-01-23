#include <bits/stdc++.h>
using namespace std;

typedef vector<vector<double>> Matrix;

struct LUFactorization {
  vector<int> RowPermutation;
  Matrix L, U;
};


void addVector(vector<double>& a, const vector<double>&b, double f) {
  for (int i = 0; i < (int)a.size(); i++)
    a[i] += b[i] * f;
}

LUFactorization ComputeLUFactorization(Matrix a) {
  int n = a.size();

  LUFactorization result;
  result.RowPermutation = vector<int>(n);
  result.L = vector<vector<double>>(n, vector<double>(n));

  for (int i = 0; i < n; i++) {

    int maxAbsIndex = i;
    for (int j = i; j < n; j++) {
      if (abs(a[j][i]) > abs(a[maxAbsIndex][i])) {
        maxAbsIndex = j;
      }
    }
    result.RowPermutation[i] = maxAbsIndex;
    swap(a[i], a[maxAbsIndex]);
    swap(result.L[i], result.L[maxAbsIndex]);
    result.L[i][i] = 1.0;

    // Eliminate.
    for (int j = i + 1; j < n; j++) {
      double ratio = -a[j][i]/a[i][i];
      addVector(a[j], a[i], ratio);
      result.L[j][i] = -ratio;
    }
  }
  result.U = a;
  return result;
};

vector<double> SolveEquation(const LUFactorization& lu, vector<double> x) {
  int n = x.size();
  // First, apply permutation.
  for (int i = 0; i < n; i++) {
    swap(x[i], x[lu.RowPermutation[i]]);
  }

  // Solve Ly = x.
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < i; j++) {
      x[i] -= lu.L[i][j] * x[j];
    }
    x[i] /= lu.L[i][i]; // Well, it is 1 anyway.
  }

  // Solve Uz = y.
  for (int i = n - 1; i >= 0; i--) {
    for (int j = n - 1; j > i; j--) {
      x[i] -= lu.U[i][j] * x[j];
    }
    x[i] /= lu.U[i][i]; // And it doesn't need to be 1.
  }

  return x;
}

void solve() {
  int n;
  cin >> n;

  Matrix A(n, vector<double>(n));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      cin >> A[i][j];

  LUFactorization lu = ComputeLUFactorization(A);

  //for (int i = 0; i < n; i++) {
    //for (int j = 0; j < n; j++)
      //cout << lu.L[i][j] << " ";
    //cout << endl;
  //}
  //for (int i = 0; i < n; i++) {
    //for (int j = 0; j < n; j++)
      //cout << lu.U[i][j] << " ";
    //cout << endl;
  //}


  int m;
  cin >> m;

  while (m--) {
    vector<double> x(n);
    for (int i = 0; i < n; i++)
      cin >> x[i];
    for (auto i : SolveEquation(lu, x))
      cout << setprecision(15) << fixed << i << " ";
    cout << endl;
  }
}

int main() {
  int z;
  cin >> z;
  while (z--)
    solve();
}



