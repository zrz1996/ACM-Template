#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <queue>
using namespace std;
typedef long long LL;
typedef long long ll;
#define For(i,a,b) for (int i = (a); i <= (b); i++)
#define FOR(i,a,b) for (int i = (a); i <= (b); i++)
#define Cor(i,a,b) for (int i = (a); i >= (b); i--)
#define rep(i,a) for (int i = 0; i < a; i++)
#define Fill(a,b) memset(a,b,sizeof(a))
int n, K, inv_K;
int P = 1998585857, g = 3;
int w[2][100000];
int fpm(int a, int b)
{
	int ret = 1;
	for (; b; b >>= 1)
	{
		if (b & 1)
			ret = (LL)ret * a % P;
		a = (LL)a * a % P;
	}
	return ret;
}
void FFT_Init() {
	for ( K = 1; K < n << 1; K <<= 1 ); inv_K = fpm(K, P - 2);
	w[ 0 ][ 0 ] = w[ 0 ][ K ] = w[ 1 ][ 0 ] = w[ 1 ][ K ] = 1;
	int G = fpm( g, ( P - 1 ) / K );
	FOR( i, 1, K - 1 ) {
		w[ 0 ][ i ] = (ll)w[ 0 ][ i - 1 ] * G % P;
	}
	FOR( i, 0, K ) {
		w[ 1 ][ i ] = w[ 0 ][ K - i ];
	}
}

void FFT( int X[], int k, int v ) {
	int i, j, l;
	for ( i = j = 0; i < k; i++ ) {
		if ( i > j ) swap( X[ i ], X[ j ] );
		for ( l = k >> 1; ( j ^= l ) < l; l >>= 1 );
	}
	for ( i = 2; i <= k; i <<= 1 )
		for ( j = 0; j < k; j += i )
			for ( l = 0; l < i >> 1; l++ ) {
				int t = (ll)X[ j + l + ( i >> 1 ) ] * w[ v ][ ( K / i ) * l ] % P;
				X[ j + l + ( i >> 1 ) ] = ( (ll)X[ j + l ] - t + P ) % P;
				X[ j + l ] = ( (ll)X[ j + l ] + t ) % P;
			}
	if (v)
		for (i = 0; i < k; i++)
			X[i] = (ll)X[i] * inv_K % P;
}
int tmp[100000];
void GetInv( int A[], int A0[], int t ) {
	if ( t == 1 ) { A0[ 0 ] = fpm( A[ 0 ], P - 2); return; }
	GetInv( A, A0, ( t + 1 ) >> 1 );
	K = 1; for ( ; K <= ( t << 1 ) + 3; K <<= 1 ); inv_K = fpm( K, P - 2);
	w[ 0 ][ 0 ] = w[ 0 ][ K ] = w[ 1 ][ 0 ] = w[ 1 ][ K ] = 1;
	int G = fpm( g, ( P - 1 ) / K );
	FOR( i, 1, K - 1 ) {
		w[ 0 ][ i ] = (ll)w[ 0 ][ i - 1 ] * G % P;
	}
	FOR( i, 0, K ) {
		w[ 1 ][ i ] = w[ 0 ][ K - i ];
	}
	FOR ( i, 0, t - 1 ) { tmp[ i ] = A[ i ]; } FOR ( i, t, K - 1 ) { tmp[ i ] = 0; }
	FFT( tmp, K, 0 ); FFT( A0, K, 0 );
	FOR ( i, 0, K - 1 ) { tmp[ i ] = 2 - (ll)tmp[ i ] * A0[ i ] % P + P; tmp[i] %= P; }
	FOR ( i, 0, K - 1 ) { A0[ i ] = (ll)A0[ i ] * tmp[ i ] % P; }
	FFT( A0, K, 1 );
	FOR ( i, t, K - 1 ) { A0[ i ] = 0; }
}
int fac[100010], inv_fac[100010], B[100010];
void GetBernoulli(int n)
{
	fac[0] = inv_fac[0] = 1;
	For(i, 1, n - 1)
		fac[i] = (ll)fac[i - 1] * i % P;
	For(i, 1, n)
		inv_fac[i] = (ll)inv_fac[i - 1] * fpm(i + 1, P - 2) % P;
	GetInv(inv_fac, B, n);
	rep(i, n)
		B[i] = (ll)B[i] * fac[i] % P;
	rep(i, n)
		cout << B[i] << endl;
}
int main()
{
	return 0; 
}
