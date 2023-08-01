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
int t,n,m,a[MAXN];
vector<int> G[MAXN];
int fa[MAXN],col[MAXN],dep[MAXN],sum[MAXN],deg[MAXN];
vector<P> edges;
void dfs(int v,int p,int d)
{
    col[v]=1; fa[v]=p;
    dep[v]=d;
    for(auto to:G[v])
    {
        if(to==p) continue;
        if(col[to]==1)
        {
            sum[fa[to]]--; sum[v]++;
            edges.push_back(P(v,to));
        }
        else if(!col[to]) {deg[v]++; deg[to]++; dfs(to,v,d+1);}
    }
    col[v]=2;
}
void dfs2(int v,int p)
{
    col[v]=1;
    for(auto to:G[v])
    {
        if(to==p) continue;
        if(!col[to]) 
        {
            dfs2(to,v);
            sum[v]+=sum[to];
        }
    }
    col[v]=2;
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear(),sum[i]=0,deg[i]=0;
        edges.clear();
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v); G[v].push_back(u);
        }
        for(int i=1;i<=n;i++) col[i]=0;
        dfs(1,0,0);
        for(int i=1;i<=n;i++) col[i]=0;
        dfs2(1,0);
        bool f=true;
        for(int i=1;i<=n;i++) if(sum[i]>=2) {f=false; break;}
        if(f)
        {
            for(auto p:edges)
            {
                vector<int> tmp; tmp.clear();
                int v=p.F,to=p.S;
                while(v!=fa[to]) 
                {
                    tmp.push_back((int)G[v].size()&1);
                    v=fa[v];
                }
                bool flag1=true;
                for(int i=1;i<(int)tmp.size();i++) if(tmp[i]!=tmp[i-1]) flag1=false;
                bool flag2=true;
                int sz=(int)tmp.size();
                for(int i=0;i<(int)tmp.size();i++)
                {
                    int nxt=(i+1)%sz;
                    if(tmp[i]==tmp[nxt]) flag2=false;
                }
                if((!flag1)&&(!flag2)) f=false;
            }
        }
        if(!f) {puts("YES"); continue;}
        int cnt=0;
        for(int i=1;i<=n;i++) if(deg[i]&1) cnt++;
        if(cnt%4==0) puts("YES"); else puts("NO");
    }
    return 0;
}

