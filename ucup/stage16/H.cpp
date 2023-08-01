#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,tot,n,k,x[MAXN],y[MAXN];
vector<int> disx,disy;
vector<P> save[MAXN];
vector<int> savex[MAXN];
vector<P> G[MAXN];
vector<int> use[MAXN];
int parity[MAXN];
bool lab[MAXN];
int ypos[MAXN],yid[MAXN];
bool choice[MAXN];
int p[MAXN],r[MAXN],faid[MAXN];
int match[MAXN];
void add_edge(int u,int v,int id){
    G[u].push_back(P(v,id));
    G[v].push_back(P(u,id));
}
void init(int n){
    for(int i=1;i<=n;i++){
        p[i]=i;
        r[i]=0;
    }
}
int find(int x){
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y){
    x=find(x);
    y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) {p[x]=y; }
    else{
        p[y]=x;
        if(r[x]==r[y]) r[x]++;
    }
}
bool same(int x,int y){
    return find(x)==find(y);
}
bool vis[MAXN];
vector<int> odd;
void dfs(int v,int id){
    vis[v]=true; faid[v]=id;
    if(parity[v]) odd.push_back(v);
    for(auto e:G[v]){
        if(e.S==id) continue;
        int to=e.F;
        if(!vis[to]) dfs(to,e.S);
    }
}
void dfs2(int v,int id){
    for(auto e:G[v]){
        if(e.S==id) continue;
        int to=e.F;
        dfs2(to,e.S);
        lab[v]^=lab[to];
    }
    if(lab[v]){
        use[ypos[id]][yid[id]]^=1;
        use[ypos[id]][yid[id]+1]^=1;
    }
}
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        n*=2;
        disx.clear(); disy.clear();
        for(int i=1;i<=n;i++) match[i]=0;
        for(int i=1;i<=n;i++){
            scanf("%d%d",&x[i],&y[i]);
            disx.push_back(x[i]); disy.push_back(y[i]);
        }
        sort(disx.begin(),disx.end()); sort(disy.begin(),disy.end());
        disx.erase(unique(disx.begin(),disx.end()),disx.end());
        disy.erase(unique(disy.begin(),disy.end()),disy.end());
        for(int i=1;i<=n;i++){
            x[i]=lower_bound(disx.begin(),disx.end(),x[i])-disx.begin()+1;
            y[i]=lower_bound(disy.begin(),disy.end(),y[i])-disy.begin()+1;
        }
        int szx=(int)disx.size(),szy=(int)disy.size();
        for(int i=1;i<=szx;i++) parity[i]=0;
        for(int i=1;i<=szy;i++) save[i].clear();
        init(szx);
        for(int i=1;i<=n;i++) {
            parity[x[i]]^=1;
            save[y[i]].push_back(P(x[i],i));
        }
        tot=0;
        for(int i=1;i<=szx;i++) G[i].clear();
        for(int i=1;i<=szy;i++){
            sort(save[i].begin(),save[i].end());
            for(int j=1;j<(int)save[i].size();j++){
                int a=save[i][j-1].S,b=save[i][j].S;
                if(!same(x[a],x[b])){
                    unite(x[a],x[b]);
                    ++tot;
                    ypos[tot]=i; yid[tot]=j-1;
                    add_edge(x[a],x[b],tot);
                }
            }
        }
        for(int i=1;i<=szx;i++) vis[i]=lab[i]=false;
        for(int i=1;i<=szy;i++) {
            use[i].resize((int)save[i].size());
            for(int j=0;j<(int)use[i].size();j++) use[i][j]=0;
        }
        for(int i=1;i<=szx;i++){
            if(!vis[i]){
                odd.clear();
                dfs(i,-1);
                for(int i=1;i<(int)odd.size();i+=2){
                    lab[odd[i]]=lab[odd[i-1]]=true;
                }
                dfs2(i,-1);
            }
        }
        for(int i=1;i<=szy;i++){
            int last=-1;
            for(int j=0;j<(int)use[i].size();j++){
                if(!use[i][j]) continue;
                else{
                    if(last==-1) last=j;
                    else{
                        match[save[i][last].S]=save[i][j].S;
                        match[save[i][j].S]=save[i][last].S;
                        last=-1;
                    }
                }
            }
            assert(last==-1);
        }
        for(int i=1;i<=szx;i++) savex[i].clear();
        for(int i=1;i<=n;i++){
            if(match[i]) continue;
            savex[x[i]].push_back(i);
        }
        vector<int> tmp;
        for(int i=1;i<=szx;i++){
            while(savex[i].size()>=2){
                int a=savex[i].back(); savex[i].pop_back();
                int b=savex[i].back(); savex[i].pop_back();
                match[a]=b; match[b]=a; 
            }
            if(savex[i].size()) {tmp.push_back(savex[i].back()); savex[i].clear();}
        }
        int ans=n/2-(int)tmp.size()/2;
        printf("%d\n",ans);
        for(int i=1;i<(int)tmp.size();i+=2){
            match[tmp[i-1]]=tmp[i]; match[tmp[i]]=tmp[i-1];
        }
        for(int i=1;i<=n;i++){
            if(match[i]){
                printf("%d %d\n",i,match[i]);
                int z=match[i];
                match[z]=match[i]=0;
            }
        }
    }
    return 0;
}

