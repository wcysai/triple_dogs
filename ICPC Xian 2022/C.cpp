#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=507;
int n,m;
string s[N];
struct edge{int to,cap,rev;};
int V;
vector<edge> G[N];
int level[N],iter[N];
const int INF=LLONG_MAX/4;
void add_edge(int from,int to,int cap){
    G[from].push_back((edge){to,cap,(int)G[to].size()});
    G[to].push_back((edge){from,0,(int)G[from].size()-1});
}

void bfs(int s){
    memset(level,-1,sizeof(level));
    queue<int> que;
    level[s]=0;
    que.push(s);
    while (!que.empty()){
        int v=que.front(); que.pop();
        for (int i=0;i<(int)G[v].size();++i){
            edge &e=G[v][i];
            if (e.cap>0&&level[e.to]<0){
                level[e.to]=level[v]+1;
                que.push(e.to);
            }
        }
    }
}

int dfs(int v,int t,int f){
    if (v==t) return f;
    for (int &i=iter[v];i<(int)G[v].size();++i){
        edge &e=G[v][i];
        if (level[v]<level[e.to]&&e.cap>0){
            int d=dfs(e.to,t,min(f,e.cap));
            if (d>0){
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
    for (;;){
        bfs(s);
        if (level[t]<0) return flow;
        memset(iter,0,sizeof(iter));
        int f;
        while ((f=dfs(s,t,INF))>0) flow+=f;
    }
}

vector<pair<int,int>> v;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n,m,c,d;
    cin>>n>>m>>c>>d;
    int abc=0;
    int sink=n+m+3, source=n+m+4;
    for (int i=0;i<n;++i){
        string s;
        cin>>s;
        for (int j=0;j<m;++j){
            if (s[j]=='.') add_edge(i+1,j+n+1,1),abc++;
        }
    }
    int ans=0;
    int ret=d*abc;
    for (int i=1;i<=250;++i){
        for (int j=0;j<n;++j){
            add_edge(source,j+1,1);
        }
        for (int j=0;j<m;++j){
            add_edge(j+n+1,sink,1);
        }
        ans+=max_flow(source,sink);
        ret=min(ret,c*i+d*(abc-ans));
    }
    cout<<ret<<endl;
}