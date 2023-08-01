#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int f(ll x){
    if (x==-1) return 0;
    if (!x) return 1;
    if (x%3) return f(x-1)+1;
    return f(x/3)+1;
}
int solve(ll l,ll r){
    ll p=1;
    int ret=0;
    while (p<=r+1){
        ll x=(r+1)/p*p-1;
        if (x<l) break;
        ret=max(ret,f(x));
        p=p*3;
    }
    return ret;
}
int main(){
    int T; scanf("%d",&T);
    while (T--){
        long long l,r;
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",solve(l,r));
    }
    return 0;
}