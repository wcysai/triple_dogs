#include<bits/stdc++.h>
#define MAXN 5005
#define INF 1000000000000000000LL
using namespace std;
typedef long long ll;
ll w[MAXN][MAXN],f[MAXN][MAXN];
int p[MAXN][MAXN];
int T,n,m;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
	    for(int i=0;i<=n+2;i++)
            for(int j=0;j<=n+2;j++)
                w[i][j]=p[i][j]=0,f[i][j]=INF;
        f[0][0]=0;
        for(int i=1;i<=m;i++){
            int l,r,v;
            scanf("%d%d%d",&l,&r,&v);
            l++; r++;
            w[l][r]-=v;
        }
	    for(int i=n+1;i;i--)
            for(int j=i+2;j<=n+1;j++)
                w[i][j]+=w[i+1][j]+w[i][j-1]-w[i+1][j-1];
	    for(int i=1;i<=n;++i)
            for(int j=n+1;j;--j){
		    int l=p[i-1][j],r=min(j==n+1?MAXN-1:p[i][j+1],j-1);
		    for(int k=l;k<=r;++k) if(f[i-1][k]+w[k+1][j]<f[i][j]) f[i][j]=f[i-1][k]+w[k+1][j],p[i][j]=k;
            printf("i=%d j=%d l=%d r=%d f=%lld\n",i,j,l,r,f[i][j]);
        }
        for(int i=1;i<=n;i++) printf("%lld%c",-f[n+1-i][n+1],i==n?'\n':' ');
    }
    return 0;
}
