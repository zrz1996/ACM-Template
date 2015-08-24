LL mult64(LL a, LL b, LL m) { // 64bit multiply 64bit
	a %= m, b %= m;
	LL ret = 0;
	for (; b; b >>= 1) {
		if (b & 1) ret = (ret + a) % m;
		a = (a + a) % m;
	}
	return ret;
}
/* return x*y%mod. no overflow if x,y < mod
 * remove 'i' in "idiv"/"imul" -> unsigned */
inline long mulmod(long x,long y,long mod)
{
	long ans = 0;
	__asm__ (
		"movq %1,%%rax\n imulq %2\n idivq %3\n"
		:"=d"(ans):"m"(x),"m"(y),"m"(mod):"%rax"
	);
	return ans;
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
bool witness(LL a, LL n)  //二次探查
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

// discrete-logarithm, finding y for equation b = g^y % p
//p is prime
int M;  //M = (int)sqrt(phi(p));
void discrete_log_init(LL g, LL p)
{
	hash_init();
	int i;
	LL tmp;
	for(i = 0, tmp = 1; i < M; i++, tmp = tmp * g % p)
		insert(tmp % p, i * 1LL);
}
LL discrete_log(LL g, LL p, LL b)
{
	LL res, am = fpow(g, M, p), inv = fpow(b, p - 2, p), x = 1;
	for(LL i = M; ; i += M)
	{
		if((res = find((x = x * am % p) * inv % p)) != -1)
		{
			return i - res;
		}   
		if(i > p)break;
	}   
	return -1;
}

//A^x=B mod C 
//hash add(); find();
int Inval(int a,int b,int n){
	int x,y,e;
	ext_gcd(a, n, x, y);
	e=(LL)x * b % n;
	return e < 0 ? e + n : e;
}
int BabyStep(int A, int B, int C)
{
	top = maxn; ++ idx; 
	LL buf = 1 % C, D = buf, K;
	int i, d = 0, tmp;
	for(i = 0; i <= 100; buf = buf * A % C, ++i)
		if (buf == B) 
			return i;
	while((tmp = gcd(A, C)) != 1)
	{
		if(B % tmp) return -1;
		++d;
		C /= tmp;
		B /= tmp;
		D = D * A / tmp % C;
	}
	int M = (int)ceil(sqrt((double)C));
	for(buf = 1 % C, i = 0; i <= M; buf = buf * A % C, ++i)
		add(i, buf); //hash
	for(i = 0, K = fpow((LL)A, M, C); i <= M; D = D * K % C, ++i)
	{
		tmp = Inval((int)D, B, C);
		int w;
		if(tmp >= 0 && (w = find(tmp)) != -1)  //hash
			return i * M + w + d;
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
