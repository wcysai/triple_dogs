#include<bits/stdc++.h>
#define F first
#define S second
#define pb push_back
const int M=1000000007;
const int inv3=(M+1)/3;
using namespace std;
typedef long long ll;
typedef pair<int,int>pi;
const int maxn=1e6+3;
const int B=15;
int n,m,k,ccnt,cnt;
bool vis[maxn];
vector<int> G[maxn];
map<pi,int> id;
void dfs(int u){
    vis[u]=1; ccnt++;
    assert(G[u].size()<=2);
    for (auto v:G[u]){
        if (!vis[v]) dfs(v);
    }
}
void add_edge(int u,int v){
    G[u].pb(v); G[v].pb(u);
}
int getid(int x,int y){
    if (x>y) swap(x,y);
    if (id.find((pi){x,y})==id.end()) id[(pi){x,y}]=++cnt;
    return id[(pi){x,y}];
}
void LG(){
    id.clear(); cnt=0;
    int ecnt=0;
    vector<pi> E;
    for (int i=1;i<=n;i++){
        for (int j=0;j<G[i].size();j++){
            int u=getid(i,G[i][j]);
            for (int k=0;k<j&&ecnt<m;k++){
                int v=getid(i,G[i][k]); 
                E.pb((pi){u,v}); ecnt++;
            }
        }
    }
    //assert(cnt==m);
    n=cnt; m=ecnt;
    for (int i=1;i<=n;i++) G[i].clear();
    for (auto e:E) add_edge(e.F,e.S);
}
mt19937_64 gen(time(0));
void solve(){
    cin >> n >> m >> k; k--;
    for (int i=1;i<=n;i++) G[i].clear();
    for (int i=0;i<m;i++){
        int u,v; //cin >> u >> v;
        while (1){
            u=gen()%n+1;
            v=gen()%n+1;
            if (u>v) swap(u,v);
            if (u!=v&&id.find((pi){u,v})==id.end()){
                id[(pi){u,v}]=1;
                break;
            }
        }
        //cout << u << " " << v << endl;
        add_edge(u,v);
    }
    int tms=0;
    while (m<n&&k>0){
        LG(); tms++; k--;
        if (!k||tms==B) break;
    }
    if (m>=n){
        cout << n << endl;
    } else {
        int ans=n;
        for (int i=1;i<=n;i++) vis[i]=0;
        for (int i=1;i<=n;i++) if (!vis[i]&&G[i].size()==1){
            ccnt=0;
            dfs(i);
            ans-=ccnt;
            ans+=max(0,ccnt-k);
        }
        cout << ans << endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _; cin >> _;
    while (_--) solve();
}
