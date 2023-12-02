#include<bits/stdc++.h>
#define MAXN 205
#define MAXM 205
#define MAXV 40005
#define inf 1000000000
#define INF 1000000000000000000LL
#define F first
#define S second
#define int long long
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
struct edge{int to,cap; ll cost; int rev,id;};
int T,n,m,k,V;
ll h[MAXV],dist[MAXV],ans;
int s,t,prevv[MAXV],preve[MAXV];
vector<edge> G[MAXV];
vector<P> H[MAXV],GG[MAXV];
int a[MAXN][MAXM],b[MAXN][MAXM];
bool inque[MAXV];
void add_edge(int from,int to,int cap,int cost){
    G[from].push_back((edge){to,cap,cost,(int)G[to].size(),1});
    G[to].push_back((edge){from,0,-cost,(int)G[from].size()-1,0});
    GG[from].push_back(P(to,cost));
    //GG[to].push_back(P(from,cost));
}
void dijkstra(int s){
    priority_queue<P,vector<P>,greater<P> >que;
    fill(dist+1,dist+V+1,INF);
    dist[s]=0;
    que.push(P(0,s));
    while(!que.empty()){
        P p=que.top(); que.pop();
        int v=p.S;
        if(dist[v]<p.F) continue;
        for(int i=0;i<G[v].size();i++){
            edge &e=G[v][i];
            if(e.cap>0&&dist[e.to]>dist[v]+e.cost+h[v]-h[e.to]){
                dist[e.to]=dist[v]+e.cost+h[v]-h[e.to];
                prevv[e.to]=v;
                preve[e.to]=i;
                que.push(P(dist[e.to],e.to));
            }
        }
    }
}
void spfa(int s){
    queue<int>que;
    fill(h+1,h+V+1,INF);
    fill(inque+1,inque+V+1,false);
    h[s]=0;
    que.push(s);
    while(!que.empty()){
        int u=que.front(); que.pop();
        for(int i=0;i<(int)G[u].size();i++){
            if(G[u][i].cap>0&&h[u]+G[u][i].cost<h[G[u][i].to]){
                h[G[u][i].to]=h[u]+G[u][i].cost;
                prevv[G[u][i].to]=u;
                preve[G[u][i].to]=i;
                if(!inque[G[u][i].to]){
                    inque[G[u][i].to]=true;
                    que.push(G[u][i].to);
                }
            }
        }
        inque[u]=false;
    }
}
ll min_cost_flow(int s,int t){
    ll res=0;
    spfa(s);
    while(true){
        dijkstra(s);
        if(dist[t]==INF) return res;
        if(h[t]+dist[t]>=0) return res;
        for(int v=1;v<=V;v++) h[v]+=dist[v];
        int d=V;
        for(int v=t;v!=s;v=prevv[v]){
            d=min(d,G[prevv[v]][preve[v]].cap);
        }
        res+=d*h[t];
        for(int v=t;v!=s;v=prevv[v]){
            edge &e=G[prevv[v]][preve[v]];
            e.cap-=d;
            G[v][e.rev].cap+=d;
        }
    }
}
void add_cons(int u,int v,int c){//f_v-f_u<=c
    //printf("cons %d %d %d\n",u,v,c);
    H[u].push_back(P(v,c));
}
int f[MAXV];
void spfa2(int s){
    queue<int>que;
    fill(f+1,f+V+1,inf);
    fill(inque+1,inque+V+1,false);
    f[s]=0;
    que.push(s);
    while(!que.empty()){
        int u=que.front(); que.pop();
        //printf("u=%d\n",u);
        for(auto p:H[u]){
            int to=p.F,cost=p.S;
            if(f[to]>f[u]+cost){
                f[to]=f[u]+cost;
                if(!inque[to]){
                    inque[to]=true;
                    que.push(to);
                }
            }
        }
        inque[u]=false;
    }
}
void spfa3(int s){
    queue<int>que;
    fill(f+1,f+V+1,INF);
    fill(inque+1,inque+V+1,false);
    f[s]=0;
    que.push(s);
    while(!que.empty()){
        int u=que.front(); que.pop();
        for(auto p:GG[u]){
            int to=p.F,cost=p.S;
            if(f[to]>f[u]+cost){
                f[to]=f[u]+cost;
                if(!inque[to]){
                    inque[to]=true;
                    que.push(to);
                }
            }
        }
        inque[u]=false;
    }
}
int get_id(int x,int y){
    return (x-1)*m+y;
}
//int sum[MAXV][MAXV];

void construct(){
    map<P,int> mp;
    for(int i=1;i<=V;i++){
        for(auto e:G[i]){
            if(!e.id) continue;
            int full;
            if(e.cap>100000) full=inf; else full=1;
            int cost=(full==inf?0:e.cost);
            //printf("i=%d to=%d full=%d cap=%d cost=%d\n",i,e.to,full,e.cap,cost);
            if(e.cap){//a_(u,v)!=cap->lambda_(u,v)=0
                mp[P(min(i,e.to),max(i,e.to))]++;
                //if(i!=s&&e.to!=t) add_cons(e.to,i,cost);
            }
            if(e.cap!=full){//a_(u,v)>0->f_v-f_u=cost_(u,v)+lambda_(u,v)
                add_cons(e.to,i,-cost);
            }
        }
    }
    for(int i=1;i<=V;i++){
        for(auto e:G[i]){
            if(!e.id) continue;
            //if(e.to==t||i==s) continue;
            int full;
            if(e.cap>100000) full=inf; else full=1;
            int cost=(full==inf?0:e.cost);
            if(mp[P(min(i,e.to),max(i,e.to))]!=full){
                add_cons(e.to,i,cost);
                add_cons(i,e.to,cost);
            }
        }
    }
    int st=V+1;
    add_cons(s,t,k); 
    add_cons(t,s,-k);
    for(int i=1;i<=V;i++) add_cons(st,i,0);
    //add_cons(s,st,0);
    spfa2(st);
    int dummy=f[s];
    for(int i=1;i<=V;i++){
        f[i]-=dummy;
    }
    //for(int i=1;i<=V;i++) printf("i=%d f=%d\n",i,f[i]);
    
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m-1;j++){
            int d=f[get_id(i,j)]-f[get_id(i,j+1)];
            d=max(d,-d);
            d=max(d,a[i][j]);
            printf("%lld%c",d,j==m-1?'\n':' ');
        }
    }
    for(int i=1;i<=n-1;i++) {
        for(int j=1;j<=m;j++){
            int d=f[get_id(i,j)]-f[get_id(i+1,j)];
            d=max(d,-d);
            d=max(d,b[i][j]);
            printf("%lld%c",d,j==m?'\n':' ');
        }
    }
}
signed main(){
    scanf("%lld",&T);
    while(T--){
        scanf("%lld%lld%lld",&n,&m,&k);
        s=n*m+1; t=n*m+2; V=t;
        for(int i=1;i<=n;i++) {
            for(int j=1;j<=m-1;j++){
                int x;
                scanf("%lld",&x); a[i][j]=x;
                add_edge(get_id(i,j),get_id(i,j+1),1,x);
                add_edge(get_id(i,j+1),get_id(i,j),1,x);
            }
        }
        for(int i=1;i<=n-1;i++) {
            for(int j=1;j<=m;j++){
                int x;
                scanf("%lld",&x); b[i][j]=x;
                add_edge(get_id(i,j),get_id(i+1,j),1,x);
                add_edge(get_id(i+1,j),get_id(i,j),1,x);
            }
        }
        for(int i=1;i<=n;i++) add_edge(s,get_id(i,1),inf,0);
        for(int i=1;i<=n;i++) GG[get_id(i,m)].push_back(P(t,0));
        spfa3(s);
        k+=f[t];
        //printf("k=%d\n",k);
        for(int i=1;i<=n;i++) add_edge(get_id(i,m),t,inf,-k);
        ans=-min_cost_flow(s,t);
        printf("%lld\n",ans);
        construct();
        for(int i=1;i<=V+1;i++) G[i].clear();
        for(int i=1;i<=V+1;i++) H[i].clear();
        for(int i=1;i<=V+1;i++) GG[i].clear();
    }
    return 0;
}
