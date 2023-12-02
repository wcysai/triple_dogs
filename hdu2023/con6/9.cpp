#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,k,a[MAXN],b[MAXN],c[MAXN];
struct edge{
    int u,v,w,id;
};
int p[MAXN],r[MAXN];
int x[MAXN],y[MAXN];
vector<edge> E;
void init(int n)
{
    for(int i=0;i<n;i++)
    {
        p[i]=i;
        r[i]=0;
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
    if(r[x]<r[y]) p[x]=y;
    else
    {
        p[y]=x;
        if(r[x]==r[y]) r[x]++;
    }
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
bool cmp(edge x,edge y){
    return x.w<y.w;
}
int main()
{
    scanf("%d",&T);
    while(T--){
        E.clear();
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i],&b[i],&c[i]);
        init(i);
        for(int i=0;i<m;i++){
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
        }
    }
    return 0;
}

