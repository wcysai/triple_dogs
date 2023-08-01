#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef pair<P,P> PP;
int n,k,a[MAXN];
PP merge(PP x,PP y)
{
    PP ret;
    ret.F.F=(x.F.F==x.S.S?x.S.S+y.F.F:x.F.F); ret.F.S=(y.F.S==y.S.S?y.S.S+x.F.S:y.F.S);
    ret.S.F=x.S.F+y.S.F-(x.F.S+1)/2-(y.F.F+1)/2+(x.F.S+y.F.F+1)/2;
    ret.S.S=x.S.S+y.S.S;
    return ret;
}
struct segtree
{
    PP ans[4*MAXN];
    void pushup(int k)
    {
        ans[k]=merge(ans[k*2],ans[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r) {ans[k]=make_pair(P(0,0),P(0,1)); return;}
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos)
    {
        if(l==r) {ans[k]=make_pair(P(1,1),P(1,1)); return;}
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos); else update(k*2+1,mid+1,r,pos);
        pushup(k);
    }
    void print(int k,int l,int r)
    {
        printf("k=%d l=%d r=%d x=%d y=%d z=%d w=%d\n",k,l,r,ans[k].F.F,ans[k].F.S,ans[k].S.F,ans[k].S.S);
        if(l==r) return;
        int mid=(l+r)/2;
        print(k*2,l,mid); print(k*2+1,mid+1,r);
    }
}seg;
vector<P> v;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {scanf("%d",&a[i]); v.push_back(P(a[i],i));}
    sort(v.begin(),v.end(),greater<P>());
    seg.build(1,1,n);
    ll ans=0;
    for(int i=0;i<n;i++)
    {
        seg.update(1,1,n,v[i].S);
        if(i==n-1||v[i].F!=v[i+1].F)
        {
            ans+=1LL*seg.ans[1].S.F*(i==n-1?v[i].F:v[i].F-v[i+1].F);
        }
    }
    printf("%lld\n",ans);
    return 0;
}

