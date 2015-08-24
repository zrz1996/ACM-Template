C(n,m)奇偶    如果(n & m) == m，那么为奇数，否则为偶数
欧拉线上的四点中，九点圆圆心到垂心和外心的距离相等，而且重心到外心的距离是重心到垂心距离的一半。
定比分点：P, O, M, PM/MO = t; M = (P + t*O) / (1+t)
求因子和
\sum_{t_1=1}^{n_1} \sum_{t_2=1}^{n_2} \cdots \sum_{t_k=1}^{n_k} d(t_1 t_2 \cdots t_k) = \sum_{\substack{1 \leq t_i \leq n_i \ \textbf{for} \ 1 \leq i \leq k \\ (t_i,t_j)=1 \ \textbf{for} \ 1 \leq i < j \leq k}}[\frac{n_1}{t_1}][\frac{n_2}{t_2}]\cdots [\frac{n_k}{t_k}]

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

vector<> v;
sort(v.begin(), v.end(), cmp);

priority_queue<int, vector<int>, cmp> P;
