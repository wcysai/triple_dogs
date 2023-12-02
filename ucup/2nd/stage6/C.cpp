#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXLOGN 20
#define INF 1000000000
#define MOD 1000000007
#define INV 500000004
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int tot,q,n,k;
int vs[MAXN*2-1],depth[MAXN*2-1],id[MAXN];
int pa[MAXN],dep[MAXN],sz[MAXN],wson[MAXN],top[MAXN],spos[MAXN],tpos[MAXN];
int st[MAXLOGN+1][4*MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
struct segtree
{
    int sum[4*MAXN],lazy[4*MAXN];
    void pushup(int k){
        sum[k]=sum[k*2];
        add(sum[k],sum[k*2+1]);
    }
    void mult(int k,int v){
        sum[k]=1LL*sum[k]*v%MOD;
        lazy[k]=1LL*lazy[k]*v%MOD;
    }
    void pushdown(int k){
        if(lazy[k]==1) return;
        for(int i=k*2;i<=k*2+1;i++){
            mult(i,lazy[k]);
        }
        lazy[k]=1;
    }
    void build(int k,int l,int r){
        lazy[k]=1;
        if(l==r){
            sum[k]=1;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid);build(k*2+1,mid+1,r);
        pushup(k);
    }      
    void update(int k,int l,int r,int x,int y,int v){
        if(l>y||x>r) return;
        if(l>=x&&r<=y) {mult(k,v); return;}
        pushdown(k);
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
}seg[2];
vector<int> G[MAXN];
void dfs1(int v,int p,int d,int &k){
    dep[v]=d;pa[v]=p;sz[v]=1; id[v]=k; vs[k]=v; depth[k++]=d;
    for(int i=0;i<(int)G[v].size();i++){
        int to=G[v][i];
        if(to==p) continue;
        dfs1(to,v,d+1,k);
        vs[k]=v; depth[k++]=d;
        if(sz[to]>sz[wson[v]]) wson[v]=to;
        sz[v]+=sz[to];
    }
}
int getMin(int x,int y){
    return depth[x]<depth[y]?x:y;
}
void rmq_init(int n){
    for(int i=1;i<=n;i++) st[0][i]=i;
    for(int i=1;1<<i<n;i++)
        for(int j=1;j+(1<<i)-1<=n;++j)
            st[i][j]=getMin(st[i-1][j],st[i-1][j+(1<<(i-1))]);
}
void dfs2(int v,int p,int num){
    top[v]=num;
    spos[v]=++tot;
    tpos[tot]=v;
    if(wson[v]) dfs2(wson[v],v,num);
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==p||to==wson[v]) continue;
        dfs2(to,v,to);
    }
}
void init(){
    tot=0;
    dfs1(1,1,1,k);
    dfs2(1,0,1);
    rmq_init(n*2-1);
    seg[0].build(1,1,n); seg[1].build(1,1,n);
}
int query(int l,int r){
    int k=31-__builtin_clz(r-l+1);
    return getMin(st[k][l],st[k][r-(1<<k)+1]);
}
int lca(int u,int v){
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
void upd(int u,int v,int val,int id){
    int res=0;
    while(top[u]!=top[v]){
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        seg[id].update(1,1,n,spos[top[u]],spos[u],val);
        u=pa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    seg[id].update(1,1,n,spos[v],spos[u],val);
}
multiset<P> s;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n-1;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    init();
    scanf("%d",&q);
    for(int i=1;i<=q;i++){
        string str;
        int u,v;
        cin>>str;
        scanf("%d%d",&u,&v);
        if(str[0]=='+'){
            s.insert(P(u,v));
            int l=lca(u,v);
            upd(u,v,2,0);
            upd(u,v,2,1);
            upd(l,l,INV,1);
        }
        else{
            s.erase(s.find(P(u,v)));
            int l=lca(u,v);
            upd(u,v,INV,0);
            upd(u,v,INV,1);
            upd(l,l,2,1);
        }
        int x=seg[0].sum[1],y=seg[1].sum[1];
        dec(x,y);
        printf("%d\n",x);
    }
    return 0;
}

