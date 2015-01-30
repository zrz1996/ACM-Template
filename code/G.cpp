const int maxn = 100010;
int w[maxn], a[maxn];
struct que
{
	int l, r,ID;
}Q[maxn];
int n,q;
void init(
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
		scanf("%d", &a[i]);
	for (int i = 1; i <= q; i++)
	{
		int u,v;
		scanf("%d%d", &u, &v);
		Q[i].l = u; Q[i].r = v;
		Q[i].ID = i;
	}
}
bool cmpL(const que &a, const que &b)
{
	return a.l < b.l;
}
bool cmpR(const que &a, const que &b)
{
	return a.r < b.r;
}

int res;
void clear()
{
	memset(w,0,sizeof(w));
	res = 0;
}
int ans[maxn];
void add(int x, int d)
{
	if (d == 1)
	{
		if (w[x-1] == 0 && w[x+1] == 0)
			res++;
		if (w[x-1] == 1 && w[x+1] == 1)
			res--;
		w[x] = 1;
	}
	if (d == -1)
	{
		if (w[x-1] == 0 && w[x+1] == 0)
			res--;
		if (w[x-1] == 1 && w[x+1] == 1)
			res++;
		w[x] = 0;
	}
}
void solve()
{
	int SQRTN = (int)sqrt((double)q);
	sort(Q + 1, Q + 1 + q, cmpL);
	for (int i = 1; i <= q; i += SQRTN) {
		clear();
		int begin = i, end = i + SQRTN - 1;
		if (end > q) end = q;
		sort(Q + begin, Q + end + 1, cmpR);
		Q[begin - 1].l = 1, Q[begin - 1].r = 0;
		for (int j = begin; j <= end; ++j) {
			for (int k = Q[j - 1].r + 1; k <= Q[j].r; ++k) add(k, 1);
			if (Q[j].l > Q[j - 1].l) {
				for (int k = Q[j - 1].l; k < Q[j].l; ++k) add(k, -1);
			} else if (Q[j].l < Q[j - 1].l) {
				for (int k = Q[j].l; k < Q[j - 1].l; ++k) add(k, 1);
			}
			ans[Q[j].ID] = res;
		}
	}
}
int main()
{
	int t;
	scanf("%d", &t);
	while (t--)
	{
		init();
		solve();
		for (int i = 1; i <= q; i++)
			printf("%d\n", ans[i]);

	}
	return 0;
}