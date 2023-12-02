#include<bits/stdc++.h>
#define F first
#define S second
#define pb push_back
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int,int>pi;
typedef vector<int> vi;
const ll inf=1e12;
const int maxn=1e6+10;
const int M=998244353;
int kase=0;
ll dis[10];
int k,n,pre[10],lim[10],cnt[10],a[50005][10];
bool vis[10];
set<pi> p[10][10];
void add(int x,int c){
    for (int j=0;j<k;j++) if (j!=c) p[c][j].insert((pi){a[x][j]-a[x][c],x});
}
void del(int x,int c){
    for (int j=0;j<k;j++) if (j!=c) p[c][j].erase((pi){a[x][j]-a[x][c],x});
}
ll D(int x,int y){
    if (!p[x][y].size()) return inf;
    return (*p[x][y].begin()).F;
}
void trans(int x,int y){
    assert(p[x][y].size()>0);
    int z=(*p[x][y].begin()).S;
    del(z,x); add(z,y);
}
mt19937_64 gen(1);
void solve(){
    cin >> n >> k;
    for (int i=0;i<n;i++)
        for (int j=0;j<k;j++)
            //a[i][j]=gen()%10+1;
            cin >> a[i][j];
/*
    for (int i=0;i<n;i++){
        for (int j=0;j<k;j++)cout<<a[i][j]<<' ';cout<<endl;
    }
*/
    //for (int i=0;i<n;i++) lim[gen()%k]++;
    //for (int j=0;j<k;j++)cout<<lim[j]<<' ';cout<<endl;
    for (int i=0;i<k;i++) cin >> lim[i];
    ll ans=0;
    for (int i=0;i<n;i++){
        int c=0;
        for (int j=1;j<k;j++) if (a[i][j]<a[i][c]) c=j;
        add(i,c); cnt[c]++; ans+=a[i][c];
        if (cnt[c]<=lim[c]) continue;
        vis[c]=1; pre[c]=c; dis[1]=0;
        for (int j=0;j<k;j++) 
            if (j!=c) vis[j]=0,pre[j]=c,dis[j]=D(c,j);
        for (int u=1;u<k;u++){
            int v=-1;
            for (int j=0;j<k;j++) if (!vis[j]&&(v==-1||dis[v]>dis[j])) v=j;
            vis[v]=1;
            for (int j=0;j<k;j++)
                if (!vis[j]){
                    ll now=dis[v]+D(v,j);
                    if (now<dis[j]){
                        dis[j]=now;
                        pre[j]=v;
                    }
                }
        }
        int t=-1;
        for (int j=0;j<k;j++) if (cnt[j]<lim[j]&&(t==-1||dis[t]>dis[j])) t=j;
        assert(t!=-1);
        assert(dis[t]<inf);
        cnt[t]++; cnt[c]--;
        ans+=dis[t];
        while (t!=c) trans(pre[t],t),t=pre[t];
    }
    cout << ans << endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int _=1;
    while (_--) solve();
}
