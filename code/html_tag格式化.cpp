#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define pb  push_back
#define rep(i, n) for (int i = 0; i < (n); i++)
vector<string> tag;
char c;
void get_tag()
{
	string s;
	s = "";
	bool flag = false;
	char c;
	while (true)
	{
		c = getchar();
		if (c == 32 || c == 10 || c == 9)
		{
			if (s.size() && flag == false)
			{
				tag.pb(s);
				s = "";
			}
			else
				if (flag)
				{
					s += c;
				}
			continue;
		}
		if (c == '<')
		{
			flag = true;
			if (s.size())
			{
				tag.pb(s);
				s = "";
			}
			s += c;
		}
		else
			if (c == '>')
			{
				flag = false;
				s += c;
				if (s == "</html>")
				{
					tag.pb(s);
					s = "";
					return;
				}
				tag.pb(s);
				s = "";
			}
			else 
				s += c;
	}	
}
vector<string> Q;
void solve()
{
	tag.clear();
	get_tag();
	Q.clear();
	int dis = 0;
	string s = "";
	rep(i, tag.size())
	{
		s = tag[i];
		if (tag[i][0] == '<')
			Q.pb(tag[i]);
		else
		{
			while (tag[i+1][0] != '<')
				s += " "+tag[++i];
			Q.pb(s);
		}
	}
	int dt = 0, type;
	rep(i, Q.size())
	{
		if (i == 0)
		{
			printf("%s\n", Q[i].c_str());
			continue;
		}
		if (Q[i][0] == '<')
		{
			if (Q[i][1] == '/')
				type = 0, dt = -1;
			else 
				if (Q[i][Q[i].size()-2] == '/')
					type = 1,dt = 0;
				else
					type = 1, dt = 1;	
		}
		else
			type = 1, dt = 0;
		rep(j,dis+type)
			putchar(' ');
		printf("%s\n", Q[i].c_str());
		dis += dt;
	}
}
int main()
{
	int t;
	scanf("%d", &t);
	rep(i, t)
	{
		printf("Case #%d:\n", i+1);
		solve();
	}
	return 0;
}
