#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 rice(time(NULL));
vector<int> G[MAXN];
int t,n,m;
bool oncyc[MAXN];
int color[MAXN];
int fa[MAXN];
int dep[MAXN],coef[MAXN],coef2[MAXN];
vector<int> cyc;
void dfs(int v,int p)
{
    color[v]=1;
    fa[v]=p;
    for(auto to:G[v])
    {
        if(to==p) continue;
        if(color[to]==1)
        {
            int now=v;
            cyc.push_back(v); oncyc[v]=true;
            do
            {
                now=fa[now];
                cyc.push_back(now); oncyc[now]=true;
            } while (now!=to);
        }
        else if(!color[to]) dfs(to,v);
    }
    color[v]=2;
}
int compute_hash(int v,int p,int d,int mod)
{
    vector<int> hsh;
    for(auto to:G[v])
    {
        if(oncyc[to]||to==p) continue;
        hsh.push_back(compute_hash(to,v,d+1,mod));
    }
    sort(hsh.begin(),hsh.end());
    int ret=dep[d];
    for(int i=0;i<(int)hsh.size();i++)
    {
        ret=(1LL*coef[i]*ret+hsh[i])%mod;
        ret^=coef2[i];
    }
    return ret;
}
int main()
{
    for(int i=0;i<=100000;i++) dep[i]=rice()%990000000+1,coef[i]=rice()%990000000+1,coef2[i]=rice()%(1<<29);
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=0;i<m;i++)
        {
            int u,v;
            scanf("%d%d",&u,&v);
            G[u].push_back(v); G[v].push_back(u);
        }
        if(m==n-1) {puts("YES"); continue;}
        if(m>n) {puts("NO"); continue;}
        for(int i=1;i<=n;i++) oncyc[i]=false,color[i]=0;
        cyc.clear();
        dfs(1,0);
        P p=P(-1,-1);
        bool f=true;
        if((int)cyc.size()%2==0)
        {
            for(int i=0;i<(int)cyc.size();i+=2)
            {
                int x=cyc[i];
                int a=compute_hash(x,0,0,1000000007);
                int b=compute_hash(x,0,0,998244353);
                //cout<<a<<' '<<b<<endl;
                if(p==P(-1,-1)) p=P(a,b);
                else if(p!=P(a,b)) {f=false; break;}
            }
            p=P(-1,-1);
            for(int i=1;i<(int)cyc.size();i+=2)
            {
                int x=cyc[i];
                int a=compute_hash(x,0,0,1000000007);
                int b=compute_hash(x,0,0,998244353);
                //cout<<a<<' '<<b<<endl;
                if(p==P(-1,-1)) p=P(a,b);
                else if(p!=P(a,b)) {f=false; break;}
            }
        }
        else
        {
            for(auto x:cyc)
            {
                int a=compute_hash(x,0,0,1000000007);
                int b=compute_hash(x,0,0,998244353);
                //cout<<a<<' '<<b<<endl;
                if(p==P(-1,-1)) p=P(a,b);
                else if(p!=P(a,b)) {f=false; break;}
            }
        }
        if(f) puts("YES"); else puts("NO");
    }
    return 0;
}