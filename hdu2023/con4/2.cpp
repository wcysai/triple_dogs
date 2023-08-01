#pragma GCC optimize(3)
// #pragma GCC optimize("trapv")
#include<bits/stdc++.h>
// #define int long long
using namespace std;

#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int N=1000007;
const int INF=1e9;
const int mod=998244353;
const double pi=acos(-1);
mt19937 rng(1234);
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
namespace internal {

#if __cplusplus >= 202002L

using std::bit_ceil;

#else

// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
    unsigned int x = 1;
    while (x < (unsigned int)(n)) x *= 2;
    return x;
}

#endif

// @param n `1 <= n`
// @return same with std::bit::countr_zero
int countr_zero(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

}  // namespace internal


#if __cplusplus >= 201703L

template <class S,
          auto op,
          auto e,
          class F,
          auto mapping,
          auto composition,
          auto id>
struct lazy_segtree {
    static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                  "op must work as S(S, S)");
    static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                  "e must work as S()");
    static_assert(
        std::is_convertible_v<decltype(mapping), std::function<S(F, S)>>,
        "mapping must work as F(F, S)");
    static_assert(
        std::is_convertible_v<decltype(composition), std::function<F(F, F)>>,
        "compostiion must work as F(F, F)");
    static_assert(std::is_convertible_v<decltype(id), std::function<F()>>,
                  "id must work as F()");

#else

template <class S,
          S (*op)(S, S),
          S (*e)(),
          class F,
          S (*mapping)(F, S),
          F (*composition)(F, F),
          F (*id)()>
struct lazy_segtree {

#endif

  public:
    lazy_segtree() : lazy_segtree(0) {}
    explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
    explicit lazy_segtree(const std::vector<S>& v) : _n(int(v.size())) {
        size = (int)internal::bit_ceil((unsigned int)(_n));
        log = internal::countr_zero((unsigned int)size);
        d = std::vector<S>(2 * size, e());
        lz = std::vector<F>(size, id());
        for (int i = 0; i < _n; i++) d[size + i] = v[i];
        for (int i = size - 1; i >= 1; i--) {
            update(i);
        }
    }

    void set(int p, S x) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= log; i++) update(p >> i);
    }

    S get(int p) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        return d[p];
    }

    S prod(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return e();

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        S sml = e(), smr = e();
        while (l < r) {
            if (l & 1) sml = op(sml, d[l++]);
            if (r & 1) smr = op(d[--r], smr);
            l >>= 1;
            r >>= 1;
        }

        return op(sml, smr);
    }

    S all_prod() { return d[1]; }

    void apply(int p, F f) {
        assert(0 <= p && p < _n);
        p += size;
        for (int i = log; i >= 1; i--) push(p >> i);
        d[p] = mapping(f, d[p]);
        for (int i = 1; i <= log; i++) update(p >> i);
    }
    void apply(int l, int r, F f) {
        assert(0 <= l && l <= r && r <= _n);
        if (l == r) return;

        l += size;
        r += size;

        for (int i = log; i >= 1; i--) {
            if (((l >> i) << i) != l) push(l >> i);
            if (((r >> i) << i) != r) push((r - 1) >> i);
        }

        {
            int l2 = l, r2 = r;
            while (l < r) {
                if (l & 1) all_apply(l++, f);
                if (r & 1) all_apply(--r, f);
                l >>= 1;
                r >>= 1;
            }
            l = l2;
            r = r2;
        }

        for (int i = 1; i <= log; i++) {
            if (((l >> i) << i) != l) update(l >> i);
            if (((r >> i) << i) != r) update((r - 1) >> i);
        }
    }

    template <bool (*g)(S)> int max_right(int l) {
        return max_right(l, [](S x) { return g(x); });
    }
    template <class G> int max_right(int l, G g) {
        assert(0 <= l && l <= _n);
        assert(g(e()));
        if (l == _n) return _n;
        l += size;
        for (int i = log; i >= 1; i--) push(l >> i);
        S sm = e();
        do {
            while (l % 2 == 0) l >>= 1;
            if (!g(op(sm, d[l]))) {
                while (l < size) {
                    push(l);
                    l = (2 * l);
                    if (g(op(sm, d[l]))) {
                        sm = op(sm, d[l]);
                        l++;
                    }
                }
                return l - size;
            }
            sm = op(sm, d[l]);
            l++;
        } while ((l & -l) != l);
        return _n;
    }

    template <bool (*g)(S)> int min_left(int r) {
        return min_left(r, [](S x) { return g(x); });
    }
    template <class G> int min_left(int r, G g) {
        assert(0 <= r && r <= _n);
        assert(g(e()));
        if (r == 0) return 0;
        r += size;
        for (int i = log; i >= 1; i--) push((r - 1) >> i);
        S sm = e();
        do {
            r--;
            while (r > 1 && (r % 2)) r >>= 1;
            if (!g(op(d[r], sm))) {
                while (r < size) {
                    push(r);
                    r = (2 * r + 1);
                    if (g(op(d[r], sm))) {
                        sm = op(d[r], sm);
                        r--;
                    }
                }
                return r + 1 - size;
            }
            sm = op(d[r], sm);
        } while ((r & -r) != r);
        return 0;
    }

  private:
    int _n, size, log;
    std::vector<S> d;
    std::vector<F> lz;

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }
    void all_apply(int k, F f) {
        d[k] = mapping(f, d[k]);
        if (k < size) lz[k] = composition(f, lz[k]);
    }
    void push(int k) {
        all_apply(2 * k, lz[k]);
        all_apply(2 * k + 1, lz[k]);
        lz[k] = id();
    }
};

struct info{
  int k, nxt, idx;
};
int a[N],par[N],dfn[N], leave[N],ans[N];
int cnt=0;
vi g[N];
int x[N],y[N],z[N]; 
using S=int;
using F=int;
S op(S l,S r){return min(l,r);}
S e(){return INF;}
F id(){return 0;}
F composition(F l,F r){return l+r;}
S mapping(F l,S r){return l+r;}

void dfs(int u,int p){
  par[u]=p;
  dfn[u]=cnt, cnt++;
  for (auto c:g[u]){
    int to=c;
    if (to==p) continue;
    dfs(to,u);
  }
  leave[u]=cnt;
}

int tot=0;
int pa[N],dep[N],sz[N],wson[N],top[N],spos[N],tpos[N];
void dfs1(int v,int p,int d)
{
    dep[v]=d;pa[v]=p;sz[v]=1;
    for(int i=0;i<(int)g[v].size();i++)
    {
        int to=g[v][i];
        if(to==p) continue;
        dfs1(to,v,d+1);
        if(sz[to]>sz[wson[v]]) wson[v]=to;
        sz[v]+=sz[to];
    }
}
void dfs2(int v,int p,int num)
{
    top[v]=num;
    spos[v]=++tot;
    tpos[tot]=v;
    if(wson[v]) dfs2(wson[v],v,num);
    for(int i=0;i<(int)g[v].size();i++)
    {
        int to=g[v][i];
        if(to==p||to==wson[v]) continue;
        dfs2(to,v,to);
    }
}

void update(int u,int v,int w, lazy_segtree<S,op,e,F,mapping,composition,id> &seg)
{
    assert(u&&v);
    int res=-INF;
    while(top[u]!=top[v])
    {
        // cerr<<u<<" "<<v<<" "<<top[u]<<" "<<top[v]<<endl;
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        seg.apply(spos[top[u]],spos[u]+1,w);
        u=pa[top[u]];
    }
    if(dep[u]<dep[v]) swap(u,v);
    seg.apply(spos[v],spos[u]+1,w);
}

void solve(){
  int n;
  n=io.xint();
  cnt=0;
  // int pa[N],dep[N],sz[N],wson[N],top[N],spos[N],tpos[N];
  for (int i=0;i<=n+2;++i) pa[i]=dep[i]=sz[i]=wson[i]=top[i]=spos[i]=tpos[i]=0;
  for (int i=1;i<=n;++i) a[i]=io.xint();
  for (int i=1;i<=n;++i) g[i].clear(), ans[i]=0;
  for (int i=1;i<=n-1;++i){
    int u,v,w;
    u=io.xint(); v=io.xint(); w=io.xint();
    x[i]=u, y[i]=v, z[i]=w;
    g[u].push_back(v), g[v].push_back(u);
  }
  dfs(1,-1);
  tot=0;
  dfs1(1,1,1);
  dfs2(1,0,1);
  lazy_segtree<S,op,e,F,mapping,composition,id> seg1(n+3), seg2(n+3);
  for (int i=1;i<=n-1;++i){
    // cerr<<x[i]<<" "<<y[i]<<" "<<par[x[i]]<<" "<<par[y[i]]<<endl;
    if (par[x[i]]!=y[i]) swap(x[i],y[i]);
    assert(par[x[i]]==y[i]);
    seg1.set(spos[x[i]],z[i]), seg2.set(spos[x[i]],z[i]);
  }
  vector<pii> lst;
  for (int i=1;i<=n;++i) lst.push_back({a[i],i});
  sort(all(lst));
  reverse(all(lst));
  int prv=-1;
  vi v;
  auto ssolve=[&](vector<int> &x,int val){
    // cerr<<"fuck: ";
    // for (auto c:x) cerr<<c<<" ";
    // cerr<<endl;
    // for (int i=1;i<=n;++i) cerr<<seg1.get(i)<<" ";
    // cerr<<endl;
    // for (int i=1;i<=n;++i) cerr<<seg2.get(i)<<" ";
    // cerr<<endl;

    for (auto c:x){
      update(c,1,-1,seg1);
      update(c,1,1,seg2);
    }
    // for (int i=1;i<=n;++i) cerr<<seg1.get(i)<<" ";
    // cerr<<endl;
    // for (int i=1;i<=n;++i) cerr<<seg2.get(i)<<" ";
    // cerr<<endl;
    // cerr<<seg1.all_prod()<<" "<<seg2.all_prod()<<endl;
    while (1){
      auto ret=seg1.min_left(n+1,[&](S x){return x>0;});
      if (ret==0) break;
      ret--;
      ans[ret]=val, seg1.set(ret,INF), seg2.set(ret,INF);
    }
    while (1){
      auto ret=seg2.min_left(n+1,[&](S y){return y>x.size();});
      if (ret==0) break;
      ret--;
      ans[ret]=val, seg1.set(ret,INF), seg2.set(ret,INF);
    }
    for (auto c:x){
      update(c,1,1,seg1);
      update(c,1,-1,seg2);
    }
  };
  for (auto c:lst){
    if (prv==-1) prv=c.first;
    if (prv==c.first) {v.push_back(c.second); continue;}
    ssolve(v,prv);
    v.clear();
    prv=c.first, v.push_back(c.second);
  } 
  ssolve(v,prv);
  for (int i=1;i<=n-1;++i) cout<<ans[spos[x[i]]]<<"\n";
}
signed main(){
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  // int size(512<<20); // 512M
  // __asm__ ( "movq %0, %%rsp\n"::"r"((char*)malloc(size)+size));
  int _;
  cin>>_;
  while (_--){
    solve();
  }
  // exit(0);
}  
/*
1
6
2 2 2 2 2 2
1 2 4
1 3 4
1 4 4
4 5 4
4 6 4
*/
