#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 100000;
const int maxint = 1000000000;
int n,m,s,t,ec = 0,d[maxn], vd[maxn], sf[maxn], tf[maxn];
struct edge_link
{
	int v, r;
	edge_link *next, *pair;
}edge[maxn], *header[maxn], *current[maxn];
void add(int u, int v, int r)
{
	ec++;
	edge[ec].v = v; edge[ec].r = r;
	edge[ec].next = header[u]; header[u] = &edge[ec];
	edge[ec].pair = &edge[ec+1];
	ec++;
	edge[ec].pair = &edge[ec-1];
	edge[ec].next = header[v]; header[v] = &edge[ec];
	edge[ec].v = u; edge[ec].r = 0;
}
int augment(int u, int flow)
{
	if (u == t)
		return flow;
	int temp, res = 0;
	for (edge_link *&e = current[u]; e!= NULL; e = e->next)
	{
		if (e->r && d[u] == d[e->v]+1)
		{
			temp = augment(e->v, min(e->r, flow-res));
			e->r -= temp, e->pair->r += temp, res += temp;
			if (d[s] == t || res == flow) return res; 
		}
	}
	if (--vd[d[u]] == 0) d[s] = t;
	else current[u] = header[u], ++vd[++d[u]];
	return res;
}
bool vis[maxn];
void bfs()
{
	queue<int> Q;
	memset(vis,0,sizeof(vis));
	d[t] = 0;
	Q.push(t);
	vis[t] = 1;
	while (!Q.empty())
	{
		int x = Q.front(); Q.pop();
		for (edge_link *e = header[x]; e != NULL; e = e->next)
		{
			if (!vis[e->v] && e->r == 0)
			{
				vis[e->v] = 1;
				d[e->v] = d[x] + 1;
				Q.push(e->v);
			}
		}
	}
	memset(vd,0,sizeof(vd));
	for (int i = 1; i <= t; i++)
		vd[d[i]]++;
}
int c[maxn];
int sap()
{
	int flow = 0;
	//memset(d,0,sizeof(d)), memset(vd,0,sizeof(vd));
	bfs();
	//vd[0] = t;
	for (int i = 1; i <= t; i++) current[i] = header[i];
	while (d[s] < t) flow += augment(s, maxint);
	return flow;
}
void build()
{
	int sumf = 0;
	scanf("%d%d", &n, &m);
	memset(sf,0,sizeof(sf));
	memset(tf,0,sizeof(tf));
	memset(c,0,sizeof(c));
	for (int i = 1; i <= m; i++)
	{
		int u,v,w;
		scanf("%d%d%d%d", &u, &v, &c[i], &w);
		add(u,v,w-c[i]);
		sf[v]+=c[i];
		tf[u]+=c[i];
		sumf += c[i];
	}
	for (int i = 1; i <= n; i++)
	{
		add(n+1,i,sf[i]);
		add(i,n+2, tf[i]);
		s = n+1;
		t = n+2;
	}
	add(t,s,maxint);
	int f = sap();
	if (f != sumf)
	{
		printf("NO\n");
		return;
	}
	else
	{
		printf("YES\n");
		for (int i = 1; i <= m; i++)	
			printf("%d\n", edge[i*2].r+c[i]);
	}
}
int main()
{
	freopen("cooling.in", "r", stdin);
	freopen("cooling.out", "w", stdout);
	build();
	return 0;
}
