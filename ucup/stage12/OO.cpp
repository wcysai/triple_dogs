#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 35
#define INF 1500000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a,b,k;
vector<int> G[MAXN];
int id[MAXN];
bool loop[MAXN];
int x[MAXN],w[MAXN],pos[(1<<10)];
int dp[(1<<10)][30][30][2];
void umax(int &x,int y) {x=max(x,y);}
void umin(int &x,int y) {x=min(x,y);}
vector<int> H[2*30*30+5];
int cnt[2*30*30+5],deg[2*30*30+5];
bool bob[2*30*30+5];
int main()
{
    scanf("%d%d%d%d",&n,&m,&a,&b); a--; b--;
    for(int i=0;i<m;i++){
        int u,v; scanf("%d%d",&u,&v);
        u--; v--;
        G[u].push_back(v);
    }
    scanf("%d",&k);
    memset(id,-1,sizeof(id));
    for(int i=0;i<k;i++){
        scanf("%d%d",&x[i],&w[i]);
        x[i]--;
        id[x[i]]=i;
    }
    for(int mask=0;mask<(1<<k);mask++)
        for(int i=0;i<k;i++)
            if(mask&(1<<i)) pos[mask]|=(1<<x[i]);
    for(int mask=1;mask<(1<<k);mask++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                dp[mask][i][j][0]=-INF;
                dp[mask][i][j][1]=INF;
            }
        for(int mask=1;mask<(1<<k);mask++){
            vector<P> v;
            memset(deg,0,sizeof(deg));
            memset(cnt,0,sizeof(cnt));
            for(int i=0;i<2*n*n;i++) H[i].clear();
            for(int i=0;i<n;i++){
                if(pos[mask]&(1<<i)) continue;
                for(int j=0;j<n;j++){
                    if(pos[mask]&(1<<j)) continue;
                    for(int turn=0;turn<2;turn++){
                        int now=turn?j:i;
                        for(auto to:G[now]){
                            if(!(pos[mask]&(1<<to))){
                                H[(1-turn)*n*n+(turn?i:to)*n+(turn?to:j)].push_back(turn*n*n+i*n+j);
                                deg[turn*n*n+i*n+j]++;
                            }
                            else{
                                if(turn){
                                    int res=dp[mask^(1<<id[to])][i][to][turn^1];
                                    if((res!=INF)&&(res!=-INF)) umin(dp[mask][i][j][turn],dp[mask^(1<<id[to])][i][to][turn^1]-w[id[to]]);
                                }
                                else{
                                    int res=dp[mask^(1<<id[to])][to][j][turn^1];
                                    if((res!=INF)&&(res!=-INF)) umax(dp[mask][i][j][turn],dp[mask^(1<<id[to])][to][j][turn^1]+w[id[to]]);
                                }
                            }
                        }
                       // printf("mask=%d pos=%d i=%d j=%d turn=%d dp=%d\n",mask,pos[mask],i,j,turn,dp[mask][i][j][turn]);
                        if(turn&&loop[j]) umin(dp[mask][i][j][turn],0);
                        if((!turn)&&loop[i]) umax(dp[mask][i][j][turn],0);
                        if(dp[mask][i][j][turn]!=INF&&dp[mask][i][j][turn]!=-INF){
                            v.push_back(P(dp[mask][i][j][turn],turn*n*n+i*n+j));
                            if(!turn) deg[turn*n*n+i*n+j]++;
                        }
                    }
                }
            }
            sort(v.begin(),v.end());
            /*printf("v=");
            for(auto x:v) printf("%d ",x.F);
            puts("");*/
            memset(bob,false,sizeof(bob));
            queue<int> que;
            for(int z=0;z<(int)v.size();z++){
                int turn=v[z].S/(n*n);
                if(!turn){
                    cnt[v[z].S]++;
                    if((cnt[v[z].S]==deg[v[z].S])&&(!bob[v[z].S])){
                        bob[v[z].S]=true; que.push(v[z].S);
                    }
                }
                else{
                    if(!bob[v[z].S]){
                        bob[v[z].S]=true;
                        que.push(v[z].S);
                    }
                }
                while(que.size()){
                    int x=que.front(); que.pop();
                    int turn=x/(n*n),i=(x-turn*n*n)/n,j=x-turn*n*n-i*n;
                    dp[mask][i][j][turn]=v[z].F;
                    //printf("mask=%d i=%d j=%d turn=%d dp=%d z=%d\n",mask,i,j,turn,v[z].F,z);
                    for(auto to:H[x]){
                        cnt[to]++;
                        if((turn)&&(cnt[to]==deg[to])&&(!bob[to])){
                            bob[to]=true; que.push(to);
                        }
                        if((!turn)&&(!bob[to])){
                            bob[to]=true; que.push(to);
                        }
                    }
                }
            }
        }
    printf("%d\n",dp[(1<<k)-1][a][b][0]);
    return 0;
}


