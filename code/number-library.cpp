LL mult64(LL a, LL b, LL m) { // 64bit multiply 64bit
	a %= m, b %= m;
	LL ret = 0;
	for (; b; b >>= 1) {
		if (b & 1) ret = (ret + a) % m;
		a = (a + a) % m;
	}
	return ret;
}

LL fpow(LL a, LL p, int mod) { // fast power-modulo algorithm
	LL res = 1;
	for (; p; p >>= 1) {
		if (p & 1) res = (res * a) % mod; // using mult64 when mod is 64-bit
		a = (a * a) % mod;
	}
	return res;
}

int exgcd(int x, int y, int &a, int &b) { // extended gcd, ax + by = g.
	int a0 = 1, a1 = 0, b0 = 0, b1 = 1;
	while (y != 0) {
		a0 -= x / y * a1; swap(a0, a1);
		b0 -= x / y * b1; swap(b0, b1);
		x %= y; swap(x, y);
	}
	if (x < 0) a0 = -a0, b0 = -b0, x = -x;
	a = a0, b = b0;
	return x;
}

int inverse(int x, int mod) { // multiplicative inverse.
	int a = 0, b = 0;
	if (exgcd(x, mod, a, b) != 1) return -1;
	return (a % mod + mod) % mod; // C1: x & mod are co-prime
	return fpow(x, mod - 2, mod); // C2: mod is prime
}

void init_inverse(int mod) { // O(n), all multiplicative inverse, mod is prime
	inv[0] = inv[1] = 1;
	for (int i = 2; i < n; ++i) {
		inv[i] = (LL)inv[mod % i] * (mod - mod / i) % mod; // overflows?
	}
}

LL CRT(int cnt, int *p, int *b) { // chinese remainder theorem
	LL N = 1, ans = 0;
	for (int i = 0; i < k; ++i) N *= p[i];
	for (int i = 0; i < k; ++i) {
		LL mult = (inverse(N / p[i], p[i]) * (N / p[i])) % N;
		mult = (mult * b[i]) % N;
		ans += mult; ans %= N;
	}
	if (ans < 0) ans += N;
	return ans;
}

void sieve(int n) { // generating primes using euler's sieve
	notP[1] = 1;
	for (int i = 2; i <= n; ++i) {
		if (!notP[i]) P[++Pt] = i;
		for (int j = 1; j <= Pt && P[j] * i <= n; ++j) {
			notP[P[j] * i] = 1;
			if (i % P[j] == 0) break;
		}
	}
}
void sieve(int n)
{
	memset(isP,0,sizeof(isP));
	mu[1] = 1;
	phi[1] = 0;
	for (int i = 2; i <= n; i++)
	{
		 if (isP[i] == 0)
		 {
			 isP[i] = 1;
			 mu[i] = -1;
			 phi[i] = i-1;
			 prime[np++] = i;
		 }
		 for (int j = 0; j < np && i * prime[j]<=n ; j++)
			 if (i % prime[j])
			 {
				 int k = i * prime[j];
				 isP[k] = -1;
				 mu[k] = -mu[i];
				 phi[k] = phi[i] * (prime[j]-1);
			 }
		 	 else
			 {
				 int k = i * prime[j];
				 isP[k] = -1;
				 mu[k] = 0;
				 phi[k] = phi[i] * prime[j];
				 break;
			 }
		 summu[i] = summu[i-1] + mu[i];
		 sumphi[i] = sumphi[i-1] + phi[i];
	}
}
bool miller_rabin(LL n, LL b) { // miller-rabin prime test
	LL m = n - 1, cnt = 0;
	while (m % 2 == 0) m >>= 1, ++cnt;
	LL ret = fpow(b, m, n);
	if (ret == 1 || ret == n - 1) return true;
	--cnt;
	while (cnt >= 0) {
		ret = mult(ret, ret, n);
		if (ret == n - 1) return true;
		--cnt;
	}
	return false;
}

bool prime_test(LL n) {
	if (n < 2) return false;
	if (n < 4) return true;
	if (n == 3215031751LL) return false;
	const int BASIC[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
	for (int i = 0; i < 12 && BASIC[i] < n; ++ i) {
		if (!miller_rabin(n, BASIC[i])) return false;
	}
	return true;
}

LL pollard_rho(LL n, LL seed) { // pollard-rho divisors factorization
	LL x, y;
	x = y = rand() % (n - 1) + 1;
	LL head = 1, tail = 2;
	while (true) {
		x = mult(x, x, n);
		x = (x + seed) % n;
		if (x == y) return n;
		LL d = gcd(max(x - y, y - x), n);
		if (1 < d && d < n) return d;
		if (++head == tail) y = x, tail <<= 1;
	}
}

void factorize(LL n, vector<LL> &divisor) {
	if (n == 1) return;
	if (prime_test(n)) divisor.push_back(n);
	else {
		LL d = n;
		while (d >= n) d = pollard_rho(n, rand() % (n - 1) + 1);
		factorize(n / d, divisor);
		factorize(d, divisor);
	}
}
//faster factor
int p[1000010], prime[100010], psize = 1000000;
LL a[1000100];
void sieve(){
	int i,j,tot,t1;
	for (i=1;i<=psize;i++) p[i]=i;
	for (i=2,tot=0;i<=psize;i++){
		if (p[i]==i) prime[++tot]=i;
		for (j=1;j<=tot && (t1=prime[j]*i)<=psize;j++){
			p[t1]=prime[j];
			if (i%prime[j]==0) break;
		}
	}
}
inline LL mul(LL a, LL b, LL p) 
{
	if (p <= 1000000000) 
		return a * b % p;
	else 
		if (p<=1000000000000LL) 
			return (((a * (b >> 20) % p) << 20) + (a * (b & ((1 << 20) - 1)))) % p;
		else 
		{
			LL d = (LL)floor(a * (long double)b / p + 0.5);
			LL ret = (a * b - d * p) % p;
			if (ret < 0) ret += p;
			return ret;
		}
}
LL fpow(LL a,LL n,LL p) 
{
	LL ans=1;
	for (; n; n >>= 1) 
	{
		if (n & 1) ans = mul(ans, a, p);
		a = mul(a, a, p);
	}
	return ans;
}
bool witness(LL a, LL n) 
{
	int t = 0;
	LL u = n - 1;
	for (; ~u & 1; u >>= 1) t++;
	LL x = fpow(a, u, n), _x = 0;
	for (; t; t--) 
	{
		_x = mul(x, x, n);
		if (_x == 1 && x != 1 && x != n-1) return 1;
		x = _x;
	}
	return _x != 1;
}
bool miller(LL n) 
{
	if (n < 2) return 0;
	if (n < psize) return p[n] == n;
	if (~n & 1) return 0;
	for (int j = 0; j <= 7; j++) 
		if (witness(rand() % (n - 1) + 1, n)) 
			return 0;
	return 1;
}
LL gcd(LL a,LL b) 
{
	LL ret = 1;
	while (a != 0) 
	{
		if ((~a & 1) && (~b & 1)) 
			ret <<= 1,a >>= 1,b >>= 1;
		else 
			if (~a & 1) 
				a >>= 1; 
			else 
				if (~b & 1) 
					b >>= 1;
				else 
				{
					if (a < b) 
						swap(a, b);
					a -= b;
				}
	}
	return ret * b;
}
LL rho(LL n) 
{
	for (;;) 
	{
		LL X = rand() % n, Y, Z, T = 1, *lY = a, *lX = lY;
		int tmp = 20;
		LL C = rand() % 10 + 3;
		X = mul(X, X, n) + C;
		*(lY++) = X; lX++;
		Y = mul(X, X, n) + C;
		*(lY++) = Y;
		for(; X != Y;) 
		{
			LL t = X - Y + n;
			Z = mul(T, t, n);
			if(Z == 0) 
				return gcd(T, n);
			tmp--;
			if (tmp == 0) 
			{
				tmp = 20;
				Z = gcd(Z, n);
				if (Z != 1 && Z != n) 
					return Z;
			}
			T = Z;
			Y = *(lY++) = mul(Y, Y, n) + C;
			Y = *(lY++) = mul(Y, Y, n) + C;
			X = *(lX++);
		}
	}
}
void find(LL n, int c)
{
	for (int i = 0; i < ct; i++)
		if (n % fac[i] == 0)
			n /= fac[i], fac[ct++] = fac[i];
    if(n == 1) return;
	if (n <= psize)
	{
		for (; n != 1; n /= p[n])
			fac[ct++] = p[n];
		return;
	}
    if(miller(n))
    {
        fac[ct++] = n;
        return ;
    }
    LL p = n;
    LL k = c;
    while(p >= n) p = rho(p);
    find(p, k);
    find(n / p, k);
}
void factorize(LL n, vector<pair<LL, LL> > &result)
{
	result.clear();
	if (n == 1)
		return;
	ct = 0;
	find(n, 120);
	sort(fac, fac + ct);
	num[0] = 1;
	int k = 1;
	for(int i=1; i<ct; i++)
	{
		if(fac[i] == fac[i-1])
			++num[k-1];
		else
		{
			num[k] = 1;
			fac[k++] = fac[i];
		}
	}
	cnt = k;
	for (int i = 0; i < cnt; i++)
		result.push_back(make_pair(fac[i], num[i]));
}

// discrete-logarithm, finding y for equation k = x^y % mod
int discrete_logarithm(int x, int mod, int k) {
	if (mod == 1) return 0;
	int s = 1, g;
	for (int i = 0; i < 64; ++i) {
		if (s == k) return i;
		s = ((LL)s * x) % mod;
	}
	while ((g = gcd(x, mod)) != 1) {
		if (k % g) return -1;
		mod /= g;
	}
	static map<int, int> M; M.clear();
	int q = int(sqrt(double(euler(mod)))) + 1;
	for (int i = 0, b = 1; i < q; ++i) {
		if (M.find(b) == M.end()) M[b] = i;
		b = ((LL)b * x) % mod;
	}
	int p = fpow(x, q, mod);
	for (int i = 0, b = 1; i <= q; ++i) {
		int v = ((LL)k * inverse(b, mod)) % mod;
		if (M.find(v) != M.end()) {
			int y = i * q + M[v];
			if (y >= 64) return y;
		}
		b = ((LL)b * p) % mod;
	}
	return -1;
}
//faster discrete log
void discrete_log_init(LL g, LL p)
{
	hash_init();
	int i;
	LL tmp;
	for(i = 0, tmp = 1; i < 1e6; i++, tmp = tmp * g % p)
		insert(tmp % p, i * 1LL);
}
LL discrete_log(LL g, LL p, LL b)
{
	LL res, am = fpow(g, 1e6, p), inv = fpow(b, p - 2, p), x = 1;
	for(LL i = 1e6; ; i += 1e6)
	{
		if((res = find((x = x * am % p) * inv % p)) != -1)
		{
			return i - res;
		}   
		if(i > p)break;
	}   
	return -1;
}
// primtive root, finding the number with order p-1 
int primtive_root(int p) {
	vector<int> factor;
	int tmp = p - 1;
	for (int i = 2; i * i <= tmp; ++i) {
		if (tmp % i == 0) {
			factor.push_back(i);
			while (tmp % i == 0) tmp /= i;
		}
	}
	if (tmp != 1) factor.push_back(tmp);
	for (int root = 1; ; ++root) {
		bool flag = true;
		for (int i = 0; i < factor.size(); ++i) {
			if (fpow(root, (p - 1) / factor[i], p) == 1) {
				flag = false;
				break;
			}
		}
		if (flag) return root;
	}
}
