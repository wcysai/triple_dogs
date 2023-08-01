#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,a[MAXN],ans;
struct segtree{
    int mini[4*MAXN],maxi[4*MAXN];
    void pushup(int k)
    {
        mini[k]=min(mini[k*2],mini[k*2+1]);
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r) {mini[k]=maxi[k]=a[l]; return;}
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos,int v)
    {
        if(l==r) {mini[k]=v; maxi[k]=v; return;}
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,v); else update(k*2+1,mid+1,r,pos,v);
        pushup(k);
    }
    int find_larger_right(int k,int l,int r,int pos,int v)
    {
        if(maxi[k]<v) return n+1;
        if(r<pos) return n+1;
        if(l==r) return l;
        int mid=(l+r)/2;
        int lhs=find_larger_right(k*2,l,mid,pos,v);
        if(lhs!=n+1) return lhs; else return find_larger_right(k*2+1,mid+1,r,pos,v);
    }
    int find_smaller_left(int k,int l,int r,int pos,int v)
    {
        if(mini[k]>v) return 0;
        if(l>pos) return 0;
        if(l==r) return l;
        int mid=(l+r)/2;
        int rhs=find_smaller_left(k*2+1,mid+1,r,pos,v);
        if(rhs!=0) return rhs; else return find_smaller_left(k*2,l,mid,pos,v);
    }
}seg;
bool cmp(P p,P q)
{
    return p.S>q.S;
}
void solve(int l,int r)
{
    if(l>=r) return;
    int mid=(l+r)/2;
    int x=l,y=r;
    int pivot=a[mid];
    //printf("l=%d r=%d pivot=%d\n",l,r,pivot);
    int p=-1;
    while(true)
    {
        int nx=seg.find_larger_right(1,1,n,x,pivot);
        int ny=seg.find_smaller_left(1,1,n,y,pivot);
        //printf("nx=%d ny=%d\n",nx,ny);
        if(nx>=ny) {p=ny; break;}
        int tx=a[nx],ty=a[ny];
        seg.update(1,1,n,ny,tx); seg.update(1,1,n,nx,ty);
        swap(a[nx],a[ny]);
        x=nx+1; y=ny-1;
        ans++;
    }
    solve(l,p); solve(p+1,r);
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        seg.build(1,1,n);
        ans=0;
        solve(1,n);
        printf("%d\n",ans);
    }
    return 0;
}

