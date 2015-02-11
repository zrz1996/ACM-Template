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
#define For(i,a,b) for (int i = (a); i <= (b); i++)
#define Cor(i,a,b) for (int i = (a); i >= (b); i--)
#define Fill(a,b) memset(a,b,sizeof(a))
const int maxn = 10000;
const int maxm = 1000000;

struct edge
{
	int nxt, v;
}E[maxm];
int head[maxn];
int tot;
int n, m;

void add(int u, int v)
{
	tot++;
	E[tot].nxt = head[u]; head[u] = tot;
	E[tot].v = v;
}
void init()
{
	scanf("%d", &n);
	int v;
	for (int i = 1; i <= n; i++)
	{
		while (scanf("%d", &v), v)
			add(i, v);
	}
}
bool flag[maxn];
struct node
{
	int v;
	node *nxt;
};
node *H = NULL;
void topsort(int p)
{
	if (flag[p])
		return;
	flag[p] = true;
	for (int i = head[p]; i; i = E[i].nxt)
		topsort(E[i].v);
	node *t = new node;
	t->nxt = H;
	H = t;
	H->v = p;
}
int main()
{
	init();
	memset(flag, 0, sizeof(flag));
	for (int i = 1; i <= n; i++)
		if (!flag[i])
			topsort(i);
	for (node *i = H; i; i = i->nxt)
		printf("%d ", i->v);
	printf("\n");
	return 0;
}
