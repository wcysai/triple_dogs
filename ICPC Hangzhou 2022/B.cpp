#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 16
#define MAXS (1<<16)
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,q,w[17],c[MAXN],d[MAXN];
multiset<int> ms[MAXM][MAXS+1],rms[MAXM][MAXS+1];
struct segtree
{
    int maxi[2][4*MAXS],ans[4*MAXS];
    void pushup(int k)
    {
        maxi[0][k]=max(maxi[0][k*2],maxi[0][k*2+1]);
        maxi[1][k]=max(maxi[1][k*2],maxi[1][k*2+1]);
        ans[k]=max(maxi[0][k*2]+maxi[1][k*2+1],max(ans[k*2],ans[k*2+1]));
    } 
    void build(int k,int l,int r)
    {
        maxi[0][k]=maxi[1][k]=ans[k]=-INF;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int pos,int id,int v)
    {
        if(l==r)
        {
            maxi[id][k]=v;
            ans[k]=max(-INF,maxi[0][k]+maxi[1][k]);
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,id,v);
        else update(k*2+1,mid+1,r,pos,id,v);
        pushup(k);
    }
    pair<P,int> query(int k,int l,int r,int x,int y)
    {                                                                                                                             
        if(l>y||x>r) return make_pair(P(-INF,-INF),-INF);
        if(l>=x&&r<=y) return make_pair(P(maxi[0][k],maxi[1][k]),ans[k]);
        int mid=(l+r)/2;
        auto p=query(k*2,l,mid,x,y),q=query(k*2+1,mid+1,r,x,y);
        pair<P,int> ret;
        ret.F.F=max(p.F.F,q.F.F);
        ret.F.S=max(p.F.S,q.F.S);
        ret.S=max(p.F.F+q.F.S,max(p.S,q.S));
        return ret;
    }
}seg[16];
void init()
{
    for(int i=m-1;i>=0;i--)
    {
        int all=(1<<(i+1));
        seg[i].build(1,0,all);
        for(int j=1;j<=n;j++)
        {
            int mask=c[j]&((1<<(i+1))-1);
            ms[i][all-mask].insert(d[j]);
            seg[i].update(1,0,all,all-mask,0,*(--ms[i][all-mask].end()));
            rms[i][mask].insert(d[j]);
            seg[i].update(1,0,all,mask,1,*(--rms[i][mask].end()));
        }
    }
}
void update(ll x,ll u,ll v)
{
    for(int i=m-1;i>=0;i--)
    {
        int all=(1<<(i+1));
        int mask=c[x]&((1<<(i+1))-1);
        ms[i][all-mask].erase(ms[i][all-mask].find(d[x]));
        if(!ms[i][all-mask].size()||*(--ms[i][all-mask].end())<d[x]) 
        seg[i].update(1,0,all,all-mask,0,ms[i][all-mask].size()?*(--ms[i][all-mask].end()):-INF);
        rms[i][mask].erase(rms[i][mask].find(d[x]));
        if(!rms[i][mask].size()||*(--rms[i][mask].end())<d[x]) 
        seg[i].update(1,0,all,mask,1,rms[i][mask].size()?*(--rms[i][mask].end()):-INF);
    }
    c[x]=u; d[x]=v;
    for(int i=m-1;i>=0;i--)
    {
        int all=(1<<(i+1));
        int mask=c[x]&((1<<(i+1))-1);
        
        if(!ms[i][all-mask].size()||*(--ms[i][all-mask].end())<d[x]) 
            seg[i].update(1,0,all,all-mask,0,d[x]);
        ms[i][all-mask].insert(d[x]);
        if(!rms[i][mask].size()||*(--rms[i][mask].end())<d[x]) 
            seg[i].update(1,0,all,mask,1,d[x]);
        rms[i][mask].insert(d[x]);
        
    }
}
ll get_ans()
{
    ll ans=0;
    for(int i=m-1;i>=0;i--) 
    {
        int all=(1<<(i+1));
        ans=max(ans,1LL*seg[i].query(1,0,all,0,all).S*w[i+1]);
    }
    return ans;
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=m;i++) scanf("%d",&w[i]);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<=n;i++) scanf("%d",&d[i]);
    init();
    ll lastans=get_ans();
    printf("%lld\n",lastans);
    for(int i=0;i<q;i++)
    {
        ll x,u,v;
        scanf("%lld%lld%lld",&x,&u,&v);
        x^=lastans; u^=lastans; v^=lastans;
        update(x,u,v);
        lastans=get_ans();
        printf("%lld\n",lastans);
    }
    return 0;
}