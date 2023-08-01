#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double db;
typedef pair<db,int> P;
const db eps=1e-10;
int n,x,c[MAXN];
vector<int> G[MAXN];
int sum[MAXN],fa[MAXN];
vector<int> a,b,vv;
int cur[MAXN],ans[MAXN];
void dfs(int v,int p)
{
    fa[v]=p;
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v); 
        sum[v]+=c[to];
    }
}
int calc(int a,int b,db y)
{
    if((db)1.0*(a)*(b+1)<y*b*(a+1)) return 0;
    //solve (a+x)(b+x+1)=y(b+x)(a+x+1)
    db xa=y-1,xb=(y-1)*(a+b+1),xc=y*a*b+y*b-a-a*b;
    db delta=xb*xb-4*xa*xc;
    assert(delta>=0);
    db res=(-xb+sqrt(delta))/(2.0*xa);
    return (int)((ceil)(res-eps));
}
int solve(db y)
{
    int res=0;
    for(int i=0;i<(int)a.size();i++) res+=calc(a[i],b[i],y);
    return res;
}
int main()
{
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1,0);
    int now=n;
    while(now!=1)
    {
        int f=fa[now];
        a.push_back(sum[f]); b.push_back(c[now]); vv.push_back(now);
        now=f;
    }
    db lb=1.0,rb=INF;
    int sz=(int)a.size();
    for(int i=0;i<80;i++)
    {
        db mid=(lb+rb)/2.0;
        if(solve(mid)<=x) rb=mid; else lb=mid;
    }
    int res=solve(rb);
    assert(res<=x);
    priority_queue<P> pque;
    for(int i=0;i<(int)a.size();i++)
    {
        cur[i]=calc(a[i],b[i],rb);
        db slope=(1.0*(a[i]+cur[i])*(b[i]+cur[i]+1)/(b[i]+cur[i])/(a[i]+cur[i]+1));
        pque.push(P(slope,i));
    }
    for(int i=0;i<x-res;i++)
    {
        P p=pque.top(); pque.pop();
        int pos=p.S;
        cur[pos]++;
        db slope=(1.0*(a[pos]+cur[pos])*(b[pos]+cur[pos]+1)/(b[pos]+cur[pos])/(a[pos]+cur[pos]+1));
        pque.push(P(slope,pos));
    }
    for(int i=0;i<sz;i++) ans[vv[i]]=cur[i];
    for(int i=1;i<=n;i++) printf("%d%c",ans[i],i==n?'\n':' ');
    return 0;
}

