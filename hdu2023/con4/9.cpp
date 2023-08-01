#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,k,a[MAXN];
vector<P> G[MAXN];
vector<int> H[MAXN];
int tot,col[MAXN],sz[MAXN],fa[MAXN],st[MAXN],ed[MAXN];
vector<int> save[MAXN];
int ans,num[MAXN];
int bit[MAXN+1];
void madd(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
int pow_mod(int a,int i){
    int s=1;
    while(i){
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
int sum(int i){
    int s=0;
    while(i>0){
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x){
    while(i<=n){
        bit[i]+=x;
        i+=i&-i;
    }
}
bool cmp(int x,int y){
    return sz[x]<sz[y];
}
void dfs(int v,int p){
    sz[v]=1; fa[v]=p; st[v]=++tot;
    for(auto e:G[v]){
        if(e.F==p) continue;
        col[e.F]=e.S;
        save[e.S].push_back(e.F);
        dfs(e.F,v);
        sz[v]+=sz[e.F];
    }
    ed[v]=tot;
}
void dfs2(int v){
    for(auto to:H[v]){
        //printf("v=%d to=%d num1=%d num2=%d\n",v,to,num[v],num[to]);
        madd(ans,1LL*num[v]*num[to]%MOD);
        dfs2(to);
    }
}
struct FastIO {
    static const int S = 1e7;
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
int main()
{
    t=io.xint();
    while(t--){
        tot=0;
        n=io.xint();
        for(int i=1;i<=n;i++) {G[i].clear(),save[i].clear(); save[i].push_back(1);}
        for(int i=0;i<n-1;i++){
            int u,v,w;
            u=io.xint(); v=io.xint(); w=io.xint();
            G[u].push_back(P(v,w)); G[v].push_back(P(u,w));
        }
        dfs(1,0);
        ans=0;
        for(int i=1;i<=n;i++){
            sort(save[i].begin(),save[i].end(),cmp);
            for(int j=0;j<(int)save[i].size();j++){
                int x=save[i][j];
                num[j]=sz[x]-(sum(ed[x])-sum(st[x]-1));
                add(st[x],num[j]);
            }
            for(int j=0;j<(int)save[i].size();j++) {int x=save[i][j]; add(st[x],-num[j]);}
            set<P> s;
            vector<P> edges;
            for(int j=0;j<(int)save[i].size();j++){
                int x=save[i][j];
                while(s.size()){
                    auto it=s.lower_bound(P(st[x],0));
                    if(it==s.end()||(it->F)>ed[x]) break;
                    int y=it->S;
                    edges.push_back(P(j,y));
                    s.erase(it);
                }
                if(sz[x]!=n) s.insert(P(st[fa[x]],j));
            }
            for(auto p:edges) {
                H[p.F].push_back(p.S); 
            }
            dfs2((int)save[i].size()-1);
            for(int j=0;j<(int)save[i].size();j++) H[j].clear();
        }
        int z=(1LL*n*(n-1)/2)%MOD;
        ans=1LL*ans*pow_mod(z,MOD-2)%MOD;
        int res=0;
        for(int i=2;i<=n;i++){
            int tmp=1LL*ans*((1LL*i*(i-1)/2)%MOD)%MOD;
            res^=tmp;
        }
        printf("%d\n",res);
    }
    return 0;
}

