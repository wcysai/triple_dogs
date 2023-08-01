#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
using namespace std;
typedef long double db;
int n,i,k;
db pow_(db x,int i)
{
    db s=1.0;
    while(i)
    {
        if(i&1) s=s*x;
        x=x*x;
        i>>=1;
    }
    return s;
}
int main()
{
    scanf("%d%d%d",&n,&i,&k);
    db ans=0.0;
    for(int j=1;j<=n;j++)
    {
        db p=pow_((db)1.0*(j)/n,k)-pow_((db)1.0*(j-1)/n,k);
        if(j>=i) ans+=p*(1.0+j)/2.0; else ans+=p*i;
    }
    printf("%.15Lf\n",ans);
    return 0;
}