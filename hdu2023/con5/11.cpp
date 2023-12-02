#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 100005
#define INF 1000000000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,tot,t,bcc_cnt,mcnt;
vector<int> G[MAXN],bcc[MAXN];
int st[MAXN],dfn[MAXN],low[MAXN],bccno[MAXN];
bool art[MAXN];
int id[MAXN];
int N;
map<P,ll> mp;
map<P,int> mp2;
struct FastIO {
    static const int S = 4e7;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline int xint()
    {
        int s = 1, c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    inline void xstring(char *s)
    {
        int c = xchar();
        while (c <= 32) c = xchar();
        for (; c > 32; c = xchar()) * s++ = c;
        *s = 0;
    }
    inline void wchar(int x)
    {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(ll x)
    {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void wstring(const char *s)
    {
        while (*s) wchar(*s++);
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;
void add_edge(int u,int v,int x){
    if(u>v) swap(u,v);
    //rintf("%d %d %d\n",u,v,x);
    mp2[P(u,v)]=x;
}
//block-cut tree:
//vertex-biconnected components are connected by their shared articulation point
void dfs(int v,int p,int &tot)
{
    dfn[v]=low[v]=++tot;
    st[t++]=v;
    for(auto to:G[v])
    {
        if(to==p) continue;
        if(!dfn[to])
        {
            dfs(to,v,tot);
            low[v]=min(low[v],low[to]);
            if(low[to]>=dfn[v])
            {
                art[v]=(dfn[v]>1||dfn[to]>2);
                bcc_cnt++;
                bcc[bcc_cnt].push_back(v); bccno[v]=bcc_cnt;
                add_edge(v,to,bcc_cnt);
                int cur=v;
                while(bcc[bcc_cnt].back()!=to)
                {
                    add_edge(st[t-1],cur,bcc_cnt);
                    bccno[st[t-1]]=bcc_cnt;
                    cur=st[t-1];
                    bcc[bcc_cnt].push_back(st[t-1]),t--;
                }
            }
        }
        else low[v]=min(low[v],dfn[to]);
    }
}
int tarjan()
{
    bcc_cnt=t=0;
    memset(dfn,0,sizeof(dfn));
    memset(art,false,sizeof(art));
    for(int i=1;i<=n;i++) if(!dfn[i]) dfs(i,-1,tot=0);
    return bcc_cnt;
}
void build_block_cut_tree()
{
    tarjan();N=0;
    for(int i=1;i<=n;i++) if(art[i]) id[i]=++N;
    for(int i=1;i<=bcc_cnt;i++)
    {
        N++;
        for(auto v:bcc[i])
        {
            if(!art[v]) id[v]=N;
        }
    }
    for(int i=1;i<=bcc_cnt;i++) bcc[i].clear();
}
vector<ll> save[MAXN];
ll solve(int id){
    sort(save[id].begin(),save[id].end());
    if(save[id].size()==1) return save[id][0];
    if(save[id].size()==2) return save[id][0]+save[id][1];
    return min(save[id][0]+save[id][1],save[id][2]);
}

int main(){
    T=io.xint();
    while(T--){
        mp.clear(); mp2.clear();
        n=io.xint(); m=io.xint();
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=0;i<m;i++){
            int u,v,w;
            u=io.xint(); v=io.xint(); w=io.xint();
            if(u>v) swap(u,v);
            mp[P(u,v)]+=w;
        }
        if(n==2){
            ll ans=0;
            for(auto p:mp) ans+=p.S;
            printf("%lld\n",ans);
            continue;
        }
        for(auto p:mp){
            G[p.F.F].push_back(p.F.S); G[p.F.S].push_back(p.F.F);
        }
        build_block_cut_tree();
        ll ans=INF;
        for(auto p:mp){
            //assert(mp2.find(p.F)!=mp2.end());
            save[mp2[p.F]].push_back(p.S);
        }
        for(int i=1;i<=bcc_cnt;i++) if(save[i].size()) ans=min(ans,solve(i));
        for(int i=1;i<=bcc_cnt;i++) save[i].clear();
        printf("%lld\n",ans);
    }
    return 0;
}

