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
int T,n,k,h[MAXN],a[MAXN],b[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&h[i]);
        h[n+1]=0;
        a[0]=b[0]=0;
        ll ans=0;
        for(int i=1;i<=n;i++){
            int x=a[i-1],y=(i==1?0:b[i-2]);
            int maxi;
            if(x+y>h[i]) maxi=min(h[i],max(h[i]-y,min(x,max(0,h[i+1]-b[i-1])))); else maxi=max(x,min(h[i]-y,max(0,h[i+1]-b[i-1])));
            a[i]=maxi; b[i]=h[i]-maxi;
            if(a[i]>=x) ans+=a[i]-x;
            if(b[i]>=y) ans+=b[i]-y;
            //printf("%d %d %d\n",i,a[i],b[i]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

