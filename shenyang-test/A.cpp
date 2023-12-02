#include<bits/stdc++.h>
#define MAXV 200005
#define MAXN 200005
#define INF 1000000000
using namespace std;
struct edge{int to,cap,rev;};
int n,V;
vector<edge> G[MAXV];
int level[MAXV];
int iter[MAXV];
void add_edge(int from,int to,int cap){
    G[from].push_back((edge){to,cap,(int)G[to].size()});
    G[to].push_back((edge){from,0,(int)G[from].size()-1});
}
void bfs(int s){
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while(!que.empty())
    {
        int v=que.front(); que.pop();
        for(int i=0;i<(int)G[v].size();i++)
        {
            edge &e=G[v][i];
            if(e.cap>0&&level[e.to]<0)
            {
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v,int t,int f){
    if(v==t) return f;
    for(int &i=iter[v];i<(int)G[v].size();i++)
    {
        edge &e=G[v][i];
        if(level[v]<level[e.to]&&e.cap>0)
        {
            int d=dfs(e.to,t,min(f,e.cap));
            if(d>0)
            {
                e.cap-=d;
                G[e.to][e.rev].cap+=d;
                return d;
            }
        }
    }
    return 0;
}
int max_flow(int s,int t){
    int flow=0;
    for(;;)
    {
        bfs(s);
        if(level[t]<0) return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while((f=dfs(s,t,INF))>0)
          flow+=f;
    }
}
int maxi[MAXN];
int cnt[MAXN];
vector<int> dis;
vector<int> save[MAXN];
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        int x;
        scanf("%d",&x);
        for(int j=0;j<x;j++) {int y; scanf("%d",&y); save[i].push_back(y); maxi[i]=max(maxi[i],y);}
        dis.push_back(maxi[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    int sz=(int)dis.size();
    int s=n+sz+1,t=n+sz+2;
    V=t;
    for(int i=1;i<=n;i++){
        int id=lower_bound(dis.begin(),dis.end(),maxi[i])-dis.begin()+1;
        for(auto x:save[i]){
            int z=lower_bound(dis.begin(),dis.end(),x)-dis.begin();
            if(z<(int)dis.size()&&dis[z]==x) cnt[z]++;
        }
        add_edge(i,n+id,1);
        add_edge(s,i,1);
    }
    for(int i=1;i<=sz;i++) add_edge(i,t,cnt[i]);
    printf("%d\n",max_flow(s,t));
}
