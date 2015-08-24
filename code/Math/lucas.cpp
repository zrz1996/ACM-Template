LL C(LL n, LL m)
{
	if (m > n) return 0;
	LL ans = 1;
	for (int i = 1; i <= m; i++)
	{
		LL a = (n + i - m) % p;
		LL b = i % p;
		ans = ans * (a * fpow(b, p-2, p) % p) % p;
	}
	return ans;
}
LL lucas(LL n, LL m)
{
	if (m == 0) return 1;
	return C(n % p, m % p) * lucas(n / p, m / p) % p;
}