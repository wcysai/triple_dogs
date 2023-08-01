#include<bits/stdc++.h>
#define MAXN 3005
#define MAXP 15
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k;
int w[MAXN][MAXP],p[MAXN];
int pre[MAXN][MAXN],suf[MAXN][MAXN];
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=k;i++) pre[0][i]=suf[n+1][i]=-INF;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&p[i]);
        for(int j=1;j<=p[i];j++) scanf("%d",&w[i][j]);
    }
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=k;j++)
        {
            pre[i][j]=pre[i-1][j];
            if(j>=p[i]&&pre[i-1][j-p[i]]!=-INF) pre[i][j]=max(pre[i][j],pre[i-1][j-p[i]]+w[i][p[i]]);
        }
    }
    for(int i=n;i>=1;i--)
    {
        for(int j=1;j<=k;j++)
        {
            suf[i][j]=suf[i+1][j];
            if(j>=p[i]&&suf[i+1][j-p[i]]!=-INF) suf[i][j]=max(suf[i][j],suf[i+1][j-p[i]]+w[i][p[i]]);
        }
    }
    int ans=0;
    for(int j=1;j<=k;j++) ans=max(ans,pre[n][j]);
    for(int i=1;i<=n;i++)
    {
        if(p[i]<k) //[k-pi+1,k-1]
        {
            for(int need=k-p[i]+1;need<=k-1;need++)
                for(int j=0;j<=need;j++)
                    if(pre[i-1][j]!=-INF&&suf[i+1][need-j]!=-INF) ans=max(ans,w[i][k-need]+pre[i-1][j]+suf[i+1][need-j]);
        }
        else ans=max(ans,w[i][k]);
    }
    printf("%d\n",ans);
    return 0;
}