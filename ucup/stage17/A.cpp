#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
vector<int> G[MAXN];
bool vis[MAXN];
vector<int> vv;
void dfs(int v){
    vis[v]=true; vv.push_back(v);  
    for(auto to:G[v]){
        if(!vis[to]) dfs(to);
    }
}
int main()
{
    scanf("%d",&n);
    bool f=false;
    for(int i=0;i<2*n-2;i++){
        int u,v; scanf("%d%d",&u,&v);
        if(u==v) f=true;
        if(u>v) swap(u,v);
        G[u].push_back(n+v); G[n+v].push_back(u);
    }
    if(f) {puts("0"); return 0;}
    int ans=1;
    for(int i=1;i<=2*n;i++){
        if(i==n+1||i==n) continue;
        if(!vis[i]){
            vv.clear();
            dfs(i);
            int e=0;
            for(auto x:vv) e+=(int)G[x].size();
            e/=2;
            if(e==(int)vv.size()) ans=2LL*ans%MOD; else ans=0;
        }
    }
    printf("%d\n",ans);
    return 0;
}

