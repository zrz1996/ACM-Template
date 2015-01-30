#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;
typedef long long LL;
LL p;
LL quick_mod(LL a, LL b)
{
	LL ans = 1;
	a %= p;
	while (b)
	{
		if (b % 2 == 1) ans = ans * a % p;
		a = a * a % p;
		b >>= 1;
	}
	return ans;
}
LL C(LL n, LL m)
{
	if (m > n) return 0;
	LL ans = 1;
	for (int i = 1; i <= m; i++)
	{
		LL a = (n + i - m) % p;
		LL b = i % p;
		ans = ans * (a * quick_mod(b, p-2) % p) % p;
	}
	cout << n << " " << m << " " << ans << endl; 
	return ans;
}
LL lucas(LL n, LL m)
{
	if (m == 0) return 1;
	return C(n % p, m % p) * lucas(n / p, m / p) % p;
}
LL n, m;
int main()
{
	cin >> n >> m >> p;
	cout << lucas(n,m);
	return 0;
}
