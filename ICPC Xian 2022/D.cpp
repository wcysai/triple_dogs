#include<bits/stdc++.h>
#define MAXN 100005
#define MAXLOGN 18
#define MAXM 5
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,q;
int a[MAXM][MAXN],r[MAXM][MAXN];
int st[MAXLOGN][MAXM][MAXN],suf[MAXLOGN][MAXM][MAXM][MAXN];
int pos[MAXM],tmp[MAXM];
//st[i][j][k]: in j-th perm after 2^i operation suffix starting from k
//st[i][j+1][k]=max_{t=0}^{m} max_{l=1}^n suf[st[t][j][k]]
int solve(int x,int y)
{
    int ans=1;
    for(int i=0;i<m;i++) {pos[i]=r[i][x]; if(r[i][y]>=pos[i]) return 1;}
    for(int i=17;i>=0;i--)
    {
        for(int j=0;j<m;j++) tmp[j]=INF;
        for(int j=0;j<m;j++)
        {
            for(int t=0;t<m;t++) tmp[t]=min(tmp[t],suf[i][j][t][pos[j]]);
        }
        bool f=false;
        for(int t=0;t<m;t++) if(r[t][y]>=tmp[t]) f=true;
        if(i==17&&(!f)) return -1;
        if(!f)
        {
            ans+=(1<<i);
            swap(tmp,pos);
        }
    }
    return ans+1;
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
        for(int j=1;j<=n;j++)
        {
            scanf("%d",&a[i][j]);
            r[i][a[i][j]]=j;
            st[0][i][a[i][j]]=j;
            //printf("i=%d j=%d k=%d st=%d\n",0,i,a[i][j],st[0][i][a[i][j]]);
        }
    for(int i=0;i<=17;i++)
    {
        for(int j=0;j<m;j++)
            for(int k=0;k<m;k++)
                for(int l=n;l>=1;l--)
                {
                    if(l==n) suf[i][j][k][l]=st[i][k][a[j][l]];
                    else suf[i][j][k][l]=min(suf[i][j][k][l+1],st[i][k][a[j][l]]);
                }
        if(i==17) break;
        for(int j=0;j<m;j++)
        {
            for(int k=1;k<=n;k++)
            {
                st[i+1][j][k]=st[i][j][k];
                for(int t=0;t<m;t++)
                    st[i+1][j][k]=min(st[i+1][j][k],suf[i][t][j][st[i][t][k]]);
                //printf("i=%d j=%d k=%d st=%d\n",i+1,j,k,st[i+1][j][k]);
            }
        }
    }
    scanf("%d",&q);
    while(q--)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",solve(x,y));
    }
    return 0;
}