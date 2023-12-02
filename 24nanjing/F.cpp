#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define int long long
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,a[MAXN];
int q,f[MAXN],g[MAXN];
struct segtree{
    int len[4*MAXN];
    ll sum[4*MAXN],lazy[4*MAXN],maxi[4*MAXN],mini[4*MAXN];
    void pushup(int k){
        sum[k]=sum[k*2]+sum[k*2+1];
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
        mini[k]=min(mini[k*2],mini[k*2+1]);
    }
    void st(int k,int v){
        sum[k]=1LL*len[k]*v; maxi[k]=mini[k]=v; lazy[k]=v;
    }
    void pushdown(int k){
        if(!lazy[k]) return;
        for(int i=k*2;i<=k*2+1;i++) st(i,lazy[k]);
        lazy[k]=0;
    }
    void build(int k,int l,int r,int type){
        lazy[k]=0; len[k]=r-l+1;
        if(l==r){
            maxi[k]=mini[k]=sum[k]=(type==0?f[l]:(type==1?g[l]:a[l]));
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid,type); build(k*2+1,mid+1,r,type);
        pushup(k);
    }
    void update(int k,int l,int r,int x,int y,ll v){
        if(l>y||x>r) return;
        if(l>=x&&r<=y){
            st(k,v); return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    ll query_sum(int k,int l,int r,int x,ll y){
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return sum[k];
        pushdown(k);
        int mid=(l+r)/2;
        return query_sum(k*2,l,mid,x,y)+query_sum(k*2+1,mid+1,r,x,y);
    }
}segf,segg,sega;
int find_pos(int k,int l,int r){//find first position that f>=g
    if(l==r) return l;
    segf.pushdown(k); segg.pushdown(k);
    int mid=(l+r)/2;
    if(segf.maxi[k*2]>=segg.mini[k*2]) return find_pos(k*2,l,mid); else return find_pos(k*2+1,mid+1,r);
}
int find_f(int k,int l,int r,ll v){//find first_position that>v
    if(l==r){
        if(sega.maxi[k]>v) return l; else return l+1;
    }
    sega.pushdown(k); 
    int mid=(l+r)/2;
    if(sega.maxi[k*2]>v) return find_f(k*2,l,mid,v); else return find_f(k*2+1,mid+1,r,v);
}
int find_g(int k,int l,int r,ll v){//find last_position that>v
    if(l==r){
        if(sega.maxi[k]>v) return l; else return l-1;
    }
    sega.pushdown(k); 
    int mid=(l+r)/2;
    if(sega.maxi[k*2+1]>v) return find_g(k*2+1,mid+1,r,v); else return find_g(k*2,l,mid,v);
}
signed main()
{
    scanf("%lld",&T);
    while(T--){
        scanf("%lld",&n);
        ll ans=0;
        for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
        for(int i=1;i<=n;i++) f[i]=max(f[i-1],a[i]);
        g[n+1]=0;
        for(int i=n;i>=1;i--) g[i]=max(g[i+1],a[i]);
        ll s=0;
        for(int i=1;i<=n;i++) s+=a[i];
        segf.build(1,1,n,0); segg.build(1,1,n,1); sega.build(1,1,n,2);
        scanf("%lld",&q);
        while(q--){
            int pos,v;
            scanf("%lld%lld",&pos,&v);
            a[pos]+=v; s+=v;
            sega.update(1,1,n,pos,pos,a[pos]);
            int r=find_f(1,1,n,a[pos]);
            if(r>pos) segf.update(1,1,n,pos,r-1,a[pos]);
            int l=find_g(1,1,n,a[pos]);
            if(l<pos) segg.update(1,1,n,l+1,pos,a[pos]);
            pos=find_pos(1,1,n);
            ll res=segf.query_sum(1,1,n,1,pos-1)+segg.query_sum(1,1,n,pos,n);
            printf("%lld\n",res-s);
        }
    }
    return 0;
}

