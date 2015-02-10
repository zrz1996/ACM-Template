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
const int maxn = 100000;
const int INF = 0xFFFFF;
int f[maxn], a[maxn];
struct cmp
{
	bool operator ()(const int &a, const int &b)
	{
		return a < b;
	}
};
template <typename T>
class Heap
{
	public:
		T v[maxn];
		int size = 0;
		void push(T x)
		{
			int c = size++;
			while (c > 0)
			{
				int p = (c - 1) / 2;
				if (v[p] <= x)
					break;
				v[c] = v[p];
				c = p;
			}
			v[c] = x;
		}
		bool empty()
		{
			return size == 0;
		}
		T top()
		{
			return v[0];
		}
		void pop()
		{
			T x = v[--size];
			int p = 0;
			while (p * 2 + 1 < size)
			{
				int lc = p * 2 + 1;
				int rc = p * 2 + 2;
				if (rc < size && v[rc] < v[lc])
					lc = rc;
				if (v[lc] >= x)
					break;
				v[p] = v[lc];
				p = lc;
			}
			v[p] = x;
		}
};
int main()
{
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
		scanf("%d", &a[i]);
	//priority_queue<int, vector<int>, cmp> P;
	Heap<int> P;
	for (int i = 0; i < n; i++)
	{
		P.push(a[i]);
	}
	while (!P.empty())
	{
		cout << P.top() << " ";
		P.pop();
	}
	cout << endl;
	return 0;
}
