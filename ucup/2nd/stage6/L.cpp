#pragma GCC optimize(3) 
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int> P;
int n,k;
ll a[MAXN],r[MAXN];
ll ans[MAXN];
set<P> s;
int res;
int p[MAXN],rk[MAXN],sz[MAXN];
bool has[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        rk[i]=0;
        sz[i]=0;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    res-=(sz[x]+1)/2; res-=(sz[y]+1)/2;
    if(rk[x]<rk[y]) {p[x]=y; sz[y]+=sz[x]; res+=(sz[y]+1)/2;}
    else
    {
        p[y]=x; sz[x]+=sz[y]; res+=(sz[x]+1)/2;
        if(rk[x]==rk[y]) rk[x]++;
    }
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&r[i]);
    sort(r+1,r+n+1);
    vector<P> v;
    for(int i=1;i<=n-1;i++){
        a[i]=r[i+1]-r[i];
        v.push_back(P(a[i],i));
    }
    init(n-1);
    sort(v.begin(),v.end());
    memset(ans,-1,sizeof(ans));
    for(int i=0;i<n-1;i++){
        has[v[i].S]=true;
        sz[v[i].S]=1; res++;
        if(has[v[i].S-1]) unite(v[i].S,v[i].S-1);
        if(has[v[i].S+1]) unite(v[i].S,v[i].S+1);
        //printf("res=%d\n",res);
        if(ans[res]==-1) ans[res]=v[i].F;
    }
    for(int i=(n/2);i>=1;i--){
        if(ans[i]==-1) ans[i]=ans[i+1];
    }
    for(int i=1;i<=n/2;i++) printf("%lld%c",ans[i],i==n/2?'\n':' ');
    return 0;
}

