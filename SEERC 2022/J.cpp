#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,s[MAXN],h[MAXN],t[MAXN];
int w[MAXN];
vector<pair<P,int> > dis;
struct segtree{
    int mini[4*MAXN],lazy[4*MAXN];
    P maxval[4*MAXN];
    void pushup(int k)
    {
        mini[k]=min(mini[k*2],mini[k*2+1]);
        maxval[k]=max(maxval[k*2],maxval[k*2+1]);
    }
    void add(int k,int v) {lazy[k]+=v; mini[k]+=v;}
    void build(int k,int l,int r)
    {
        if(l==r)
        {
            maxval[k]=P(w[l],l);
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void pushdown(int k)
    {
        for(int i=k*2;i<=k*2+1;i++) add(i,lazy[k]);
        lazy[k]=0;
    }
    void update(int k,int l,int r,int x,int y,int v)
    {
        if(l>y||x>r) return;
        if(l>=x&&r<=y) {add(k,v); return;}
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    void rem_val(int k,int l,int r,int pos)
    {
        if(l==r) {maxval[k]=P(0,l); return;}
        int mid=(l+r)/2;
        pushdown(k);
        if(pos<=mid) rem_val(k*2,l,mid,pos); else rem_val(k*2+1,mid+1,r,pos);
        pushup(k);
    }
    int find_right(int k,int l,int r,int pos)
    {
        if(r<pos) return -1;
        if(mini[k]>0) return -1;
        if(l==r) return l;
        pushdown(k);
        int mid=(l+r)/2;
        int x=find_right(k*2,l,mid,pos);
        if(x!=-1) return x; else return find_right(k*2+1,mid+1,r,pos);
    }
    P query(int k,int l,int r,int x,int y)
    {
        if(l>y||x>r) return P(0,0);
        if(l>=x&&r<=y) return maxval[k];
        int mid=(l+r)/2;
        pushdown(k);
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) {scanf("%d",&s[i]); dis.push_back(make_pair(P(s[i],0),i));}
    for(int i=1;i<=m;i++) {scanf("%d%d",&h[i],&t[i]); dis.push_back(make_pair(P(h[i],1),i));}
    sort(dis.begin(),dis.end());
    for(int i=0;i<(int)dis.size();i++)
    {
        if(dis[i].F.S) {h[dis[i].S]=i+1; w[i+1]=t[dis[i].S];}
        else s[dis[i].S]=i+1;
    }
    seg.build(1,1,n+m);
    ll ans=0;
    for(int i=1;i<=n;i++)
    {
        //match to left
        P p=seg.query(1,1,n+m,1,s[i]);
        //match to right
        int pos=seg.find_right(1,1,n+m,s[i]);
        if(pos==-1) pos=n+m;
        P q=seg.query(1,1,n+m,s[i],pos);
        if(!p.F&&!q.F);
        else if(p.F>q.F)
        {
            ans+=p.F;
            assert(p.F&&s[i]>=p.S);
            seg.update(1,1,n+m,p.S,s[i]-1,1);
            seg.rem_val(1,1,n+m,p.S);
        }
        else
        {
            assert(q.F&&q.S>=s[i]);
            ans+=q.F;
            seg.update(1,1,n+m,s[i],q.S-1,-1);
            seg.rem_val(1,1,n+m,q.S);
        }
        printf("%lld%c",ans,i==n?'\n':' ');
    }
    return 0;
}

