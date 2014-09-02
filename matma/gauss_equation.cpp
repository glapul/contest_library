
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
vector<vector<double> > matrix;
bool eq(double a, double b)
{
    return abs(a-b)<10e-9;
}
void swap_row(int a, int b)
{
	swap(matrix[a], matrix[b]);
}
void add_row(int from, int to, double C)
{
	for (int i = 0; i < matrix[to].size(); i++)
		matrix[to][i] += matrix[from][i] * C;
}
void elim()
{
	int n = matrix.size();
	int m = matrix[0].size();
	for (int i = 0; i < n; i++)
	{
		int nonzero = i;
		while (nonzero<n && matrix[nonzero][i] == 0 )
			nonzero++;
		if (nonzero < n)
			swap_row(i, nonzero);
		for (int j = i + 1; j < n; j++)
			add_row(i, j, -matrix[j][i] / matrix[i][i]);
	}
	for (int i = n - 1; i >= 0; i--)
	{
		if (!eq(matrix[i][i],0.0))
		{
			for (int j = i - 1; j>=0; j--)
				add_row(i, j, -matrix[j][i] / matrix[i][i]);
			double tmp = matrix[i][i];
			for (int j = 0; j < matrix[i].size(); j++)
				matrix[i][j] /= tmp;
		}
	}
}
