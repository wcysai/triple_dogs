#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll inf=1e16;
int G[305][305];
bool vis[305];
int n,m,c[305],T;
ll w[305],d[305][305],d2[305][305],dis[305][305],ans[305][305];
void Min(ll &x,ll y){
    if (y<x) x=y;
}
int main(){
    scanf("%d",&T);
    while (T--){
        scanf("%d%d",&n,&m);
        memset(G,0,sizeof(G));
        for (int i=1;i<=n;i++) scanf("%d",&c[i]);
        for (int i=1;i<=n;i++) scanf("%lld",&w[i]);
        while (m--){
            int u,v;scanf("%d%d",&u,&v);
            G[u][v]=G[v][u]=1;
        }
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++) 
                if (!G[i][j]||c[i]!=c[j]) d[i][j]=inf; else d[i][j]=w[j];
            d[i][i]=0;
        }
        for (int k=1;k<=n;k++)
            for (int i=1;i<=n;i++)
                for (int j=1;j<=n;j++)
                    Min(d[i][j],d[i][k]+d[k][j]);
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++){
                d2[i][j]=inf;
                if (c[i]==c[j]) continue;
                for (int k=1;k<=n;k++)
                    if (G[k][j]&&c[k]!=c[j]) Min(d2[i][j],w[i]+d[i][k]+w[j]);
            }
        for (int i=1;i<=n;i++)
            for (int j=1;j<=n;j++) 
                if (i!=j) d[i][j]+=w[i];
        for (int i=1;i<=n;i++){
            memset(vis,0,sizeof(vis));
            for (int j=1;j<=n;j++) dis[i][j]=inf;
            for (int j=1;j<=n;j++) dis[i][j]=d2[i][j];
            dis[i][i]=0;
            while (1){
                int pos=-1;
                for (int j=1;j<=n;j++) if (!vis[j]){
                    if (pos==-1||dis[i][j]<dis[i][pos]) pos=j;
                }
                if (pos==-1) break;
                vis[pos]=1;
                for (int j=1;j<=n;j++)
                    Min(dis[i][j],max(dis[i][pos],d2[pos][j]));
            }
            for (int j=1;j<=n;j++){
                ans[i][j]=inf;
                for (int k=1;k<=n;k++)
                    Min(ans[i][j],max(dis[i][k],d[k][j]));
            }
        }
        for (int i=1;i<=n;i++){
            for (int j=1;j<=n;j++) printf("%lld ",ans[i][j]);
            puts("");
        }
    }
}