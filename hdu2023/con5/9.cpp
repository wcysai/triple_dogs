#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,p[MAXN];
vector<int> G[MAXN];
vector<int> H[MAXN];
int wson[MAXN],top[MAXN],len[MAXN],ans[MAXN];
int lg[MAXN];
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
void dfs(int v,int num)
{
    top[v]=num; len[v]=1;
    if(wson[v]) {
        dfs(wson[v],num);
        len[v]=len[wson[v]]+1;
    }
    if(top[v]==v){
        if(p[v]) H[top[p[v]]].push_back(v);
    }
    for(int i=0;i<(int)G[v].size();i++)
    {
        int to=G[v][i];
        if(to==wson[v]) continue;
        dfs(to,to);
    }
}
void dfs2(int v){
    ans[v]=lg[len[v]]+1;
    for(auto to:H[v]){
        dfs2(to);
        ans[v]=max(ans[v],ans[to]+lg[len[v]]+1);
    }
}
int main()
{
    int size(512<<20); // 512M
    __asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));
    for(int i=1;i<=20;i++) lg[(1<<(i-1))+1]++;
    for(int i=1;i<=1000000;i++) lg[i]+=lg[i-1];
    T=io.xint();
    while(T--){
        n=io.xint();
        for(int i=1;i<=n;i++) {G[i].clear(); H[i].clear();}
        int root=0;
        for(int i=1;i<=n;i++){
            p[i]=io.xint();
            if(p[i]==0) root=i;
            else G[p[i]].push_back(i);
        }
        for(int i=1;i<=n;i++) wson[i]=io.xint();
        dfs(root,root);
        dfs2(root); 
        printf("%d\n",ans[root]);
    }
    exit(0);
}

