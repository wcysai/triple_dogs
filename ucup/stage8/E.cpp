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
typedef long double db;
int n,k,a[MAXN];
db b[MAXN];
int ans[MAXN];
db c[MAXN];
bool check(){
    ll sum=0;
    for(int i=1;i<=n;i++) 
    {
        if(ans[i]<1||ans[i]>10000) return false;
        sum+=ans[i]*ans[i];
    }
    db z=sqrt((db)sum);
    for(int i=1;i<=n;i++){
        c[i]=(db)1.0*ans[i]/z;
        if(abs(b[i]-c[i])>1e-6) return false;
    }
    return true;
}
void go(){
    int g=0;
    for(int i=1;i<=n;i++) g=__gcd(ans[i],g);
    for(int i=1;i<=n;i++) ans[i]/=g;
    for(int i=1;i<=n;i++) printf("%d\n",ans[i]);
    exit(0);
}
int main()
{
    scanf("%d",&n);
    db s=0.0;
    for(int i=1;i<=n;i++){ 
        scanf("%Lf",&b[i]);
    }
    for(int i=1;i<=10000;i++) {
        ans[1]=i;
        for(int j=2;j<=n;j++){
            ans[j]=(int)(b[j]*ans[1]/b[1]+0.5);
        }
        if(check()) go();
    }
    return 0;
}

