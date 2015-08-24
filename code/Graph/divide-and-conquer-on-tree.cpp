int bk, size[maxn], parent[maxn], ver[maxn];
bool cut[maxn];

void bfs(int r) { // bfs in each sub-tree
	parent[r] = 0, bk = 0; // maintain root extra information
	static queue<int> Q; static stack<int> U;
	Q.push(r);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop(); U.push(u);
		size[u] = 1, ver[++bk] = u; // find a node in sub-tree
		for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
			int v = *it;
			if (v == parent[u] || cut[v]) continue;
			parent[v] = u; // maintain v from u
			Q.push(v);
		}
	}
	while (!U.empty()) {
		int u = U.top(); U.pop();
		if (parent[u]) size[parent[u]] += size[u];
	}
}

int findCentre(int r) {
	static queue<int> Q;
	int result = 0, rsize = maxint;
	bfs(r);
	Q.push(r);
	while (!Q.empty()) {
		int u = Q.front();
		Q.pop();
		int temp = size[r] - size[u];
		for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
			int v = *it;
			if (cut[v] || v == parent[u]) continue;
			temp = max(temp, size[v]);
			Q.push(v);
		}
		if (temp < rsize) rsize = temp, result = u;
	}
	return result;
}

int work(int u) {
	int result = 0;
	u = findCentre(u);
	cut[u] = true;
	for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
		int v = *it;
		if (!cut[v]) /*result += */work(v); // process each sub-tree
	}
	for (vector<int>::iterator it = edge[u].begin(); it != edge[u].end(); ++it) {
		int v = *it;
		if (cut[v]) continue;
		bfs(v); // then combine sub-trees
	}
	cut[u] = false;
	return result;
}

int fa[maxn], dep[maxn], son[maxn], size[maxn];
void dfs1(int x, int p, int depth)
{
	fa[x] = p; dep[x] = depth;
	size[x] = 1;
	int maxsize = 0;
	son[x] = 0;
	for (int i = head[x]; i; i = E[i].nxt)
	{
		int v = E[i].v;
		if (v != p)
		{
			dfs1(v, x, depth + 1);
			size[x] += size[v];
			if (size[v] > maxsize)
			{
				maxsize = size[v];
				son[x] = v;
			}
		}
	}
}
int top[maxn], p[maxn], fp[maxn], lable;
void dfs2(int x, int sp)
{
	top[x] = sp;
	p[x] = ++lable;
	fp[p[x]] = x;
	if (son[x])
		dfs2(son[x], sp);
	else
		return;
	for (int i = head[x]; i; i = E[i].nxt)
	{
		int v = E[i].v;
		if (v != son[x] && v != fa[x])
			dfs2(v, v);
	}
}
int find(int u, int v)
{
	int f1 = top[u], f2 = top[v];
	int ret = 0;
	while (f1 != f2)
	{
		if (dep[f1] < dep[f2])
		{
			swap(f1, f2);
			swap(u, v);
		}
		ret = max(ret, seg.query(p[f1], p[u], 1, n, 1));
		u = fa[f1]; f1 = top[u];
	}
	if (u == v)
		return ret;
	if (dep[u] > dep[v])
		swap(u, v);
	ret = max(ret, seg.query(p[son[u]], p[v], 1, n, 1));
	return ret;
}