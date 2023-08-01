#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
vector<int> G[MAXN];
int dp[MAXN][2];
void dfs(int v,int p){
    if(G[v].size()==1&&v!=1){
        dp[v][0]=a[v]; dp[v][1]=1-a[v];
        return;
    }
    dp[v][0]=0; dp[v][1]=-INF;
    for(auto to:G[v]){
        if(to==p) continue;
        dfs(to,v);
        int x=max(dp[to][0]+dp[v][0],dp[to][1]+dp[v][1]);
        int y=max(dp[to][1]+dp[v][0],dp[to][0]+dp[v][1]);
        dp[v][0]=x; dp[v][1]=y;
    }
    dp[v][1-a[v]]++;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<n-1;i++){
        int u,v; scanf("%d%d",&u,&v);
        G[u].push_back(v); G[v].push_back(u);
    }
    dfs(1,0);
    printf("%d\n",max(dp[1][0],dp[1][1]));
    return 0;
}

