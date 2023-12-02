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
int T,n,m,a,b,p;
int fact[MAXN],invf[MAXN],p1[MAXN],p2[MAXN],sum[MAXN];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int pow_mod(int a,int i){
    int s=1;
    while(i){
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int comb(int n,int k){
    if(n<k) return 0;
    return 1LL*fact[n]*invf[k]%MOD*invf[n-k]%MOD;
}
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=1000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[1000000]=pow_mod(fact[1000000],MOD-2);
    for(int i=999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d%d%d",&n,&m,&a,&b);
        p=1LL*a*pow_mod(b,MOD-2)%MOD;
        for(int i=1;i<=n;i++){
            sum[i]=sum[i-1];
            add(sum[i],pow_mod(i,m));
        }
        p1[0]=p2[0]=1;
        for(int i=1;i<=n;i++) p1[i]=1LL*p1[i-1]*p%MOD;
        for(int i=1;i<=n;i++) p2[i]=1LL*p2[i-1]*(MOD+1-p)%MOD;
        int ans=0;
        for(int i=1;i<=n;i++){
            add(ans,1LL*comb(n,i)*p1[i]%MOD*p2[n-i]%MOD*sum[i]%MOD);
        }
        printf("%d\n",ans);
    }
    return 0;
}

