#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 205
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
int l[MAXN],r[MAXN],len[MAXN],invlen[MAXN];
int pow_mod(int a,int i){
    int s=1;
    while(i){
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int pr(int i,int j){//calc prob that i is greater than j
    if(i<j){
        int st=max(l[i],l[j]+1)-l[j];
        int ed=min(r[j],r[j]+1)-l[j];
        if(st>ed) return 0;
        int res=(1LL*(ed-st+1)*(st+ed)/2)%MOD;
        res=1LL*res*invlen[i]%MOD*invlen[j]%MOD;
    }
    else{
        int st=max(l[i],l[j])-l[j]+1;
        int ed=min(r[j],r[j])-l[j]+1;
        if(st>ed) return 0;
        int res=(1LL*(ed-st+1)*(st+ed)/2)%MOD;
        res=1LL*res*invlen[i]%MOD*invlen[j]%MOD;
    }
}
int dp[MAXN][MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=2*n;i++) {
        scanf("%d%d",&l[i],&r[i]);
        len[i]=r[i]-l[i]+1; invlen[i]=pow_mod(len[i],MOD-2);
    }
    int ans=0;
    a
    for(int i=1;i<=2*n;i++){
        for(int j=1;j<=2*n;j+=2){
            
        }
    }
    return 0;
}

