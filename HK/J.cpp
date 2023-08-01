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
int T,n,k,a[MAXN];
vector<int> G[MAXN];
int dp[MAXN];
void dfs(int v){
    dp[v]=1;
    if(!G[v].size()) return;
    vector<int> vv;
    for(auto to:G[v]){
        dfs(to); vv.push_back(dp[to]);
    }
    sort(vv.begin(),vv.end());
    int sz=(int)vv.size();
    if(vv.size()==1) dp[v]=vv[sz-1];
    else dp[v]=max(vv[sz-1],vv[sz-2]+1);
}
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=0;i<=n;i++) G[i].clear();
        for(int i=1;i<=n;i++){
            int p; scanf("%d",&p);
            G[p].push_back(i);
        }
        dfs(0);
        printf("%d\n",dp[0]);
    }
    return 0;
}

