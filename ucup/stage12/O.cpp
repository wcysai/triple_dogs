#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 35
#define INF 1000000005
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
int dp[(1<<10)][2*30*30];
void umax(int &x,int y) {x=max(x,y);}
void umin(int &x,int y) {x=min(x,y);}
vector<int> H[2*30*30+5],revH[2*30*30+5];
int deg[2*30*30+5];
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
                dp[mask][i*n+j]=dp[mask][n*n+i*n+j]=-INF;
            }
        for(int mask=1;mask<(1<<k);mask++){
            vector<P> v;
            memset(deg,0,sizeof(deg));
            for(int i=0;i<2*n*n;i++) H[i].clear(),revH[i].clear();
            set<P> s;
            for(int i=0;i<n;i++){
                if(pos[mask]&(1<<i)) continue;
                for(int j=0;j<n;j++){
                    if(pos[mask]&(1<<j)) continue;
                    for(int turn=0;turn<2;turn++){
                        int now=turn?j:i,cur=turn*n*n+i*n+j;
                        for(auto to:G[now]){
                            int ncur=(1-turn)*n*n+(turn?i:to)*n+(turn?to:j);
                            if(!(pos[mask]&(1<<to))){
                                //printf("add edge turn=%d i=%d j=%d nturn=%d ni=%d nj=%d\n",turn,i,j,1-turn,turn?i:to,turn?to:j);
                                H[cur].push_back(ncur); revH[ncur].push_back(cur);
                                deg[cur]++;
                            }
                            else{
                                umax(dp[mask][cur],w[id[to]]-dp[mask^(1<<id[to])][ncur]);
                            }
                        }
                    }
                }
            }
            queue<int> que;
            for(int i=0;i<n;i++){
                if(pos[mask]&(1<<i)) continue;
                for(int j=0;j<n;j++){
                    if(pos[mask]&(1<<j)) continue;
                    for(int turn=0;turn<2;turn++){
                        int cur=turn*n*n+i*n+j;
                        s.insert(P(dp[mask][cur],cur));
                        if(!deg[cur]) que.push(cur);
                    }
                }
            }
            while(true){
                if(que.size()){
                    int cur=que.front(); que.pop();
                    int turn=cur/(n*n),i=(cur-turn*n*n)/n,j=cur-turn*n*n-i*n;
                    //printf("que mask=%d i=%d j=%d turn=%d dp=%d\n",mask,i,j,turn,dp[mask][cur]);
                    s.erase(P(dp[mask][cur],cur)); 
                    for(auto to:revH[cur]){
                        if(-dp[mask][cur]>dp[mask][to]){
                            s.erase(P(dp[mask][to],to));
                            umax(dp[mask][to],-dp[mask][cur]);
                            s.insert(P(dp[mask][to],to));
                        }
                        int nturn=to/(n*n),ni=(to-nturn*n*n)/n,nj=to-nturn*n*n-ni*n;
                        //printf("nturn=%d ni%d nj=%d deg=%d\n",nturn,ni,nj,deg[to]);
                        deg[to]--; if(!deg[to]) que.push(to); 
                    }
                    continue;
                }
                if(s.size()&&(((--s.end())->F)>0)){
                    auto it=(--s.end());
                    int cur=it->S; deg[cur]=0; s.erase(it);
                    int turn=cur/(n*n),i=(cur-turn*n*n)/n,j=cur-turn*n*n-i*n;
                    //printf("s mask=%d i=%d j=%d turn=%d dp=%d\n",mask,i,j,turn,dp[mask][cur]);
                    for(auto to:revH[cur]){
                        if(-dp[mask][cur]>dp[mask][to]){
                            s.erase(P(dp[mask][to],to));
                            umax(dp[mask][to],-dp[mask][cur]);
                            s.insert(P(dp[mask][to],to));
                        }
                        int nturn=to/(n*n),ni=(to-nturn*n*n)/n,nj=to-nturn*n*n-ni*n;
                        //printf("nturn=%d ni%d nj=%d deg=%d\n",nturn,ni,nj,deg[to]);
                        deg[to]--; if(!deg[to]) que.push(to); 
                    }
                    continue;
                }
                break;
            }
            for(int i=0;i<n;i++){
                if(pos[mask]&(1<<i)) continue;
                for(int j=0;j<n;j++){
                    if(pos[mask]&(1<<j)) continue;
                    for(int turn=0;turn<2;turn++){
                        int cur=turn*n*n+i*n+j;
                        if(deg[cur]>0) {assert(dp[mask][cur]<=0); dp[mask][cur]=0;}
                    }
                }
            }
        }
    printf("%d\n",dp[(1<<k)-1][a*n+b]);
    return 0;
}

