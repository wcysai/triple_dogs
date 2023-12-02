#include<bits/stdc++.h>
#define MAXN 200005
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n1,n2,m;
vector<int> G[MAXN];
vector<int> H[MAXN],rH[MAXN];
int mx[MAXN],my[MAXN];
queue<int> que;
int dx[MAXN],dy[MAXN];
vector<P> E;
bool vis[MAXN];
bool find(int u){
    for(int i=0;i<(int)G[u].size();i++){
        if(!vis[G[u][i]]&&dy[G[u][i]]==dx[u]+1){
            vis[G[u][i]]=true;
            if(!my[G[u][i]]||find(my[G[u][i]])){
                mx[u]=G[u][i];
                my[G[u][i]]=u;
                return true;
            }
        }
    }
    return false;
}
int matching(){
    for(int i=1;i<=n1+n2;i++) mx[i]=0;
    for(int i=1;i<=n1+n2;i++) my[i]=0;
    int ans=0;
    while(true){
        bool flag=false;
        while(!que.empty()) que.pop();
        for(int i=1;i<=n1+n2;i++) dx[i]=0;
        for(int i=1;i<=n1+n2;i++) dy[i]=0;
        for(int i=1;i<=n1;i++) if(!mx[i]) que.push(i);
        while(!que.empty()){
            int u=que.front();
            que.pop();
            for(int i=0;i<(int)G[u].size();i++){
                if(!dy[G[u][i]]){
                    dy[G[u][i]]=dx[u]+1;
                    if(my[G[u][i]]){
                        dx[my[G[u][i]]]=dy[G[u][i]]+1;
                        que.push(my[G[u][i]]);
                    }
                    else flag=true;
                }
            }
        }
        if(!flag) break;
        for(int i=1;i<=n1+n2;i++) vis[i]=0;
        for(int i=1;i<=n1;i++) if(!mx[i]&&find(i)) ans++;
    }
    return ans;
}
void add_edge(int u,int v){
    H[u].push_back(v);
    rH[v].push_back(u);
}
bool vs[MAXN];
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n1,&m);
        E.clear();
        n2=n1;
        for(int i=1;i<=m;i++){
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(n1+v); G[n1+v].push_back(u);
            E.push_back(P(u,n1+v));
        }
        matching();
        int s=2*n1+1,t=2*n1+2;
        for(int i=1;i<=n1;i++) if(mx[i]) add_edge(i,s); else add_edge(s,i);
        for(int i=n1+1;i<=n1+n2;i++) if(my[i]) add_edge(t,i); else add_edge(i,t);
        for(auto p:E){
            if(mx[p.F]==p.S) add_edge(p.S,p.F); else add_edge(p.F,p.S);
        }
        int l=0,r=0;
        queue<int> que;
        //left reachable from  s, right reach t
        for(int i=1;i<=n1+n2+2;i++) vs[i]=false;
        vs[s]=true; que.push(s);
        while(que.size()){
            int v=que.front(); que.pop();
            for(auto to:H[v]){
                if(!vs[to]) {vs[to]=true; que.push(to); if(to>=1&&to<=n1) l++;}
            }
        }
        for(int i=1;i<=n1+n2+2;i++) vs[i]=false;
        vs[t]=true; que.push(t);
        while(que.size()){
            int v=que.front(); que.pop();
            for(auto to:rH[v]){
                if(!vs[to]) {vs[to]=true; que.push(to); if(to>=n1+1&&to<=n1+n2) r++;}
            }
        }
        printf("%lld\n",1LL*l*r);
        for(int i=1;i<=n1+n2+2;i++) G[i].clear(),H[i].clear(),rH[i].clear();
    }
    return 0;
}
