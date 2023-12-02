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
int T,n,m,k,a[MAXN];
vector<int> pos[MAXN];
vector<P> query[MAXN];
struct segtree{
    int lazy[4*MAXN],maxi[4*MAXN];
    void pushup(int k){
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
    }
    void add(int k,int v){
        maxi[k]+=v; lazy[k]+=v;
    }
    void pushdown(int k){
        if(!lazy[k]) return;
        for(int i=k*2;i<=k*2+1;i++) add(i,lazy[k]);
        lazy[k]=0;
    }
    void build(int k,int l,int r){
        lazy[k]=0;
        if(l==r) {maxi[k]=0;  return;}
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int x,int y){
        if(l>y||x>r) return;
        if(l>=x&&r<=y){
            add(k,1); return;
        }
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y); update(k*2+1,mid+1,r,x,y);
        pushup(k);
    }
    int query(int k,int l,int r,int x,int y){
        if(l>y||x>r) return 0;
        if(l>=x&&r<=y) return maxi[k];
        pushdown(k);
        int mid=(l+r)/2;
        return max(query(k*2,l,mid,x,y),query(k*2+1,mid+1,r,x,y));
    }
}seg;
bool has[MAXN];
vector<int> v;
int last[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m); v.clear();
        for(int i=1;i<=n;i++) {scanf("%d",&a[i]); if(!has[a[i]]) v.push_back(a[i]); has[a[i]]=true;}
        for(int i=1;i<=n;i++) pos[a[i]].push_back(i);
        for(auto x:v){
            int last=1;
            for(int j=0;j<(int)pos[x].size();j++){
                int r=pos[x][j]-1;
                if(last<=r) query[r].push_back(P(last,x));
                last=pos[x][j]+1;
            }
            if(last<=n) query[n].push_back(P(last,x));
        }
        for(int i=1;i<=m;i++){
            if(!has[i]){
                query[n].push_back(P(1,i));
                break;
            }
        }
        seg.build(1,1,n);
        for(int i=1;i<=n;i++) last[a[i]]=0;
        int ans=-1;
        for(int i=1;i<=n;i++){
            seg.update(1,1,n,last[a[i]]+1,i);
            for(auto p:query[i]){
                ans=max(ans,seg.query(1,1,n,p.F,i)-p.S);
            }
            last[a[i]]=i;
        }
        for(int i=1;i<=n;i++) pos[a[i]].clear();
        for(int i=1;i<=n;i++) has[a[i]]=false;
        for(int i=1;i<=n;i++) query[i].clear();
        printf("%d\n",ans);
    }
    return 0;
}

