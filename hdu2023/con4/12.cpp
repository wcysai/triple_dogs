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
int T,n,k,a[MAXN],b[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        ll ans=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&a[i],&b[i]);
            ans-=b[i];
            a[i]+=b[i];
        }
        sort(a+1,a+n+1,greater<int>());
        for(int i=1;i<=n;i++){
            if(i&1) ans+=a[i]; 
        }
        printf("%lld\n",ans);
    }
    return 0;
}

