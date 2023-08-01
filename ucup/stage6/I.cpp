#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define MAXM 2001
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,m,k,a[MAXN];
int ax1[MAXN],ax2[MAXN],ay1[MAXN],ay2[MAXN];
int bx1[MAXN],bx2[MAXN],by1[MAXN],by2[MAXN];
vector<int> buca[MAXM][MAXM],bucb[MAXM][MAXM];
bool check(int i,int j){
    int dx1=max(ax1[i],bx1[j]),dx2=min(ax2[i],bx2[j]);
    int dy1=max(ay1[i],by1[j]),dy2=min(ay2[i],by2[j]);
    if(dx1>=dx2||dy1>dy2) return false;
    int ins=(dx2-dx1)*(dy2-dy1);
    int area=(ax2[i]-ax1[i])*(ay2[i]-ay1[i]);
    return 2*ins>=area;
}

vector<int> G[MAXN];
int mx[MAXN],my[MAXN];
queue<int> que;
int dx[MAXN],dy[MAXN];
bool vis[MAXN];
void add_edge(int u,int v){
    G[u].push_back(v);
}
bool find(int u){
    for(int i=0;i<G[u].size();i++){
        if(!vis[G[u][i]]&&dy[G[u][i]]==dx[u]+1){
            vis[G[u][i]]=true;
            if(!my[G[u][i]]||find(my[G[u][i]]))
            {
                mx[u]=G[u][i];
                my[G[u][i]]=u;
                return true;
            }
        }
    }
    return false;
}
int matching()
{
    memset(mx,0,sizeof(mx));
    memset(my,0,sizeof(my));
    int ans=0;
    while(true)
    {
        bool flag=false;
        while(!que.empty()) que.pop();
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));
        for(int i=1;i<=n;i++)
            if(!mx[i]) que.push(i);
        while(!que.empty())
        {
            int u=que.front();
            que.pop();
            for(int i=0;i<G[u].size();i++)
                if(!dy[G[u][i]])
                {
                    dy[G[u][i]]=dx[u]+1;
                    if(my[G[u][i]])
                    {
                        dx[my[G[u][i]]]=dy[G[u][i]]+1;
                        que.push(my[G[u][i]]);
                    }
                    else flag=true;
                }
        }
        if(!flag) break;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            if(!mx[i]&&find(i)) ans++;
    }
    return ans;
}
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=100000;i++) G[i].clear();
        for(int i=0;i<=2000;i++)
            for(int j=0;j<=2000;j++)
                {buca[i][j].clear(); bucb[i][j].clear();}
        for(int i=1;i<=n;i++) {
            scanf("%d%d%d%d",&ax1[i],&ay1[i],&ax2[i],&ay2[i]);
            buca[ax1[i]][ay1[i]].push_back(i);
        }
        for(int i=1;i<=m;i++) {
            scanf("%d%d%d%d",&bx1[i],&by1[i],&bx2[i],&by2[i]);
            bucb[bx1[i]][by1[i]].push_back(i);
        }
        for(int i=0;i<=2000;i++)
            for(int j=0;j<=2000;j++){
                for(auto id1:buca[i][j]){
                    for(int dx=-3;dx<=3;dx++){
                        if(i+dx<0||i+dx>2000) continue;
                        for(int dy=-3;dy<=3;dy++){
                            if(j+dy<0||j+dy>2000) continue;
                            for(auto id2:bucb[i+dx][j+dy])
                                if(check(id1,id2)) add_edge(id1,n+id2);
                        }
                    }
                }
            }
        printf("%d\n",matching());
    }
    return 0;
}

