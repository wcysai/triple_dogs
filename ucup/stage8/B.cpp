#include<bits/stdc++.h>
#define MAXN 2030
using namespace std;
int T,n,c;
vector<int> G[MAXN];
int mx[MAXN],my[MAXN];
queue<int> que;
int dx[MAXN],dy[MAXN];
bool valid[MAXN];
bool vis[MAXN];
bool find(int u){
    for(int i=0;i<G[u].size();i++){
        if(!valid[G[u][i]]) continue;
        if(!vis[G[u][i]]&&dy[G[u][i]]==dx[u]+1){
            vis[G[u][i]]=true;
            if((my[G[u][i]]==-1)||find(my[G[u][i]])){
                mx[u]=G[u][i];
                my[G[u][i]]=u;
                return true;
            }
        }
    }
    return false;
}
int matching(){
    memset(mx,-1,sizeof(mx));
    memset(my,-1,sizeof(my));
    memset(vis,0,sizeof(vis));
    int ans=0;
    while(true)
    {
        bool flag=false;
        while(!que.empty()) que.pop();
        memset(dx,0,sizeof(dx));
        memset(dy,0,sizeof(dy));
        for(int i=0;i<(1<<n);i++){
            if(__builtin_popcount(i)&1) continue;
            if(!valid[i]) continue;
            if(mx[i]==-1) que.push(i);
        }
        while(!que.empty()){
            int u=que.front(); 
            que.pop();
            for(int i=0;i<G[u].size();i++){
                if(!valid[G[u][i]]) continue;
                if(!dy[G[u][i]]){
                    dy[G[u][i]]=dx[u]+1;
                    if(my[G[u][i]]!=-1){
                        dx[my[G[u][i]]]=dy[G[u][i]]+1;
                        que.push(my[G[u][i]]);
                    }
                    else flag=true;
                }
            }
        }
        if(!flag) break;
        memset(vis,0,sizeof(vis));
        for(int i=0;i<(1<<n);i++){
            if(__builtin_popcount(i)&1) continue;
            if(!valid[i]) continue;
            if((mx[i]==-1)&&find(i)) ans++;
           // printf("i=%d ans=%d\n",i,ans);
        }
    }
    return ans;
}
string s1,s2;
int main(){
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&c);
        cin>>s1>>s2;
        int st=0;
        for(int i=0;i<n;i++){
            if(s1[i]!=s2[i]) st+=(1<<i);
        }
        for(int i=0;i<(1<<n);i++){
            G[i].clear();
            for(int j=0;j<n;j++) G[i].push_back(i^(1<<j));
        }
        for(int i=0;i<(1<<n);i++) valid[i]=true;
        for(int i=0;i<c;i++){
            string s;
            cin>>s;
            int mask=0;
            for(int j=0;j<n;j++){
                if(s[j]=='.') mask+=(1<<j);
            }
            valid[mask]=false;
        }
        int a=matching();
        valid[st]=false;
        int b=matching();
        if(a==b) puts("Bob"); else puts("Alice");
    }
    return 0;
}

