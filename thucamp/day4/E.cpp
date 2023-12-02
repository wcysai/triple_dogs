#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define F first
#define S second
#define ls t[o].ch[0]
#define rs t[o].ch[1]
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937_64 rng(std::chrono::system_clock::now().time_since_epoch().count());
struct node
{
    int ch[2],sz,val,lazy,pri,maxi;
};
namespace treap
{
    int root,tot;
    node t[MAXN];
    void init()
    {
        root=0;
        t[root].ch[0]=t[root].ch[1]=0;
        tot=0;
    }
    int newnode(int val)
    {
        tot++;
        t[tot].val=val; t[tot].ch[0]=t[tot].ch[1]=0;
        t[tot].sz=1; t[tot].pri=rng(); t[tot].maxi=t[tot].lazy=0;
        return tot;
    }
    void pushup(int o)
    {
        t[o].sz=t[ls].sz+t[rs].sz+1;
        t[o].maxi=max(t[ls].maxi,t[rs].maxi);
    }
    void add(int o,int v)
    {
        if(!o) return;
        t[o].maxi+=v; t[o].lazy+=v;
    }
    void pushdown(int o)
    {
        if(!t[o].lazy) return;
        add(ls,t[o].lazy); add(rs,t[o].lazy);
        t[o].lazy=0;
    }
    P split(int o,int cnt)
    {
        if(!o) return P(0,0);
        pushdown(o);
        if(t[ls].sz>=cnt)
        {
            P p=split(ls,cnt);
            int tl=p.F,tr=p.S;
            ls=tr; pushup(o);
            return P(tl,o);
        }
        else
        {
            P p=split(rs,cnt-t[ls].sz-1);
            int tl=p.F,tr=p.S;
            rs=tl; pushup(o);
            return P(o,tr);
        }
    }
    int merge(int x,int y)
    {
        if(!x||!y) return x+y;
        if(t[x].pri<t[y].pri)
        {
            pushdown(x);
            t[x].ch[1]=merge(t[x].ch[1],y);
            pushup(x);
            return x;
        }
        else
        {
            pushdown(y);
            t[y].ch[0]=merge(x,t[y].ch[0]);
            pushup(y);
            return y;
        }
    }
    void ins(int val)
    {
        P p=split(root,val);
        int tl=p.F,tr=p.S;
        root=merge(merge(tl,newnode(val)),tr);
    }
    void print(int o)
    {
        if(!o) return;
        print(ls);
        printf("%d ",t[o].val);
        print(rs);
    }
};
using namespace treap;
int n,m,q,a,b;
int type[MAXN],x[MAXN],y[MAXN];
int rt[MAXN];
set<int> row[MAXN];
set<int> col[MAXN];
int num[MAXN];
// row: 0-(n+1)
// col: 0-(m+1)
// dir: 0 : U 1: D 2: L 3:R
int get_id(int row,int col,int dir){
    return 4*(row*(m+2)+col)+dir;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<q;i++) scanf("%d%d%d",&type[i],&x[i],&y[i]);
    int ans=0;
    for(int i=1;i<=m;i++){
        int id=get_id(1,i,1);
        num[i]=newnode();
    }
    init();
    for(int i=1;i<=n;i++) ins(i);
    for(int i=0;i<n;i++)
    {
        scanf("%d%d",&a,&b);
        if(a>=b) continue;
        int len=min(b-a,n-b+1);
        P p1=split(root,a-1);
        P p2=split(p1.S,len);
        P p3=split(p2.S,b-a-len);
        P p4=split(p3.S,len);
        root=merge(p1.F,merge(p4.F,merge(p3.F,merge(p2.F,p4.S))));
    }
    print(root);
    return 0;
}
