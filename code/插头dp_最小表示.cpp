#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <iostream>
using namespace std;
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
char c[20];
void init()
{
	scanf("%d%d",&n, &m);
	memset(maze,0,sizeof(maze));
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", c);
		for (int j = 0; j < m; j++)
			if (c[j] == '.')
				maze[i][j+1] = 1, ex = i, ey = j+1;
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
int main()
{
	init();
	solve();
	return 0;
}
