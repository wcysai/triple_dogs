#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 2000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,k;
vector<int> c[MAXN];
int now[MAXN];
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
    	k=io.xint();
        for(int i=0;i<k;i++){
            int sz; sz=io.xint();
            for(int j=0;j<sz;j++){
                int x; x=io.xint(); c[i].push_back(x);
            }
            sort(c[i].begin(),c[i].end());
        }
        int ans=INF;
        set<P> s;
        for(int i=0;i<k;i++){
            now[i]=0;
            s.insert(P(c[i][now[i]],i));
        }
        while(true){
            auto it1=s.begin(); auto it2=(--s.end());
            ans=min(ans,(it2->F)-(it1->F));
            int val=(it1->F);
            vector<int> tmp;
            while(s.size()&&(((s.begin()->F)==val))){
                tmp.push_back(s.begin()->S);
                s.erase(s.begin());
            }
            bool f=true;
            for(auto x:tmp){
                if(now[x]==(int)c[x].size()-1) {f=false; break;}
                now[x]++;
                s.insert(P(c[x][now[x]],x));
            }
            if(!f) break;
        }
        printf("%d\n",ans);
        for(int i=0;i<k;i++) c[i].clear();
    }
    return 0;
}
