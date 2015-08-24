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

const int MAX_SIDE = 100000, MAX_NODE = 100000;

class network_flow
{
    private:
        
        int label[MAX_NODE], GAP[MAX_NODE];
        bool visited[MAX_NODE];
        int in_flow[MAX_NODE];
        int vS, vT;
        int tot_node, label_max;
        queue<int> active[MAX_NODE];
    
    public:
        struct EDGES
        {
            int pre[MAX_SIDE], val[MAX_SIDE], node[MAX_SIDE], last[MAX_NODE];
            int tot;
            EDGES()
            {
                tot = 1;
            }
            void add_edge(int s, int t, int v)
            {
                tot++;
                pre[tot] = last[s];
                node[tot] = t;
                val[tot] = v;
                last[s] = tot;
            }
        }edge;
        void set_s(int s) { vS = s; }
        void set_t(int t) { vT = t; }
        void set_tot_node(int n) { tot_node = n; }
        void HLPP()
        {
            get_length();
            prepare();
            max_flow();
        }
        
        void add_edge(int s, int t, int v)
        {
            edge.add_edge(s, t, v);
            edge.add_edge(t, s, 0);
        }
        
        void max_flow()
        {
            while(label_max)
            {
                if(active[label_max].empty())
                {
                    label_max--;
                    continue;
                }

                int now = active[label_max].front(), ext, val;
                int label_min = tot_node + 1;
                int push_flow;
                
                active[label_max].pop();
                for(int pos(edge.last[now]); pos; pos = edge.pre[pos])
                {
                    ext = edge.node[pos];
                    val = edge.val[pos];
                    if(val > 0)
                    {
                        if(label[ext] + 1 == label[now])
                        {
                            push_flow = min(val, in_flow[now]);
                            edge.val[pos] -= push_flow;
                            edge.val[pos ^ 1] += push_flow;
                            in_flow[now] -= push_flow;
                            in_flow[ext] += push_flow;
                            if(push_flow)
                                active[label[ext]].push(ext);
                        }
                    }
                    if(edge.val[pos])
                        label_min = min(label_min, label[ext]);
                    if(!in_flow[now])
                        break;
                }
                if(in_flow[now] && now != vT && label_min < tot_node)
                {
                    int cache = label[now];
                    GAP[label[now]] --;
                    label[now] = label_min + 1;
                    GAP[label[now]] ++;
                    if(GAP[cache] == 0)
                    {
                        for(int i(1); i <= tot_node; ++ i)
                            if(label[i] > cache && label[i] < tot_node + 1)
                            {
                                GAP[label[i]]--;
                                GAP[tot_node + 1]++;
                                label[i] = tot_node + 1;
                            }
                    }
                    active[label[now]].push(now);
                    if(label[now] > label_max)
                        label_max= label[now];
                }    
            }
        }
        
        void prepare()
        {
            for(int pos(edge.last[vS]); pos; pos = edge.pre[pos])
            {
                int ext = edge.node[pos], val = edge.val[pos]; 
                if(val > 0)
                {
                    in_flow[ext] += val;
                    edge.val[pos] -= val;
                    edge.val[pos ^ 1] += val;
                    if(label[ext] > label_max)
                        label_max = label[ext];
                    active[label[ext]].push(ext);
                }
            }
        }
        
        void get_length()
        {
            int queue[MAX_NODE];
            
            fill(label + 1, label + 1 + tot_node, tot_node + 1);
            memset(visited, 0, sizeof(visited));
            queue[0]  = vT;
            label[vT]= 0;
            visited[vT] = 1;
            GAP[0] = 1;
            GAP[tot_node + 1] = tot_node - 1;
            
            for(int p1(0), p2(0); p1 <= p2; ++ p1)
            {
                int now = queue[p1], ext;
                for(int pos(edge.last[now]); pos; pos = edge.pre[pos])
                {
                    ext = edge.node[pos];
                    if(!visited[ext])
                    {
                        visited[ext] = 1;
                        queue[++p2] = ext;
                        label[ext] = label[now] + 1;
                        GAP[tot_node + 1]--;
                        GAP[label[ext]]++;
                    }
                }
            }
        }
        int get_ans()
        {
            return in_flow[vT];
        }
}net;
