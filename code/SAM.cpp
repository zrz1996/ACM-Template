//K-string
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <cstring>
#include <cmath>
#include <queue>
#include <map>
#include <set>

using namespace std;
#define N 200009
struct SAM
{
    SAM *pre,*son[27];
    int len,count;
}pool[N*3],*tail,*root,*now;

int t,n,m,k,tot,ans;
char ch[N],ch1;
void add(int c)
{
    SAM *p=tail,*np=&pool[tot++];tail=np;
    memset(np->son,NULL,sizeof(np->son));
    np->len=p->len+1;np->count=0;
    while(p&&p->son[c]==NULL) p->son[c]=np,p=p->pre;
    if(p==NULL) np->pre=root;
    else
    {
        SAM *q=p->son[c];
        if(q->len==p->len+1) np->pre=q;
        else
        {
            SAM *nq=&pool[tot++];
            *nq=*q;
            nq->len=p->len+1;
            np->pre=q->pre=nq;
            while(p&&p->son[c]==q) p->son[c]=nq,p=p->pre;
        }
    }
    while(np!=root && np->count<k)
    {
        ++(np->count);
        if(np->count==k)
        {
            ans+=np->len-np->pre->len;
            break;
        }
        np=np->pre;
    }
}
int main()
{
    while(~scanf("%d%d%d",&n,&m,&k))
    {
        scanf("%s",ch);
        tot=ans=0;
        now=tail=root=&pool[tot++];
        memset(root->son,NULL,sizeof(root->son));
        root->len=root->count=0;
        for(int i=0;i<n;++i) add(ch[i]-'a');
        while(m--)
        {
            scanf("%d",&t);
            if(t==2) printf("%d\n",ans);
            else
            {
                getchar();
                scanf("%c",&ch1);
                add(ch1-'a');
            }
        }
    }
    return 0;
}
