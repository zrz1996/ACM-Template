//求强联通分量
void tarjan(int u)
{
  low[u] = dfn[u] = ++curDfn;
  sta[sta_n++] = u;
  for (int i = head[u]; i; i = E[i].nxt)
  {
    if (!dfn[E[i].nxt])
    {
      tarjan(E[i].nxt);
      low[u] = min(low[u], low[E[i].v]);
    }
    else 
      if (!sccNum[E[i].v])
        low[u] = min(low[u], dfn[E[i].v]);
  }
  if (low[u] == dfn[u])
  {
    nScc++;
    int v;
    do
      v = sta[--sta_n], sccNum[v] = nScc;
    while (u != v);
  }
}
// 求点双连通分量+割点
void tarjan(int u, int peid = -1)
{
  low[u] = dfn[u] = ++curDfn;
  int nSubtree = 0;
  for (int i = head[u]; i = E[i].nxt; i = E[i].nxt)
    if (i != peid)
    {
      if (!dfn[E[i].v])
      {
        sta[sta_n++] = i;
        tarjan(E[i].v, i ^ 1);
        nSubtree++;
        if (low[E[i].v] >= dfn[v])
        {
          if (dfn[u] != 1)
            isCutPoint[u] = true;
          nBcc++;
          int e;
          do
            e = sta[--sta_n], bccNum[e] = nBcc;
          while (e != i);
        }
        low[u] = min(low[u], low[E[i].v]);
      }
      else
      {
        low[u] = min(low[u], dfn[E[i].v]);
        if (dfn[E[i].v] < dfn[u])
          sta[sta_n++] = i;
      }
    }
  if (dfn[u] == 1 && nSubtree >= 2)
    isCutPoint[u] = true;
}

// 求边双连通分量+桥
void tarjan(int u, int fa = -1)
{
  low[u] = dfn[u] = ++curDfn;
  sta[sta_n++] = u;
  inSta[u] = 1;
  for (int i = head[u]; i; i = E[i].nxt)
    if (E[i].v != fa)
    {
      if (!dfn[E[i].v])
      {
        tarjan(E[i].v, u);
        low[u] = min(low[u], low[E[i].v]);
      }
      else
        if (inSta[E[i].v])
          low[u] = min(low[u], dfn[E[i].v]);
    }
  if (low[u] == dfn[u])  //edge fa <-> u is a bridge 
  {
    int v;
    do
      v = sta[--sta_n], ebccNum[v] = u, inSta[v] = 0;
    while (u != v);
  }
}