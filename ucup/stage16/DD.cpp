#include <bits/stdc++.h>
#define int long long
const int mod = 998244353, G = 3;
typedef std::vector<int> vi; 
typedef long long ll;
namespace Math {
	inline int pw(int base, int p) {
		static int res;
		for (res = 1; p; p >>= 1, base = static_cast<long long> (base) * base % mod) if (p & 1) res = static_cast<long long> (res) * base % mod;
		return res;
	}
	inline int inv(int x) { return pw(x, mod - 2); }
}
inline void reduce(int &x) { x += x >> 31 & mod; }
#define maxn 300005
int a[maxn], ans[maxn];
namespace FFT{
    struct num{
        double x,y;
        num() {x=y=0;}
        num(double x,double y):x(x),y(y){}
    };
    inline num operator+(num a,num b) {return num(a.x+b.x,a.y+b.y);}
    inline num operator-(num a,num b) {return num(a.x-b.x,a.y-b.y);}
    inline num operator*(num a,num b) {return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
    inline num conj(num a) {return num(a.x,-a.y);}
    int base=1;
    std::vector<num> roots={{0,0},{1,0}};
    std::vector<int> rev={0,1};
    const double PI=acosl(-1.0);
    void ensure_base(int nbase){
        if(nbase<=base) return;
        rev.resize(1<<nbase);
        for(int i=0;i<(1<<nbase);i++)
            rev[i]=(rev[i>>1]>>1)+((i&1)<<(nbase-1));
        roots.resize(1<<nbase);
        while(base<nbase){
            double angle=2*PI/(1<<(base+1));
            for(int i=1<<(base-1);i<(1<<base);i++){
                roots[i<<1]=roots[i];
                double angle_i=angle*(2*i+1-(1<<base));
                roots[(i<<1)+1]=num(cos(angle_i),sin(angle_i));
            }
            base++;
        }
    }
    void fft(std::vector<num> &a,int n=-1){
        if(n==-1) n=a.size();
        assert((n&(n-1))==0);
        int zeros=__builtin_ctz(n);
        ensure_base(zeros);
        int shift=base-zeros;
        for(int i=0;i<n;i++)
            if(i<(rev[i]>>shift))
                std::swap(a[i],a[rev[i]>>shift]);
        for(int k=1;k<n;k<<=1){
            for(int i=0;i<n;i+=2*k){
                for(int j=0;j<k;j++){
                    num z=a[i+j+k]*roots[j+k];
                    a[i+j+k]=a[i+j]-z;
                    a[i+j]=a[i+j]+z;
                }
            }
        }
    }
    std::vector<num> fa,fb;
    std::vector<ll> multiply(std::vector<int> &a, std::vector<int> &b){
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<sz;i++){
            int x=(i<(int)a.size()?a[i]:0);
            int y=(i<(int)b.size()?b[i]:0);
            fa[i]=num(x,y);
        }
        fft(fa,sz);
        num r(0,-0.25/sz);
        for(int i=0;i<=(sz>>1);i++){
            int j=(sz-i)&(sz-1);
            num z=(fa[j]*fa[j]-conj(fa[i]*fa[i]))*r;
            if(i!=j) fa[j]=(fa[i]*fa[i]-conj(fa[j]*fa[j]))*r;
            fa[i]=z;
        }
        fft(fa,sz);
        std::vector<ll> res(need);
        for(int i=0;i<need;i++) res[i]=fa[i].x+0.5;
        return res;
    }
    std::vector<int> multiply_mod(std::vector<int> &a,std::vector<int> &b,int m,int eq=0){
        int need=a.size()+b.size()-1;
        int nbase=0;
        while((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if(sz>(int)fa.size()) fa.resize(sz);
        for(int i=0;i<(int)a.size();i++){
            int x=(a[i]%m+m)%m;
            fa[i]=num(x&((1<<15)-1),x>>15);
        }
        fill(fa.begin()+a.size(),fa.begin()+sz,num{0,0});
        fft(fa,sz);
        if(sz>(int)fb.size()) fb.resize(sz);
        if(eq) copy(fa.begin(),fa.begin()+sz,fb.begin());
        else{
            for(int i=0;i<(int)b.size();i++){
                int x=(b[i]%m+m)%m;
                fb[i]=num(x&((1<<15)-1),x>>15);
            }
            fill(fb.begin()+b.size(),fb.begin()+sz,num{0,0});
            fft(fb,sz);
        }
        double ratio=0.25/sz;
        num r2(0,-1),r3(ratio,0),r4(0,-ratio),r5(0,1);
        for(int i=0;i<=(sz>>1);i++){
            int j=(sz-i)&(sz-1);
            num a1=(fa[i]+conj(fa[j]));
            num a2=(fa[i]-conj(fa[j]))*r2;
            num b1=(fb[i]+conj(fb[j]))*r3;
            num b2=(fb[i]-conj(fb[j]))*r4;
            if(i!=j){
                num c1=(fa[j]+conj(fa[i]));
                num c2=(fa[j]-conj(fa[i]))*r2;
                num d1=(fb[j]+conj(fb[i]))*r3;
                num d2=(fb[j]-conj(fb[i]))*r4;
                fa[i]=c1*d1+c2*d2*r5;
                fb[i]=c1*d2+c2*d1;
            }
            fa[j]=a1*b1+a2*b2*r5;
            fb[j]=a1*b2+a2*b1;
        }
        fft(fa,sz);fft(fb,sz);
        std::vector<int> res(need);
        for(int i=0;i<need;i++){
            ll aa=fa[i].x+0.5;
            ll bb=fb[i].x+0.5;
            ll cc=fa[i].y+0.5;
            res[i]=(aa+((bb%m)<<15)+((cc%m)<<30))%m;
        }
        return res;
    }
    std::vector<int> square_mod(std::vector<int> &a,int m){
        return multiply_mod(a,a,m,1);
    }
};
namespace Poly {
#define N maxn
	int rev[N], lim, s, ilim;
	int Wn[N + 1];
	inline void clear(register int *l, const int *r) {
		if (l >= r) return ;
		while (l != r) *l++ = 0;
	}
 
	inline void init(const int n) {
		s = -1, lim = 1; while (lim < n) lim <<= 1, ++s; ilim = Math::inv(lim);
		for (register int i = 0; i < lim; ++i) rev[i] = rev[i >> 1] >> 1 | (i & 1) << s;
		const int t = Math::pw(G, (mod - 1) / lim);
		*Wn = 1; for (register int *i = Wn; i != Wn + lim; ++i) *(i + 1) = static_cast<long long> (*i) * t % mod;
	}
	inline void NTT(int *A, const int op = 1) {
		static int Wt[N];
		for (register int i = 1; i < lim; ++i) if (i < rev[i]) std::swap(A[i], A[rev[i]]);
		for (register int mid = 1; mid < lim; mid <<= 1) {
			const int t = lim / mid >> 1;
			*Wt = Wn[op ? 0 : lim];
			for (register int *i = Wt, W = 0; i != Wt + mid; ++i, W += t) *i = Wn[op ? W : lim - W];
			for (register int i = 0; i < lim; i += mid << 1) {
				for (register int j = 0; j < mid; ++j) {
					const int X = A[i + j], Y = static_cast<long long> (Wt[j]) * A[i + j + mid] % mod;
					reduce(A[i + j] += Y - mod), reduce(A[i + j + mid] = X - Y);
				}
			}
		}
		if (!op) for (register int *i = A; i != A + lim; ++i) *i = static_cast<long long> (*i) * ilim % mod;
	}
 
	std::vector<int> P[N << 1], S[N << 1];
	int C[N], D[N];
	void DC_NTT(int rt, int l, int r) {
		if (l == r) { P[rt] = {a[l], 1}; return ; }
		int mid = l + r >> 1;
		DC_NTT(rt << 1, l, mid), DC_NTT(rt << 1 | 1, mid + 1, r);
		int L = rt << 1, R = rt << 1 | 1;
		int n = P[L].size(), m = P[R].size();
		init(n + m - 1);
		std::copy(P[L].begin(), P[L].end(), C); clear(C + n, C + lim);
		std::copy(P[R].begin(), P[R].end(), D); clear(D + m, D + lim);
		NTT(C), NTT(D);
		for (int i = 0; i < lim; ++i) C[i] = static_cast<long long> (C[i]) * D[i] % mod;
		NTT(C, 0);
		P[rt].assign(C, C + n + m - 1);
	}
 
	int E[N];
	void INV(int *A, int *B, int n) {
		if (n == 1) {
			*B = Math::inv(*A);
			return ;
		}
		INV(A, B, n + 1 >> 1);
		init(n + n - 1);
		std::copy(A, A + n, E); clear(E + n, E + lim);
		clear(B + (n + 1 >> 1), B + lim);
		NTT(B), NTT(E);
		for (int i = 0; i < lim; ++i) B[i] = (2 + mod - static_cast<long long> (B[i]) * E[i] % mod) * B[i] % mod;
		NTT(B, 0); clear(B + n, B + lim);
	}
	int F[N];
	void DIV(int A, int n, int B, int m) {
		const int len = n - m + 1;
		init(len << 1);
		std::reverse_copy(S[A].begin(), S[A].end(), C); clear(C + len, C + lim);
		std::reverse_copy(P[B].begin(), P[B].end(), D); clear(D + len, D + lim);
		clear(F, F + lim);
		INV(D, F, len);
		NTT(C), NTT(F);
		for (int i = 0; i < lim; ++i) F[i] = static_cast<long long> (F[i]) * C[i] % mod;
		NTT(F, 0);
		clear(F + len, F + lim);
	}
	void __DIVMOD(int res, int A, int n, int B, int m) {
		if (n < m) {
			S[res].assign(S[A].begin(), S[A].end());
			return ;
		}
		DIV(A, n, B, m);
		init(n);
		std::reverse_copy(F, F + n - m + 1, C); clear(C + n - m + 1, C + lim);
		std::copy(P[B].begin(), P[B].end(), D); clear(D + m, D + lim);
		NTT(C), NTT(D);
		for (int i = 0; i < lim; ++i) C[i] = static_cast<long long> (C[i]) * D[i] % mod;
		NTT(C, 0);
		for (int i = 0; i < m - 1; ++i) reduce(C[i] = S[A][i] - C[i]);
		S[res].assign(C, C + m - 1);
	}
	void DIVMOD(int res, int A) {
		int n = S[A].size(), m = P[res].size();
		__DIVMOD(res, A, n, res, m);
	}
 
	void solve(int rt, int l, int r) {
		if (l == r) {
			ans[l] = S[rt][0];
			return ;
		}
		int mid = l + r >> 1;
		DIVMOD(rt << 1, rt), DIVMOD(rt << 1 | 1, rt);
		solve(rt << 1, l, mid), solve(rt << 1 | 1, mid + 1, r);
	}
 
	void work(int *f, int n, int m) {
		DC_NTT(1, 1, m);
		S[0].assign(f, f + n);
		DIVMOD(1, 0);
		solve(1, 1, m);
	}
#undef N
}

int n, m;
int f[maxn];
const int M=998244353;
int jc[maxn],njc[maxn],inv[maxn];
int binom(int x,int y){
    return 1ll*jc[x]*njc[y]%M*njc[x-y]%M;
}
void init(){
    inv[1]=1; for (int i=2;i<maxn;i++) inv[i]=M-1ll*(M/i)*inv[M%i]%M;
    jc[0]=njc[0]=1; for (int i=1;i<maxn;i++) jc[i]=1ll*jc[i-1]*i%M,njc[i]=1ll*njc[i-1]*inv[i]%M;
}
void inc(int &x,int y){x+=y;if (x>=M)x-=M;}
void dec(int &x,int y){x-=y;if (x<0) x+=M;}
int b[maxn],h[maxn],NN;
bool qry(int x,int y){
    return b[x]>=y;
}

vi solve(int L,int R){
    if (L==R) return (vi){h[L],1};
    int mid=(L+R)>>1;
    vi lp=solve(L,mid);
    vi rp=solve(mid+1,R);
    return FFT::multiply_mod(lp,rp,M);
}
vi chuo(vi &A,int N){
    n=A.size(); m=N+1;
    memset(f,0,sizeof(f));
    memset(a,0,sizeof(a));
    for (int i=0;i<n;i++) f[i]=A[i];
    for (int i=1;i<=m;i++) a[i]=i-1;
	Poly::work(f, n, m);
    vi res(m);
    for (int i=0;i<m;i++) res[i]=ans[i+1];
    return res;
}
void work(){
    int n;
    memset(b,0,sizeof(b));
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&b[i]);
    std::reverse(b+1,b+n+1);
    int r=1;
    while (qry(r+1,r+1)) r++;
    if (qry(r,r+1)&&qry(r+1,r)){
        printf("%d %d\n",r,jc[r]);
        exit(0);
    } 
    int tot=0,sum=0;
    if (!qry(r,r+1)){
        tot++;
        int pos=r;
        for (int i=r;i;i--){
            while (qry(pos+1,i)) ++pos;
            h[i]=pos;
        }
        pos=r;
        while (pos>0&&!qry(pos,r+1)) pos--;
        NN=pos;
        vi A=solve(1,r);
        vi B=chuo(A,NN);
        for (int i=0;i<=NN;i++) 
            if (i&1) dec(sum,1ll*binom(NN,i)*B[i]%M);
            else inc(sum,1ll*binom(NN,i)*B[i]%M);
    }
    if (!qry(r+1,r)){
        tot++;
        int pos=r;
        for (int i=r;i;i--){
            while (qry(i,pos+1)) ++pos;
            h[i]=pos;
        }
        pos=r;
        while (pos>0&&!qry(r+1,pos)) pos--;
        NN=pos;
        vi A=solve(1,r);
        vi B=chuo(A,NN);
        for (int i=0;i<=NN;i++) 
            if (i&1) dec(sum,1ll*binom(NN,i)*B[i]%M);
            else inc(sum,1ll*binom(NN,i)*B[i]%M);
    }
    if (tot==2) dec(sum,jc[r]);
    printf("%d %d\n",r,sum);
}
signed main() {
    init();
    work();
	return 0;
}
