#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 10000005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,fact[MAXN],invf[MAXN];
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
int main()
{
    fact[0]=invf[0]=1;
    for(int i=1;i<=10000000;i++) fact[i]=1LL*fact[i-1]*i%MOD;
    invf[10000000]=pow_mod(fact[10000000],MOD-2);
    for(int i=9999999;i>=1;i--) invf[i]=1LL*invf[i+1]*(i+1)%MOD;
    scanf("%d",&n);
    int ans=0;
    for(int i=1;i<=n;i++){
        int num=n-i;
        if(num>=i-1) add(ans,1LL*fact[n-i]*invf[n-2*i+1]%MOD*fact[n-i]%MOD);
    }
    printf("%d\n",ans);
    return 0;
}

