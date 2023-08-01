#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 15005
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,n1,n2;
vector<int> GG[MAXN];
int mx[MAXN],my[MAXN],dx[MAXN],dy[MAXN];
queue<int> que;
vector<int> G[MAXN],rG[MAXN];
vector<int> vs;
bool used[MAXN],vis[MAXN];
int cmp[MAXN];
int col[MAXN];
bitset<14001> bs[14001];
void add_edge(int from,int to){
    G[from].push_back(to);
    rG[to].push_back(from);
}
void dfs1(int v,int from){
    //printf("v=%d from=%d\n",v,from);
    used[v]=true;
    if(v!=from) {bs[from].set(n1+v); bs[n1+v].set(from);}
    for(auto to:GG[v]){
        if(used[to]) continue;
        dfs1(to,from);
    }
}
void dfs(int v){
    used[v]=true;
    for(int i=0;i<(int)G[v].size();i++)
        if(!used[G[v][i]]) dfs(G[v][i]);
    vs.push_back(v);
}
void rdfs(int v,int k){
    used[v]=true;
    cmp[v]=k;
    for(int i=0;i<(int)rG[v].size();i++)
        if(!used[rG[v][i]]) rdfs(rG[v][i],k);
}
int scc(){
    memset(used,0,sizeof(used));
    vs.clear();
    for(int v=1;v<=n;v++) if(!used[v]) dfs(v);
    int k=0;
    memset(used,0,sizeof(used));
    for(int i=vs.size()-1;i>=0;i--) if(!used[vs[i]]) rdfs(vs[i],++k);
    return k;
}
bool find(int u){
    for(int i=n1+1;i<=2*n1;i++){
        if(bs[u][i]&&(!vis[i])&&dy[i]==dx[u]+1){
            vis[i]=true;
            if(!my[i]||find(my[i])){
                mx[u]=i;
                my[i]=u;
                return true;
            }
        }
    }
    return false;
}
void color(int v,int c){
    assert(!col[v]);
    col[v]=c;
    if(mx[v]){
        color(mx[v]-n1,c);
    }
}
int matching(){
    memset(mx,0,sizeof(mx));
    memset(my,0,sizeof(my));
    int ans=0;
    while(true){
        bool flag=false;
        while(!que.empty()) que.pop();
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));
        for(int i=1;i<=n1;i++)
            if(!mx[i]) que.push(i);
        while(!que.empty()){
            int u=que.front();
            que.pop();
            for(int i=n1+1;i<=2*n1;i++)
                if(bs[u][i]&&!dy[i]){
                    dy[i]=dx[u]+1;
                    if(my[i]){
                        dx[my[i]]=dy[i]+1;
                        que.push(my[i]);
                    }
                    else flag=true;
                }
        }
        if(!flag) break;
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n1;i++)
            if(!mx[i]&&find(i)) ans++;
    }
    return ans;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        int u,v; scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    int num=scc();
    set<P> s;
    for(int i=1;i<=n;i++){
        //printf("i=%d cmp=%d\n",i,cmp[i]);
        for(auto to:G[i]){
            if(cmp[to]==cmp[i]) continue;
            if(s.count(P(cmp[i],cmp[to]))) continue;
            //printf("add %d %d\n",cmp[i],cmp[to]);
            GG[cmp[i]].push_back(cmp[to]);
            s.insert(P(cmp[i],cmp[to]));
        }
    }
    n1=n2=num;
    for(int i=1;i<=num;i++){
        memset(used,0,sizeof(used));
        dfs1(i,i);
    }
    matching();
   // printf("%d\n",num-matching());
    int tot=0;
    for(int i=1;i<=n1;i++)
        if(!my[n1+i]) 
            color(i,++tot);
   // printf("tot=%d\n",tot);
    for(int i=1;i<=n;i++) 
        printf("%d%c",col[cmp[i]],i==n?'\n':' ');
    return 0;
}

