#include<bits/stdc++.h>
#define pb push_back
#define F first
#define S second
using namespace std;
typedef pair<int,int>pi;
const int maxn=1e6+15;
set<pi> A,ban;
const int inf=1e9;
struct node{
    string op;
    int x,y;
}a[2005];
bool cmp(node u,node v){
    return u.x<v.x;
}
vector<node> r[9];
int sx,sy,tx,ty,n,tot;
vector<pi> bans,cbans;
vector<pi> G[maxn];
int dis[maxn];
bool vis[maxn];
void dij(int s,int n){
    priority_queue<pi,vector<pi>,greater<pi> > Q;
    for (int i=1;i<=n;i++) vis[i]=0,dis[i]=inf;
    dis[s]=0; Q.push((pi){dis[s],s});
    while (!Q.empty()){
        pi tmp=Q.top(); Q.pop();
        int u=tmp.S;
        if (!vis[u]) vis[u]=1; else continue;
        for (auto e:G[u]){
            int v=e.F;
            if (dis[v]>dis[u]+e.S){
                dis[v]=dis[u]+e.S;
                Q.push((pi){dis[v],v});
            }
        }
    }
}
bool valid(int y){
    return y>=1&&y<=8;
}
bool ins(int x,int y){
    if (!valid(y)) return 0;
    if (A.find((pi){x,y})!=A.end()) return 0;
    if (ban.find((pi){x,y})==ban.end()){
        ban.insert((pi){x,y});
    }
    return 1;
}
bool banned(int x,int y){
    if (ban.find((pi){x,y})!=ban.end()) return 1;
    if (!r[y].size()) return 0;
    int m=r[y].size();
    if (x<r[y][0].x) return r[y][0].op=="R"||r[y][0].op=="Q";
    if (x>r[y][m-1].x) return r[y][m-1].op=="R"||r[y][m-1].op=="Q";
    int lf=0,rt=m-1;
    while (rt-lf>1){
        int mid=(lf+rt)>>1;
        if (r[y][mid].x<x) lf=mid; else rt=mid;
    }
    return r[y][lf].op=="R"||r[y][lf].op=="Q"||r[y][rt].op=="R"||r[y][rt].op=="Q";
}
set<int> tX;
vector<int> X;
void add_edge(int u,int v,int w){
    //cout<<u<<' '<<v<<' '<<w<<endl;
    G[u].pb((pi){v,w});
    G[v].pb((pi){u,w});
}
void add_c(int u,int c,int x,int y){
    if (banned(x,y)) return;
    add_edge(u,c*8+y,abs(X[c]-x));
    for (int i=y-1;i>=1;i--){
        if (banned(X[c],i)) break;
        add_edge(u,c*8+i,max(abs(x-X[c]),abs(y-i)));
    }
    for (int i=y+1;i<=8;i++){
        if (banned(X[c],i)) break;
        add_edge(u,c*8+i,max(abs(x-X[c]),abs(y-i)));
    }
}
void Add_edge(int u,int x,int y){
    for (int i=0;i<tot;i++) if (x==X[i]) add_edge(u,i*8+y,0);
    if (x<X[0]) add_c(u,0,x,y);
    if (x>X[tot-1]) add_c(u,tot-1,x,y);
    for (int i=0;i<tot-1;i++) {
        if (x>X[i]&&x<X[i+1]){
            add_c(u,i+1,x,y);
            add_c(u,i,x,y);
        }
    }
}
int main(){
    cin >> sx >> sy >> tx >> ty;
    //if (sx>tx) swap(sx,tx),swap(sy,ty);
    cin >> n;
    if (!n){
        cout << max(abs(sx-tx),abs(sy-ty)) << endl;
        return 0;
    }
    for (int i=1;i<=n;i++){
        cin >> a[i].op >> a[i].x >> a[i].y;
        A.insert((pi){a[i].x,a[i].y});
        ban.insert((pi){a[i].x,a[i].y});
        r[a[i].y].pb(a[i]);
    }
    for (int i=1;i<=8;i++) sort(r[i].begin(),r[i].end(),cmp);
    for (int i=1;i<=n;i++){
        int x=a[i].x,y=a[i].y;
        ins(x,y);
        if (a[i].op=="K"){
            ins(x-1,y-1);
            ins(x+1,y-1);
            ins(x-1,y+1);
            ins(x+1,y+1);
            ins(x,y-1);
            ins(x,y+1);
            ins(x-1,y);
            ins(x+1,y);
        } 
        if (a[i].op=="N"){
            ins(x-1,y-2);
            ins(x+1,y-2);
            ins(x-1,y+2);
            ins(x+1,y+2);
            ins(x-2,y-1);
            ins(x+2,y-1);
            ins(x-2,y+1);
            ins(x+2,y+1);
        } 
        if (a[i].op=="R"||a[i].op=="Q"){
            for (int i=y-1;i>=1;i--){
                if (!ins(x,i)) break;
            }
            for (int i=y+1;i<=8;i++){
                if (!ins(x,i)) break;
            }
        }
        if (a[i].op=="B"||a[i].op=="Q"){
            for (int i=y-1;i>=1;i--){
                if (!ins(x+y-i,i)) break;
            }
            for (int i=y-1;i>=1;i--){
                if (!ins(x-y+i,i)) break;
            }
            for (int i=y+1;i<=8;i++){
                if (!ins(x+y-i,i)) break;
            }
            for (int i=y+1;i<=8;i++){
                if (!ins(x-y+i,i)) break;
            }
        }
    }
    for (auto pt:ban){
        int x=pt.F;
        if (tX.find(x-1)==tX.end()) tX.insert(x-1);
        if (tX.find(x)==tX.end()) tX.insert(x);
        if (tX.find(x+1)==tX.end()) tX.insert(x+1);
    }
    for (auto x:tX) X.pb(x);
    tot=X.size();
 
    bool ok=0;
    if (sx<X[0]&&tx<X[0]) ok=1;
    if (sx>X[tot-1]&&tx>X[tot-1]) ok=1;
    for (int i=0;i<tot-1;i++){
        if (sx>X[i]&&sx<X[i+1]&&tx>X[i]&&tx<X[i+1]) ok=1;
    }
    if (ok){
        for (int i=min(sy,ty);i<=max(sy,ty);i++) if (banned(sx,i)) {puts("0");return 0;}
        cout << max(abs(sx-tx),abs(sy-ty)) << endl;
        return 0;
    }
    //for (auto x:X)cout<<x<<' ';cout<<endl;
    Add_edge(tot*8+1,sx,sy);
    Add_edge(tot*8+2,tx,ty);
    for (int i=0;i<tot;i++){
        int x=X[i];
        for (int j=1;j<8;j++){
            if (banned(x,j)||banned(x,j+1)) continue;
            add_edge(i*8+j,i*8+j+1,1);
        }
    }
    for (int i=0;i<tot-1;i++){
        int xa=X[i],xb=X[i+1];
        if (xb-xa==1){
            for (int j=1;j<8;j++){
                if (!(banned(xa,j)||banned(xb,j))) add_edge(i*8+j,(i+1)*8+j,1);
                if (!(banned(xa,j)||banned(xb,j+1))) add_edge(i*8+j,(i+1)*8+j+1,1);
                if (!(banned(xb,j)||banned(xa,j+1))) add_edge((i+1)*8+j,i*8+j+1,1);
            }
        } else {
            for (int j=1;j<=8;j++) add_c(i*8+j,i+1,xa,j);
        }
    }
    int N=tot*8+2;
    dij(N-1,N);
    if (dis[N]==inf) cout << "-1" << endl;
    else cout << dis[N] << endl;
}
