#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>
using namespace std;
const int maxn = 2005;
typedef long long LL;
const LL Mod = 100000007;
LL fac[maxn], C[maxn][maxn], B[maxn], Inv[maxn], n, k;
void init()
{
	/*fac[0] = 1;
	for (int i = 1; i < maxn; i++)
		fac[i] = fac[i-1] * i % Mod;*/
	for (int i = 0; i < maxn; i++)
	{
		C[i][0] = C[i][i] = 1;
		if (i == 0) continue;
		for (int j = 1; j < i; j++)
			C[i][j] = (C[i-1][j] + C[i-1][j-1]) % Mod;
	}
	Inv[1] = 1;
	for (int i = 2; i < maxn; i++)
		Inv[i] = (Mod - Mod / i) * Inv[Mod % i] % Mod;
	B[0] = 1;
	for (int i = 1; i < maxn; i++)
	{
		LL ans = 0;
		if (i == maxn - 1)
			break;
		for (int j = 0; j < i; j++)
		{
			ans += B[j]*C[i+1][j];
			ans %= Mod;
		}
		ans *= -Inv[i+1];
		ans = (ans % Mod + Mod) % Mod;
		B[i] = ans;
	}
}
LL Cal(int n, int k)
{
	LL ans = Inv[k+1];
	LL sum = 0;
	for (int i = 1; i <= k+1; i++)
	{
		sum += C[k+1][i]*fac[i] % Mod * B[k+1-i] % Mod;
	   	sum %= Mod;	
	}
	ans *= sum;
	ans %= Mod;
	return ans;
}
int main()
{
	init();
	while (scanf("%lld%lld", &n, &k) != EOF)
	{
		fac[0] = 1;
		for (int i = 1; i < maxn; i++)
			fac[i] = fac[i-1] * (n+1) % Mod;
		printf("%lld\n",Cal(n,k));
	}
	return 0;
}
