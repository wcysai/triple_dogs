#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define MAXM 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int d[MAXN];
int b[MAXN],bel[MAXN],cost[MAXN];
ll a[MAXN];
vector<int> G[MAXN];
ll val[MAXM];
int T,n,k;
struct LinearMatroid
{
    ll basis[55][64];
    void clear()
    {
        memset(basis,0,sizeof(basis));
    }
    void add(int x)
    {
        int v=bel[x];
        ll tmp=a[x];
        for(auto to:G[v]){
            ll z=tmp;
            for(int j=63;j>=0;j--)
            {
                if(!(z&(1LL<<j))) continue;
                if(!basis[to][j])
                {
                    basis[to][j]=z;
                    break;
                }
                else z^=basis[to][j];
            }
        }
    }
    bool test(int x)
    {
        int v=bel[x];
        ll tmp=a[x];
        for(auto to:G[v]){
            ll z=tmp;
            bool f=false;
            for(int j=63;j>=0;j--){
                if(!(z&(1LL<<j))) continue;
                if(!basis[to][j]) {f=true; break;} else z^=basis[to][j];
            }
            if(!f) return false;
        }
        return true;
    }
};
struct PartitionMatroid{
    vector<int> cnt;
    bool clear(){
        cnt.clear(); cnt.resize(n+1);
        return true;
    }
    void add(int x){
        cnt[bel[x]]++;
    }
    void dec(int x){
        cnt[bel[x]]--;
    }
    bool test(int x){
        return !cnt[bel[x]];
    }
};
 
 
template <typename MT1, typename MT2>
struct MatroidIntersection
{
    int n,S,T;
    MatroidIntersection(int _n):n(_n){}
    int pre[MAXM],d[MAXM];
    bool inque[MAXM],has[MAXM];
    vector<int> g[MAXM];
    queue<int> que;
    void clear_all()
    {
        for(int i=1;i<=n+2;i++){
            inque[i]=false;
            pre[i]=0;
            d[i]=INF;
            if(has[i]) cost[i]=b[i]; else cost[i]=-b[i];
            g[i].clear();
        }
        while(que.size()) que.pop();
    }
    void add_edge(int u,int v)
    {
        g[u].push_back(v);
    }
    vector<int> getcur()
    {
        vector<int> ret;
        for(int i=1;i<=n;i++) if(has[i]) ret.push_back(i);
        return ret;
    }
    void enqueue(int v,int p)
    {
        pre[v]=p;
        if(!inque[v])
        {
            inque[v]=true;
            que.push(v);
        }
    }
    pair<vector<int>,ll> run()
    {
        ll ans=0;
        memset(has,false,sizeof(has));
        MT1 allmt1;  MT2 allmt2;
        allmt1.clear(); allmt2.clear();
        /*for(int i=1;i<=n;i++){
            if(allmt1.test(i)&&allmt2.test(i)){
                allmt1.add(i); allmt2.add(i);
                ans+=w[i];
                has[i]=true;
            }
        }*/
        S=n+1; T=n+2;
        while(true)
        {
            clear_all();
            auto cur=getcur();
            allmt1.clear(); allmt2.clear();
            for(auto x:cur) {allmt1.add(x); allmt2.add(x);}
            vector<MT1> vmt1; vector<MT2> vmt2;
            vmt1.resize(cur.size()); vmt2.resize(cur.size());
            for(auto &x:vmt1) x.clear();
            for(auto &x:vmt2) x.clear();
            for(int i=0;i<(int)cur.size();i++)
                for(int j=0;j<(int)cur.size();j++){
                    if(i==j) continue;
                    vmt1[i].add(cur[j]);
                    vmt2[i].add(cur[j]);
                }
            for(int i=0;i<(int)cur.size();i++){
                for(int j=1;j<=n;j++){
                    if(has[j]) continue;
                    if(vmt1[i].test(j)) add_edge(cur[i],j);
                    if(vmt2[i].test(j)) add_edge(j,cur[i]);
                }
            }
            for(int i=1;i<=n;i++){
                if(!has[i]){
                    if(allmt1.test(i)) add_edge(S,i);
                    if(allmt2.test(i)) add_edge(i,T);
                }
            }
            d[S]=0; que.push(S); inque[S]=true;
            cost[S]=cost[T]=0;
            while(que.size()){
                int u=que.front(); que.pop();
                for(auto to:g[u])
                    if(d[to]>d[u]+cost[to])
                    {
                        d[to]=d[u]+cost[to];
                        enqueue(to,u);
                    }
                inque[u]=false;
            }
            if(d[T]==INF) return make_pair(getcur(),ans);
            ans+=d[T];
            //printf("d=%d\n",d[T]);
            int last=pre[T];
            while(last!=S)
            {
                has[last]^=1;
                last=pre[last];
            }
        }
    }
};
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=1;i<=2*n;i+=2){
            scanf("%lld%d%lld%d",&a[i],&b[i],&a[i+1],&b[i+1]);
            bel[i]=bel[i+1]=(i+1)/2;
        }
        for(int i=0;i<n-1;i++){
            int u,v; scanf("%d%d",&u,&v);
            G[u].push_back(v); G[v].push_back(u);
        }
        for(int i=1;i<=n;i++) G[i].push_back(i);
        MatroidIntersection<LinearMatroid,PartitionMatroid> matint(2*n);
        auto res=matint.run();
        if((int)res.F.size()!=n) {printf("-1\n"); continue;}
        printf("%lld\n",-res.S);
    }
    return 0;
}
 
