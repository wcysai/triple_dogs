#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=5e5+5;
ll a[maxn],R[maxn],L[maxn];
bool vis[maxn];
int nxt[maxn],pre[maxn],n;
bool check(ll x){
    for (int i=0;i<n;i++){
        nxt[i]=(i+1)%n; 
        pre[(i+1)%n]=i;
        L[i]=R[i]=vis[i]=0;
    }
    queue<int> q;
    int cnt=0;
    for (int i=0;i<n;i++) if (x>=a[i]) vis[i]=1,q.push(i);
    while (!q.empty()){
        int w=q.front(); q.pop(); ++cnt; 
        if (cnt==n) break;
        int u=pre[w],v=nxt[w];
        nxt[u]=v; pre[v]=u;
        R[u]+=R[w]+a[w];
        L[v]+=L[w]+a[w];
        if (!vis[u]&&R[u]+x>=a[u]) vis[u]=1,q.push(u);
        if (!vis[v]&&L[v]+x>=a[v]) vis[v]=1,q.push(v);
    }
    return cnt==n;
}
int main(){
    scanf("%d",&n);
    for (int i=0;i<n;i++) scanf("%lld",&a[i]);
    ll l=-1,r=2e13;
    while (r-l>1){
        ll mid=(l+r)>>1;
        if (check(mid)) r=mid; else l=mid;
    }
    cout << r << endl;
}