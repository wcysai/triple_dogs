#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define MAXW 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,W,k,a[MAXN];
ll dp[MAXN],ndp[MAXN];
ll sum[MAXN];
vector<P> items;
ll ans=0;
void upd(ll &a,ll b) {a=max(a,b);}
int main()
{
    scanf("%d%d%d",&n,&W,&k);
    for(int i=1;i<=n;i++){
        int w,v;
        scanf("%d%d",&w,&v);
        items.push_back(P(v,w));
    }
    sort(items.begin(),items.end());
    sum[n]=0;
    for(int i=n-1;i>=0;i--) sum[i]=sum[i+1]+items[i].F;
    ans=sum[n-k];
    printf("%lld\n",ans);
    for(int i=0;i<n;i++){
        memset(ndp,0,sizeof(dp));
        for(int j=0;j<=W;j++){
            upd(ndp[j],dp[j]);
            if(j+items[i].S<=W) upd(ndp[j+items[i].S],dp[j]+items[i].F);
        }
        swap(dp,ndp);
        for(int j=0;j<=W;j++) {
            printf("i=%d j=%d dp=%lld\n",i,j,dp[j]);
            upd(ans,dp[j]+sum[max(i+1,n-k)]);
        }
    }
    printf("%lld\n",ans);
    return 0;
}

