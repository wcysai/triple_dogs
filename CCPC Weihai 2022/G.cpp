#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll l,r,x,s[1111111];
int n;
const int B=1<<20;
ll cnt(ll m){
    return s[B]*(m/B)+s[m%B];
}
int main(){
    scanf("%lld%d",&x,&n);
    for (int i=1;i<=B;i++) s[i]=s[i-1]+(__gcd((x*i)^x,x)==1);
    while (n--){
        scanf("%lld%lld",&l,&r);
        printf("%lld\n",cnt(r)-cnt(l-1));
    }
    return 0;
}