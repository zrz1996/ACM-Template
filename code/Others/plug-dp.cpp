//verison 1
//hash
const int maxn = 1000010;
const int Hash_Mod = 30007;
const int maxm = 15;
int maze[maxm][maxm];
int code[maxm];
int n, m;
struct HashMap
{
	int head[Hash_Mod], nxt[maxn], size;
	long long f[maxn],state[maxn];
	void init()
	{
		memset(head,0,sizeof(head));
		size = 0;
	}
	void push(long long st, long long ans)
	{
		int ht = st % Hash_Mod;
		for (int i = head[ht]; i; i = nxt[i])
		{
			if (state[i] == st)
			{
				f[i] += ans;
				return;
			}
		}
		size++;
		nxt[size] = head[ht]; head[ht] = size;
		state[size] = st; f[size] = ans;
	}
}hm[2];
void decode(int *code, int m, long long st)
{
	for (int i = m; i >= 0; i--)
	{
		code[i] = st & 7;
		st >>= 3;
	}
}
int ch[maxm];
long long encode(int *code, int m)
{
	long long st = 0;
	memset(ch,-1,sizeof(ch));
	ch[0] = 0;
	int cnt = 1;
	for (int i = 0; i <= m; i++)
	{
		if (ch[code[i]] == -1)
			ch[code[i]] = cnt++;
		code[i] = ch[code[i]];
		st <<= 3;
		st |= code[i];
	}
	return st;
}
//换行原理：上一行行尾是----|,下一行行首是|----,水平线上的状态完全相同
void shift(int *code, int m)
{
	for (int i = m; i > 0; i--)
		code[i] = code[i-1];
	code[0] = 0;
}
int ex, ey;
void dpblank(int i, int j, int cur)
{
	int k, up, left;
	for (k = 1; k <= hm[cur].size; k++)
	{
		decode(code, m, hm[cur].state[k]);
		left = code[j-1];
		up = code[j];
		if (up && left)
		{
			if (up == left)
			{
				if (i == ex && j == ey)
				{
					code[j-1] = code[j] = 0;
					if (j == m)
						shift(code,m);
					hm[cur ^ 1].push(encode(code,m),hm[cur].f[k]);
				}
			}
			else
			{
				code[j] = code[j-1] = 0;
				for (int p = 0; p <= m; p++)
					if (code[p] == left)
						code[p] = up;
				if (j == m)
					shift(code,m);
				hm[cur ^ 1].push(encode(code,m),hm[cur].f[k]);
			}
		}
		else
			if ((left != 0 && up == 0) || (up != 0 && left == 0))
			{
				int p = left + up;
				if (maze[i+1][j])
				{
					code[j-1] = p; code[j] = 0;
					if (j == m)
						shift(code,m);
					hm[cur ^ 1].push(encode(code,m),hm[cur].f[k]);
				}
				if (maze[i][j+1])
				{
					code[j-1] = 0; code[j] = p;
					hm[cur ^ 1].push(encode(code,m),hm[cur].f[k]);
				}
			}
			else
			{
				if (maze[i][j+1] && maze[i+1][j])
				{
					code[j-1] = code[j] = 13;
					hm[cur ^ 1].push(encode(code,m),hm[cur].f[k]);
				}
			}
	}

}
void dpblock(int i, int j, int cur)
{
	for (int k = 1; k <= hm[cur].size; k++)
	{
		decode(code, m, hm[cur].state[k]);
		code[j-1] = code[j] = 0;
		if (j == m)
			shift(code,m);
		hm[cur ^ 1].push(encode(code,m), hm[cur].f[k]);
	}
}
void solve()
{
	int cur = 0;
	hm[cur].init();
	hm[cur].push(0,1);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= m; j++)
		{
			hm[cur ^ 1].init();
			if (maze[i][j])
				dpblank(i,j,cur);
			else
				dpblock(i,j,cur);
			cur ^= 1;
		}
	long long ans = 0;
	for (int i = 1; i <= hm[cur].size; i++)
		ans += hm[cur].f[i];
	printf("%lld\n", ans);
}

//version 2
//matrix improved
const int maxm = 7, maxs = 2187, pow3[] = {1, 3, 9, 27, 81, 243, 729, 2187}; // m+1, 3**(m+1)
int n, m, top, stack[maxm + 1], match[maxs][maxm + 1], cnt, valid[maxs], ID[maxs];
int mt[N + 1][N + 1], mt2[N + 1][N + 1], f[maxm][maxs], g[maxs]; // N: cnt
int gb3(int v, int bit) { return (v / pow3[bit - 1]) % 3; }
int mb3(int v, int bit, int value) { return v - pow3[bit - 1] * gb3(v, bit) + pow3[bit - 1] * value; }
int ub3(int v, int bit) { return v - pow3[bit - 1] * gb3(v, bit); }
void upd(int &x, int v) { x += v; x %= mod; }

void dfs(int p, int st, int lt) {
	if (p > m + 1) {
		if (lt == 0) {
			valid[st] = true;
			if (st % 3 == 0) ID[st] = ++cnt; // omitted
			top = 0;
			for (int j = 1; j <= m + 1; ++j) {
				if (gb3(st, j) == 1) {
					stack[++top] = j;
				} else if (gb3(st, j) == 2) {
					match[st][j] = stack[top];
					match[st][stack[top--]] = j;
				}
			}
		}
	} else {
		dfs(p + 1, st, lt); // #
		dfs(p + 1, mb3(st, p, 1), lt + 1); // (
		if (lt) dfs(p + 1, mb3(st, p, 2), lt - 1); // )
	}
}

int plugDP(int n, int m) {
	memset(valid, 0, sizeof(valid)), memset(ID, -1, sizeof(ID)), cnt = 0;
	memset(mt, 0, sizeof(mt)), memset(mt2, 0, sizeof(mt2));
	dfs(1, 0, 0);
	for (int start = 0; start < pow3[m + 1]; ++start) {
		if (ID[start] == -1) continue;
		for (int fi = 0; fi < 2; ++fi) { // Last colume flag
			memset(f, 0, sizeof(f)); memset(g, 0, sizeof(g));
			f[0][start] = 1;
			for (int j = 0; j <= m; ++j) {
				for (int k = 0; k < pow3[m + 1]; ++k) {
					if (!valid[k]) continue;
					if (j == m) {
						if (!fi && !gb3(k, j + 1)) { // i != n
							upd(g[ub3(k, j + 1) * 3], f[j][k]); // Unmark last bit
						}
					} else {
						 // Consider mp[i][j + 1] valid ? (bit1 = bit2 = 0)
						int bit1 = gb3(k, j + 1), bit2 = gb3(k, j + 2), 
							t = ub3(ub3(k, j + 1), j + 2), tt;
						if (bit1 == 1 && bit2 == 2) { // Merge two brackets
							if (fi && j + 1 == m) { // i == n
								upd(f[j + 1][t], f[j][k]);
							}
						} else if (bit1 == 2 && bit2 == 1) {
							upd(f[j + 1][t], f[j][k]);
						} else if (!bit1 && !bit2) { // bit1 == 0 && bit2 == 0
							tt = mb3(mb3(t, j + 1, 1), j + 2, 2);
							upd(f[j + 1][tt], f[j][k]);
						} else if (bit1 == bit2) {
							if (bit1 == 1) { // bit1 == 1 && bit2 == 1
								tt = mb3(t, match[k][j + 2], 1);
								upd(f[j + 1][tt], f[j][k]);
							} else { // bit1 == 2 && bit2 == 2
								tt = mb3(t, match[k][j + 1], 2);
								upd(f[j + 1][tt], f[j][k]);
							}
						} else { // bit1 == 0 || bit2 == 0
							upd(f[j + 1][k], f[j][k]);
							swap(bit1, bit2);
							tt = mb3(mb3(t, j + 1, bit1), j + 2, bit2);
							upd(f[j + 1][tt], f[j][k]);
						}
					}
				}
			}
			if (fi) {
				for (int i = 0; i < pow3[m + 1]; ++i) if (ID[i] != -1) mt2[ID[start]][ID[i]] = f[m][i];
			} else {
				for (int i = 0; i < pow3[m + 1]; ++i) if (ID[i] != -1) mt[ID[start]][ID[i]] = g[i];
			}
		}
	}
	matrix_t mat = 0, mat2 = 0, mf = 0;
	for (int i = 1; i <= cnt; ++i) for (int j = 1; j <= cnt; ++j) {
		mat.x[j][i] = mt[i][j], mat2.x[j][i] = mt2[i][j];
	}
	mat = mat2 * mat.power(n - 1);
	mf.x[ID[0]/* ?? */][1] = 1;
	mf = mat * mf;
	return mf.x[ID[0]][1];
}