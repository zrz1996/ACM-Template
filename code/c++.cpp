#pragma comment(linker,"/STACK:102400000,102400000") 
压位 1 ~ n          
void zip(int x)
{
	int p = x / 32;
	int q =  x % 32;
	mask[][p] |= (1 << q); 
}
C(n,m)奇偶    如果(n & m) == m，那么为奇数，否则为偶数
欧拉线上的四点中，九点圆圆心到垂心和外心的距离相等，而且重心到外心的距离是重心到垂心距离的一半。
定比分点：P, O, M, PM/MO = t; M = (P + t*O) / (1+t)
.vimrc
set smartindent
set cindent
set number
set st=4
set ts=4
set sw=4
map <F9> :w<cr>:!g++ % -o %< -g -Wall<cr>
map <C-F9> :!time ./%<<cr>
map <F4> :w<cr>:!gedit %<cr>
set smarttab
set nowrap

#include <iomanip>
cout <<setprecision()

char buf[];
string x = buf;
bool strcmp(buf,"")

auto it = setty.begin();
auto it : setty

typedef pair< , > PII;
PII.first   PII.second

vector<> v;
sort(v.begin(), v.end(), cmp);
