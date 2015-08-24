const int maxn = 100002, logn = 21, maxint = 0x7f7f7f7f;
int n, sa[maxn], r[maxn + maxn], h[maxn], mv[maxn][logn];
void initlg() {
	_lg[1] = 0;
	for (int i = 2; i < maxn; ++i) 
		_lg[i] = _lg[i - 1] + ((i & (i - 1)) == 0 ? 1 : 0);
}
void da(int *r, int *sa, int n, int m) //r[n] = 0!!
{
	int i, j, p, *x = wa, *y = wb, *t;
	for(i = 0; i < m; i++) ws[i] = 0;
	for(i = 0; i < n; i++) ws[x[i] = r[i]]++;
	for(i = 1; i < m; i++) ws[i] += ws[i-1];
	for(i = n-1; i >= 0; i--) sa[--ws[x[i]]] = i;
	for(j = 1, p = 1; p < n; j *= 2, m = p)
	{
		for(p = 0, i = n - j; i < n; i++) y[p++] = i;
		for(i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i] - j;
		for(i = 0; i < n; i++) wv[i] = x[y[i]];
		for(i = 0; i < m; i++) ws[i] = 0;
		for(i = 0; i < n; i++) ws[wv[i]]++;
		for(i = 1; i < m; i++) ws[i] += ws[i-1];
		for(i = n - 1; i >= 0; i--) sa[--ws[wv[i]]] = y[i];
		t = x; x = y; y = t;
		p = 1;
		x[sa[0]] = 0;
		for (i = 1; i < n; i++)
			x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + j] == y[sa[i - 1] + j]) ? p-1 : p++;
	}
	return;
}
int height[maxn], rank[maxn];    //height[2..n]
void calheight(int *r, int *sa)
{
	for (int i = 1; i <= n; i++)
		rank[sa[i]] = i;
	int j, k = 0;
	for (int i = 0; i < n; height[rank[i++]] = k)
		for (k ? k-- : 0, j = sa[rank[i] - 1]; r[i+k] == r[j+k]; k++);
}
int askRMQ(int l, int r) {
	int len = r - l + 1, log = _lg[r - l + 1];
	return min(mv[l][log], mv[r - (1 << log) + 1][log]);
}

int LCP(int i, int j) {
	i = r[i], j = r[j];
	if (i > j) swap(i, j);
	return askRMQ(++i, j);
}
