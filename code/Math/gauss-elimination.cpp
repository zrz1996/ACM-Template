void gauss(int n, double g[maxn][maxn]) { // input: N * (N + 1) Matrix
	for (int i = 1; i <= n; ++i) {
		double temp = 0;
		int pos = -1;
		for (int j = i; j <= n; ++j) {
			if (fabs(g[j][i]) > temp) temp = fabs(g[j][i]), pos = j;
		}
		if (pos == -1) continue;
		for (int k = 1; k <= n + 1; ++k) swap(g[pos][k], g[i][k]);
		temp = g[i][i];
		for (int k = 1; k <= n + 1; ++k) g[i][k] /= temp;
		for (int j = i + 1; j <= n; ++j) {
			temp = g[j][i];
			for (int k = 1; k <= n + 1; ++k) g[j][k] -= temp * g[i][k];
		}
	}
	for (int i = n; i >= 1; --i) {
		for (int j = 1; j < i; ++j) {
			g[j][n + 1] -= g[i][n + 1] * g[j][i];
			g[j][i] = 0;
		}
	}
}
// n is the number of variables, t is the number of equations
// index from 1
// return the number of free variables
int gauss()
{
	int pos;
	int i = 1, j = 1;
	while (i <= t && j <= n)
	{
		pos = i;
		for (int k = i; k <= t; k++)
			if (a[k][j] != 0)
			{
				pos = k;
				break;
			}
		if (a[pos][j] > 0)
		{
			if (pos != i)
				for (int k = 1; k <= n; k++)
					swap(a[i][k], a[pos][k]);
			for (int p = i+1; p <= t; p++)
				if (a[p][j] > 0)
				{
					for (int k = j; k <= n; k++)
						a[p][k] ^= a[i][k];
				}
			i++;
		}
		j++;
	}
	return n - i + 1;
}