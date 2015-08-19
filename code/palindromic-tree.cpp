struct Palindromic_Tree {
	int next[maxn][N], fail[maxn], cnt[maxn], num[maxn], len[maxn];
	int S[maxn];
	int last, n, p;

	int newnode(int l) {
		for (int i = 0; i < N; ++i) next[p][i] = 0;
		cnt[p] = 0;
		num[p] = 0;
		len[p] = l;
		return p++;
	}

	void init() {
		p = 0;
		newnode(0);
		newnode(-1);
		n = last = 0;
		S[n] = -1;
		fail[0] = 1;
	}

	void add(int c) {
		c -= 'a';
		S[++n] = c;
		int cur = last;
		while (S[n - len[cur] - 1] != S[n])
			cur = fail[cur];
		if (!next[cur][c]) {
			int now = newnode(len[cur] + 2);
			int x = fail[cur];
			while (S[n - len[x] - 1] != S[n])
				x = fail[x];
			fail[now] = next[x][c];
			next[cur][c] = now;
			num[now] = num[fail[now]] + 1;
		}
		last = next[cur][c];
		cnt[last]++;
	}

	void count() {
		for (int i = p - 1; i >= 0; --i) cnt[fail[i]] += cnt[i];
	}
};