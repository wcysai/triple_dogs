#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define MAXN 5005
#define MAXM 100005
#define MAXT 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,T;
int x[MAXN],y[MAXN],a[MAXN],b[MAXN],f[MAXM],g[MAXM];
ll c[MAXT];
ll ans[MAXT];
vector<int> ord;
struct segtree
{
    vector<P> st[4*MAXM];
    void build(int k,int l,int r)
    {
        st[k].clear();
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
    }
    void add(int k,int u,int v)
    {
        P p=P(u,v);
        while(st[k].size()>1)
        {
            int sz=(int)st[k].size();
            if(1LL*(st[k][sz-1].F-st[k][sz-2].F)*(p.S-st[k][sz-1].S)<=1LL*(st[k][sz-1].F-p.F)*(st[k][sz-2].S-st[k][sz-1].S))
                st[k].pop_back();
            else break;
        }
        st[k].push_back(p);
    }
    ll query(int k,int u,int v)
    {
        if(!st[k].size()) return -1;
        int l=-1,r=(int)st[k].size()-1;
        while(r-l>1)
        {
            int mid=(l+r)/2;
            if(1LL*st[k][mid].F*u+1LL*st[k][mid].S*v>=1LL*st[k][mid+1].F*u+1LL*st[k][mid+1].S*v) l=mid;
            else r=mid;
        }
        return 1LL*st[k][r].F*u+1LL*st[k][r].S*v;
    }
    void ins(int k,int l,int r,int pos,int u,int v)
    {
        add(k,u,v);
        if(l==r) return;
        int mid=(l+r)/2;
        if(pos<=mid) ins(k*2,l,mid,pos,u,v); else ins(k*2+1,mid+1,r,pos,u,v);
    }
    void solve(int k,int l,int r,int y,int lb,int rb)
    {
        if(lb>rb) return;
        if(!st[k].size()) return;
        if(lb==rb&&ans[ord[lb]]>=1LL*r*y) return;
        if(l==r)
        {
            for(int i=lb;i<=rb;i++) if(c[ord[i]]>=1LL*l*g[y]+1LL*f[l]*y) ans[ord[i]]=max(ans[ord[i]],1LL*l*y);
            return;
        }
        int mid=(l+r)/2;
        vector<int> lhs,rhs;
        ll res=query(k*2+1,g[y],y);
        if(res==-1)
        {
            solve(k*2,l,mid,y,lb,rb);
            return;
        }
        int lu=-1,ru=rb-lb+1;
        while(ru-lu>1)
        {
            int m=(lu+ru)/2;
            if(c[ord[lb+m]]>=res) ru=m; else lu=m;
        }
        solve(k*2,l,mid,y,lb,lb+ru-1); solve(k*2+1,mid+1,r,y,lb+ru,rb);  
    }
}seg;
bool cmp(int x,int y)
{
    return c[x]<c[y];
}
int main()
{
    scanf("%d%d%d",&n,&m,&T);
    for(int i=1;i<=n;i++) scanf("%d",&x[i]);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=m;i++) scanf("%d",&y[i]);
    for(int i=1;i<=m;i++) scanf("%d",&b[i]);
    for(int i=1;i<=100000;i++) f[i]=INF;
    for(int i=1;i<=100000;i++) g[i]=INF;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            f[x[j]-x[i]]=min(f[x[j]-x[i]],a[i]+a[j]);
     for(int i=1;i<=m;i++)
        for(int j=i+1;j<=m;j++)
            g[y[j]-y[i]]=min(g[y[j]-y[i]],b[i]+b[j]);
    for(int i=1;i<=T;i++) scanf("%lld",&c[i]);
    for(int i=1;i<=T;i++) ans[i]=0;
    for(int i=1;i<=T;i++) ord.push_back(i);
    sort(ord.begin(),ord.end(),cmp);
    for(int i=1;i<=100000;i++)
        if(f[i]!=INF) seg.ins(1,1,100000,i,i,f[i]);
    for(int i=1;i<=100000;i++) 
        if(g[i]!=INF) seg.solve(1,1,100000,i,0,T-1);
    for(int i=1;i<=T;i++) printf("%lld\n",ans[i]);
    return 0;
}
/*
3 4 20
1 3 4
3 1 2
1 3 4 7
4 2 1 2
1
5
6
7
9
10
11
12
15
16
17
22
23
28
30
35
43
47
49
57
*/