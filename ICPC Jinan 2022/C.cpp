#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
int dp[MAXN][MAXN];
int way[MAXN][MAXN];
int agg[MAXN][MAXN];
int ans[MAXN][MAXN];
int sz[MAXN],cnt[MAXN];
vector<int> G[MAXN];
int fact[MAXN],invf[MAXN],all;
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void add_item(int v,int maxi)
{
    for(int i=maxi;i>=1;i--)
        for(int j=maxi;j>=v;j--)
            add(dp[i][j],dp[i-1][j-v]);
}
void dec_item(int v,int maxi)
{
    for(int i=1;i<=maxi;i++)
        for(int j=v;j<=maxi;j++)
            dec(dp[i][j],dp[i-1][j-v]);
}
int pow_mod(int a,int i)
{
    int s=1;
    while(i)
    {
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
void dfs(int v,int p)
{
    sz[v]=1; 
    for(auto to:G[v])
    {
        if(to==p) continue;
        dfs(to,v);
        sz[v]+=sz[to]; cnt[v]++;
    }
    for(int i=0;i<=cnt[v];i++)
        for(int j=0;j<=sz[v];j++)
            dp[i][j]=0;
    dp[0][0]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        add_item(sz[to],sz[v]-1);
    }
    for(auto to:G[v])
    {
        if(to==p) continue;
        dec_item(sz[to],sz[v]-1);
        for(int i=1;i<=cnt[v];i++)
            for(int j=0;j<=sz[v]-sz[to]-1;j++)
                add(way[to][j],1LL*fact[i-1]*fact[cnt[v]-i]%MOD*dp[i-1][j]%MOD);
        add_item(sz[to],sz[v]-1);
    }
    all=1LL*all*fact[cnt[v]]%MOD;
}
void solve(int v,int p,int res,int d)
{
    for(int i=d+1;i<=n;i++) 
        ans[v][i]=1LL*res*agg[v][i-d-1]%MOD;
    for(auto to:G[v])
    {
        if(to==p) continue;
        for(int i=0;i<=sz[v]-sz[to]-1;i++)
            for(int j=0;j<=n-sz[v];j++)
                add(agg[to][i+j],1LL*way[to][i]*agg[v][j]%MOD);
        solve(to,v,1LL*res*invf[cnt[v]]%MOD,d+1);
    }
}
int main()
{
    fact[0]=1;
    for(int i=1;i<=500;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[500]=pow_mod(fact[500],MOD-2);
    for(int i=499;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&n);
    for(int i=0;i<n-1;i++)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    all=1;
    dfs(1,0);
    agg[1][0]=1;
    solve(1,0,all,0);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            printf("%d%c",ans[i][j],j==n?'\n':' ');
    return 0;
}

