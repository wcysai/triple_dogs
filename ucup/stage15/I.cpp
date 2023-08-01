#include<bits/stdc++.h>
#define MAXN 65
#define MAXM 6005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,tot,tot2;
vector<pair<int,P> > edges;
struct GraphMatroid
{
    int p[MAXN],rk[MAXN];
    void clear(){
        for(int i=1;i<=n;i++) p[i]=i,rk[i]=0;
    }
    int find(int x){
        if(p[x]==x) return x;
        return p[x]=find(p[x]);
    }
    void unite(int u,int v){
        u=find(u); v=find(v);
        if(rk[u]<rk[v]){
            p[u]=v;
        }
        else{
            p[v]=u; if(rk[u]==rk[v]) rk[u]++;
        }
    }
    void add(int id)
    {
        int u=edges[id].S.F,v=edges[id].S.S;
        if(find(u)==find(v)) return;
        else unite(u,v);
    }
    bool test(int id){
        int u=edges[id].S.F,v=edges[id].S.S;
        return (find(u)!=find(v));
    }
}gm;
struct PartitionMatroid
{
    int cnt[125];
    void clear()
    {
        memset(cnt,0,sizeof(cnt));
    }
    void add(int id)
    {
        cnt[edges[id].F]++;
    }
    bool test(int id)
    {
        return (cnt[edges[id].F]==0);
    }
}pm;


template <typename MT1, typename MT2>
struct MatroidIntersection
{
    int n;
    MatroidIntersection(int _n):n(_n){}
    int pre[MAXM],id[MAXM];
    bool vis[MAXM],sink[MAXM],has[MAXM];
    queue<int> que;
    void clear_all()
    {
        memset(vis,false,sizeof(vis));
        memset(sink,false,sizeof(sink));
        memset(pre,0,sizeof(pre));
        while(que.size()) que.pop();
    }
    vector<int> getcur()
    {
        vector<int> ret;
        for(int i=0;i<n;i++) if(has[i]) ret.push_back(i);
        return ret;
    }
    void enqueue(int v,int p)
    {
        vis[v]=true; pre[v]=p;
        que.push(v);
    }
    vector<int> run()
    {
        MT1 mt1;  MT2 mt2;
        while(true)
        {
            vector<int> cur=getcur();
            int cnt=0;
            for(int i=0;i<n;i++) if(has[i]) id[i]=cnt++;
            MT1 allmt1; MT2 allmt2; allmt1.clear(); allmt2.clear();
            vector<MT1> vmt1(cur.size()); vector<MT2> vmt2(cur.size());
            for(auto &x:vmt1) x.clear(); for(auto &x:vmt2) x.clear();
            clear_all();
            for(auto x:cur) allmt1.add(x),allmt2.add(x);
            for(int i=0;i<(int)cur.size();i++)
                for(int j=0;j<(int)cur.size();j++)
                {
                    if(i==j) continue;
                    vmt1[i].add(cur[j]);
                    vmt2[i].add(cur[j]);
                }
            for(int i=0;i<n;i++)
            {
                if(has[i]) continue;
                if(allmt1.test(i)) {que.push(i); vis[i]=true;}
            }
            for(int i=0;i<n;i++)
            {
                if(has[i]) continue;
                if(allmt2.test(i)) sink[i]=true;
            }
            int last=-1;
            while(que.size())
            {
                int v=que.front(); que.pop();
                if(sink[v]) {last=v; break;}
                for(int i=0;i<n;i++)
                {
                    if(vis[i]) continue;
                    if(has[i]==has[v]) continue;
                    if(has[v])
                    {
                        if(vmt1[id[v]].test(i)) enqueue(i,v);
                    }
                    else
                    {
                        if(vmt2[id[i]].test(v)) enqueue(i,v);
                    }
                }
            }
            if(last==-1) return cur;
            while(last)
            {
                has[last]^=1;
                last=pre[last];
            }
        }
    }
};
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++)
    {
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        edges.push_back(make_pair(w,P(u,v)));
    }
    sort(edges.begin(),edges.end());
    MatroidIntersection<GraphMatroid,PartitionMatroid> matint(0);
    int c=0;
    for(int i=0;i<m;i++){
        int now=i;
        while(now<m&&edges[i].F==edges[now].F) now++;
        if(edges[i].F!=c) {printf("%d\n",c); return 0;}
        matint.n=now;
        printf("now=%d\n",now);
        vector<int> v=matint.run();
        for(auto x:v) printf("%d ",x);
        puts("");
        if(v.size()!=c+1) {printf("%d\n",c); return 0;}
        c++;
        i=now-1;
    }
    printf("%d\n",c);
    return 0;
}
