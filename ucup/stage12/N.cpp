#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,q;
vector<P> edges[4*MAXN];
bool ask[MAXN];
int a[MAXN],b[MAXN],c[MAXN];
ll p[MAXN],sz[MAXN];
ll res[MAXN];
ll ans;
vector<pair<ll&,ll> > backup;
vector<P> queries;
void modify(ll &ref,ll v){
    backup.push_back({ref,ref});
    ref=v;
}
void rollback(int t){
    while((int)backup.size()>t){
        backup.back().F=backup.back().S;
        backup.pop_back();
    }
}
void init(int n){
    ans=0;
    for(int i=1;i<=n;i++){
        p[i]=i;
        sz[i]=1;
    }
}
int find(int x){
   while(p[x]!=x) x=p[x];
   return x;
}
bool unite(int x,int y){
    x=find(x);
    y=find(y);
    if(x==y) return false;
    modify(ans,ans+sz[x]*sz[y]);
    if(sz[x]<sz[y]){
        modify(p[x],y); modify(sz[y],sz[y]+sz[x]);
    }
    else{
        modify(p[y],x); 
        modify(sz[x],sz[x]+sz[y]);
    }
    return true;
}
void add_edge(int k,int l,int r,int x,int y,int u,int v){
    if(x>r||l>y) return;
    if(l>=x&&r<=y){
        edges[k].push_back(P(u,v));
        return;
    }
    int mid=(l+r)/2;
    add_edge(k*2,l,mid,x,y,u,v);add_edge(k*2+1,mid+1,r,x,y,u,v);
}
void solve(int k,int l,int r){
    if(l>r) return;
    int t=(int)backup.size();
    for(auto e:edges[k]) unite(e.F,e.S);
    if(l==r){
        res[queries[l].S]=ans;
        rollback(t);
        return;
    }
    int mid=(l+r)/2;
    solve(k*2,l,mid);solve(k*2+1,mid+1,r);
    rollback(t);
}
int main(){
    scanf("%d%d%d",&n,&m,&k);
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&a[i],&b[i],&c[i]);
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        int x;
        scanf("%d",&x);
        queries.push_back(P(x,i));
    }
    sort(queries.begin(),queries.end());
    for(int i=0;i<m;i++){
        int cur=0;
        for(int j=29;j>=0;j--){
            int x=((c[i]>>j)&1),y=((k>>j)&1);
            if(y==0){
                if(x) cur+=(1<<j);
                continue;
            }
            else {
                if(x){
                    int l=lower_bound(queries.begin(),queries.end(),P(cur+(1<<j),0))-queries.begin();
                    int r=lower_bound(queries.begin(),queries.end(),P(cur+(1<<(j+1)),0))-queries.begin()-1;
                    if(l<=r) add_edge(1,0,q-1,l,r,a[i],b[i]);
                }
                else{
                    int l=lower_bound(queries.begin(),queries.end(),P(cur,0))-queries.begin();
                    int r=lower_bound(queries.begin(),queries.end(),P(cur+(1<<j),0))-queries.begin()-1;
                    if(l<=r) add_edge(1,0,q-1,l,r,a[i],b[i]);
                    cur+=(1<<j);
                }
            }
        }
    }
    init(n);
    solve(1,0,q-1);
    for(int i=0;i<q;i++) printf("%lld\n",res[i]);
    return 0;
}



