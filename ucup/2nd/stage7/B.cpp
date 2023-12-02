#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 200000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
bool check(ll x){
    ll sum=0;
    for(int i=1;i<=n;i++){
        sum+=min(1LL*a[i],x);
    }
    if(sum>=k*x) return true; else return false;
}
int main()
{
    scanf("%d%d",&n,&k);
    ll s=0;
    for(int i=1;i<=n;i++) {scanf("%d",&a[i]); s+=a[i];}
    ll l=0,r=s/k+5;
    while(r-l>1){
        ll mid=(l+r)/2;
        if(check(mid)) l=mid; else r=mid;
    }
    printf("%lld\n",l);
    return 0;
}

