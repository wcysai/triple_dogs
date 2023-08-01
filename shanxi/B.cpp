#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 18
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
#define int long long
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,tot,a[MAXN];
vector<int> G[MAXN];
int sta[MAXLOGN+1][2*MAXN];
int fa[MAXN],vs[MAXN*2-1];
int depth[MAXN*2-1];
int id[MAXN],st[MAXN],ed[MAXN];
ll bit[MAXN];
ll sum(int i){
    int s=0;
    while(i>0){
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,ll x){
    while(i<=n){
        bit[i]+=x;
        i+=i&-i;
    }
}
void dfs(int v,int p,int d,int &k){
    id[v]=k; fa[v]=p;
    vs[k]=v; st[v]=++tot;
    depth[k++]=d;
    for(int i=0;i<(int)G[v].size();i++)
    {
        if(G[v][i]!=p)
        {
            dfs(G[v][i],v,d+1,k);
            vs[k]=v;
            depth[k++]=d;
        }
    }
    ed[v]=tot;
}
int getMin(int x, int y)
{
    return depth[x]<depth[y]?x:y;
}

void rmq_init(int n)
{
    for(int i=1;i<=n;++i) sta[0][i]=i;
    for(int i=1;1<<i<n;++i)
        for(int j=1;j+(1<<i)-1<=n;++j)
            sta[i][j]=getMin(sta[i-1][j],sta[i-1][j+(1<<(i-1))]);
}
void init(int V)
{
    int k=0;
    dfs(1,0,0,k);
    rmq_init(V*2-1);
}
int query(int l, int r)
{
    int k=31-__builtin_clz(r-l+1);
    return getMin(sta[k][l],sta[k][r-(1<<k)+1]);
}
int lca(int u,int v)
{
    if(u==v) return u;
    return vs[query(min(id[u],id[v]),max(id[u],id[v]))];
}
int dis(int u,int v)
{
    return depth[id[u]]+depth[id[v]]-2*depth[id[lca(u,v)]];
}
vector<pair<P,int> > paths[MAXN];
ll f[MAXN],g[MAXN];
ll calc_sum(int v){//calculate sum of weights on path of v to root
    return sum(st[v]);
}
void update(int v,ll cost){//add weight to edge of (v,fa[v])
    add(st[v],cost); add(ed[v]+1,-cost);
}
//f[v]: ans of subtree of v
//g[v]: ans of subtree of fa[v] excluding subtree of v
void dfs2(int v,int p){
    vector<int> son;
    for(auto to:G[v]) {
        if(to==p) continue;
        dfs2(to,v);
        son.push_back(to);
    }
    if(!son.size()) return;
    int sz=(int)son.size();
    vector<ll> dp(1<<sz,-INF),save(1<<sz,-1);
    vector<P> choices;
    for(auto q:paths[v]){
        int x=q.F.F,y=q.F.S,w=q.S,mask=0;
        if(y==v) swap(x,y);
        if(x==v){
            ll val=calc_sum(y)+w;
            val+=f[y];
            for(int i=0;i<(int)son.size();i++){
                int to=son[i];
                if(st[to]<=st[y]&&ed[to]>=ed[y]) mask|=(1<<i);
            }
            save[mask]=max(save[mask],val);
         //   printf("mask=%d val=%lld\n",mask,val);
        }
        else{
            ll val=calc_sum(x)+calc_sum(y)+w;
            val+=f[x]; val+=f[y];
            for(auto to:G[v]){
                if(to==p) continue;
                if((st[to]<=st[y]&&ed[to]>=ed[y])||(st[to]<=st[x]&&ed[to]>=ed[x])) continue;
                val+=f[to];
            }
            for(int i=0;i<(int)son.size();i++){
                int to=son[i];
                if(st[to]<=st[y]&&ed[to]>=ed[y]) mask|=(1<<i);
                if(st[to]<=st[x]&&ed[to]>=ed[x]) mask|=(1<<i);
            }
            save[mask]=max(save[mask],val);
           // printf("mask=%d val=%lld\n",mask,val);
        }
    }
    dp[0]=0;
    for(int mask=1;mask<(1<<sz);mask++){
        int id=0;
        for(int i=sz-1;i>=0;i--) if(mask&(1<<i)) {id=i; break;}
        if((save[(1<<id)]!=-1)&&(dp[mask^(1<<id)]!=-INF)) dp[mask]=max(dp[mask],dp[mask^(1<<id)]+save[(1<<id)]);
        for(int i=0;i<sz;i++)
            if((mask&(1<<i))&&(i!=id)&&(save[(1<<id)^(1<<i)]!=-1)&&(dp[mask^(1<<id)^(1<<i)]!=-INF))
                dp[mask]=max(dp[mask],dp[mask^(1<<id)^(1<<i)]+save[(1<<id)^(1<<i)]);
    }
    for(int mask=0;mask<(1<<sz);mask++)
        for(int i=0;i<sz;i++)
            if(!(mask&(1<<i))) dp[mask]+=f[son[i]];
   // for(int mask=0;mask<(1<<sz);mask++) printf("mask=%d dp=%lld\n",mask,dp[mask]);
    for(int mask=0;mask<(1<<sz);mask++){
        f[v]=max(f[v],dp[mask]);
        for(int i=0;i<sz;i++)
            if(!(mask&(1<<i))) g[son[i]]=max(g[son[i]],dp[mask]-f[son[i]]);
    }
    for(auto to:G[v]){
        if(to==p) continue;
        update(to,g[to]);
      //  printf("to=%d g[to]=%lld\n",to,g[to]);
    }
   // printf("v=%d f[v]=%lld\n",v,f[v]);
}
signed main()
{
    //freopen("input.txt","r",stdin);
    scanf("%lld%lld%lld",&n,&m,&k);
    for(int i=0;i<n-1;i++){
        int x,y;
        scanf("%lld%lld",&x,&y);
        G[x].push_back(y); G[y].push_back(x);
    }
    init(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        scanf("%lld%lld%lld",&u,&v,&w);
        paths[lca(u,v)].push_back(make_pair(P(u,v),w));
    }
    dfs2(1,0);
    printf("%lld\n",f[1]);
    return 0;
}
