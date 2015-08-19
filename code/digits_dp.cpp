#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
typedef long long LL;
L1 getsum1(int n, int k)
{
	LL B = 1;
	for (int i = 0; i < n; i++) B *= k;
	return B * n * (k - 1) / 2;
}
L2 getsum2(int prefixsum, int n, int k)
{
	LL B = getsum1(n, k);
	LL C = prefixsum;
	for (int i = 0; i < n; i++)
		C *= k;
	return B + C;
}
LL getsum3(int prefixsum, long long n, int k)
{
	if (n < k)
	{
		LL ret = 0;
		for (int i = 0; i <= n; i++)
			ret += prefixsum + i;
		return ret;
	}
	LL t = 1, tn = n;
	int d = 0;
	while (tn >= k)
	{
		tn /= k;
		t *= k;
		d++;
	}
	LL ret = 0;
	for (int i = 0; i < tn; i++)
		ret += getsum2(prefixsum + i, d, k);
	ret += getsum3(prefixsum + tn, n - tn * t, k);
	return ret;
}
int main()
{
	int k;
	long long a, b;
	scanf("%lld%lld%d",&a, &b, &k);
	printf("%lld\n", getsum3(0,b,k) - getsum3(0,a-1,k));
	return 0;
}
