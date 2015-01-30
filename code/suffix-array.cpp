const int maxn = 100002, logn = 21, maxint = 0x7f7f7f7f;
int n, sa[maxn], r[maxn + maxn], h[maxn], mv[maxn][logn];
// r is `doubled`
void initlg() {
	_lg[1] = 0;
	for (int i = 2; i < maxn; ++i) _lg[i] = _lg[i - 1] + ((i & (i - 1)) == 0 ? 1 : 0);
}
// remember to clear r & call initlg() before calling
void construct(int n, int *s) { // initlg();
	static pair<int/* Type */, int> ord[maxn];
	for (int i = 1; i <= n; ++i) ord[i] = make_pair(s[i], i);
	sort(ord + 1, ord + 1 + n);
	for (int i = 1; i <= n; ++i) {
		sa[i] = ord[i].second;
		r[sa[i]] = (i == 1 ? 1 : r[sa[i - 1]] + (ord[i - 1].first != ord[i].first));
	}
	static int tr[maxn], tsa[maxn], c[maxn];
	for (int l = 1; l < n; l <<= 1) {
		int cnt = 0;
		for (int i = 1; i <= n; ++i) if (sa[i] + l > n) tsa[++cnt] = sa[i];
		for (int i = 1; i <= n; ++i) if (sa[i] > l) tsa[++cnt] = sa[i] - l;
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= n; ++i) ++c[r[i]];
		for (int i = 1; i <= n; ++i) c[i] += c[i - 1];
		for (int i = n; i >= 1; --i) sa[c[r[tsa[i]]]--] = tsa[i];
		tr[sa[1]] = 1;
		for (int i = 2; i <= n; ++i) {
			tr[sa[i]] = tr[sa[i - 1]] + (r[sa[i]] != r[sa[i - 1]] || r[sa[i] + l] != r[sa[i - 1] + l]);
		}
		for (int i = 1; i <= n; ++i) r[i] = tr[i];
		if (r[sa[n]] == n) break;
	}
	int k = 0; /* Height && RMQ */
	for (int i = 1; i <= n; ++i) {
		if (--k < 0) k = 0;
		for (int j = sa[r[i] - 1]; r[i] != 1 && s[i + k] == s[j + k]; ++k);
		h[r[i]] = k;
	}
	for (int i = 1; i <= n; ++i) mv[i][0] = h[i];
	for (int k = 1; k < logn; ++k) {
		for (int i = 1, len = 1 << (k - 1); i + len <= n; ++i) {
			mv[i][k] = min(mv[i][k - 1], mv[i + len][k - 1]);
		}
	}
}

//faster algorithm
void da(int *r,int *sa,int n,int m) //r[n] = 0!!
{
	int i,j,p,*x=wa,*y=wb,*t;
	for(i=0;i<m;i++) ws[i]=0;
	for(i=0;i<n;i++) ws[x[i]=r[i]]++;
	for(i=1;i<m;i++) ws[i]+=ws[i-1];
	for(i=n-1;i>=0;i--) sa[--ws[x[i]]]=i;
	for(j=1,p=1;p<n;j*=2,m=p)
	{
		for(p=0,i=n-j;i<n;i++) y[p++]=i;
		for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
		for(i=0;i<n;i++) wv[i]=x[y[i]];
		for(i=0;i<m;i++) ws[i]=0;
		for(i=0;i<n;i++) ws[wv[i]]++;
		for(i=1;i<m;i++) ws[i]+=ws[i-1];
		for(i=n-1;i>=0;i--) sa[--ws[wv[i]]]=y[i];
		t=x; x=y; y=t;
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
		for (k?k--:0,j = sa[rank[i] - 1]; r[i+k] == r[j+k]; k++);
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