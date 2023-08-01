#include<bits/stdc++.h>
#define pb push_back
#define F first
#define S second
using namespace std;
const int maxn=1e6+10;
typedef long long ll;
typedef pair<int,int>pi;
struct node{
    ll d,g;
};
vector<pi> G[maxn];
node dp[maxn];
ll sz[maxn],dep[maxn],ans[maxn],gg[maxn];
int n,k,cnt[maxn];
node comb(node u,node v){
    if (u.d==-1) return v;
    if (v.d==-1) return u;
    node ret;
    ret.d=min(u.d,v.d);
    ret.g=__gcd(__gcd(u.g,v.g),abs(u.d-v.d));
    return ret;
}
void dfs(int u,int fa){
    dp[u]=(node){-1,-1};
    sz[u]=cnt[u];
    for (auto e:G[u]){
        int v=e.F;
        if (v==fa) continue;
        dep[v]=dep[u]+e.S;
        dfs(v,u);
        sz[u]+=sz[v];
        node tmp=dp[v]; 
        if (tmp.d!=-1) tmp.d+=e.S;
        dp[u]=comb(dp[u],tmp);
    }
    if (cnt[u]) dp[u]=comb(dp[u],(node){0,0});
}
void dfs2(int u,int fa,node p){
    int m=G[u].size();
    vector<node> L(m,(node){-1,-1}),R(m,(node){-1,-1});
    node tot=comb(p,dp[u]);
    assert(tot.d!=-1);
    gg[u]=__gcd(tot.d,tot.g);
    for (int i=0;i<m;i++){
        pi e=G[u][i];
        int v=e.F;
        if (v==fa) continue;
        node tmp=dp[v]; 
        if (tmp.d!=-1) tmp.d+=e.S;
        L[i]=R[i]=tmp;
        ans[v]=ans[u]-sz[v]*e.S+(k-sz[v])*e.S;
    }
    for (int i=1;i<m;i++) L[i]=comb(L[i],L[i-1]);
    for (int i=m-2;i>=0;i--) R[i]=comb(R[i],R[i+1]);
    if (cnt[u]) p=comb(p,(node){0,0});
    for (int i=0;i<m;i++){
        pi e=G[u][i];
        int v=e.F;
        if (v==fa) continue;
        node tmp=p;
        if (i>0) tmp=comb(tmp,L[i-1]);
        if (i<m-1) tmp=comb(tmp,R[i+1]);
        if (tmp.d!=-1) tmp.d+=e.S;
        dfs2(v,u,tmp);
    }
}
int main(){
    scanf("%d%d",&n,&k);
    for (int i=0;i<k;i++){
        int x; scanf("%d",&x);
        cnt[x]++;
    }
    for (int i=1;i<n;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        G[u].pb((pi){v,w});
        G[v].pb((pi){u,w});
    }
    dfs(1,0);
    for (int i=1;i<=n;i++) ans[1]+=dep[i]*cnt[i];
    dfs2(1,0,(node){-1,-1});
    ll Ans=5e18;
    for (int i=1;i<=n;i++){
        if (!ans[i]) Ans=0;
        else Ans=min(Ans,ans[i]/gg[i]);
    }
    printf("%lld\n",Ans*2);
    return 0;
}