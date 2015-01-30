#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <map>
using namespace std;

const int maxn = 1100;

bool notP[maxn];
int P[maxn], Pt;
void sieve(int n)
{
	Pt = 0;
	notP[1] = 1;
	for (int i = 2; i <= n; i++)
	{
		if (!notP[i]) P[++Pt] = i;
		for (int j = 1; j <= Pt && P[j] * i <= n; j++) {
			notP[P[j] * i] = 1;
			if (i % P[j] == 0) break;
		}
	}
}
int a[110][110];
int n,t;
void build()
{
	sieve(1000);
	scanf("%d%d", &t, &n);
	memset(a,0,sizeof(a));
	for (int i = 1; i <= n; i++)
	{
		int x;
		scanf("%d", &x);
		for (int j = 1; j <= t; j++)
		{
			if (x == 0)
				break;
			while ((x != 0) && (x % P[j] == 0))
			{
				a[j][i]++;
				x /= P[j];
			}
			a[j][i] %= 2;
		}
	}
}
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
int ans[1100];
void calc()
{
	int len = 1;
	ans[1] = 1;
	int p = gauss();
	for (int i = 1; i <= p; i++)
	{
		int x = 0;
		for (int k = 1; k <= len; k++)
		{
			ans[k] = ans[k]*2+x;
			x = ans[k] / 10;
			ans[k] %= 10; 
		}
		if (x > 0)
		{
			len++;
			ans[len] = x;
		}
	}
	ans[1]--;
	for (int i = len; i > 0; i--)
	{
		printf("%d", ans[i]);
	}
	printf("\n");
}
int main()
{
	freopen("rsa.in", "r", stdin);
	freopen("rsa.out", "w", stdout);
	build();
	calc();
	return 0;
}
