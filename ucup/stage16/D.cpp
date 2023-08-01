#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
typedef vector<int> vi; 
typedef long long ll;
typedef unsigned long long ull;
namespace Math {
	inline int pw(int base, int p) {
		static int res;
		for (res = 1; p; p >>= 1, base = static_cast<long long> (base) * base % mod) if (p & 1) res = static_cast<long long> (res) * base % mod;
		return res;
	}
	inline int inv(int x) { return pw(x, mod - 2); }
}
inline void reduce(int &x) { x += x >> 31 & mod; }
#define maxn 262144
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
    vector<num> roots={{0,0},{1,0}};
    vector<int> rev={0,1};
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
    void fft(vector<num> &a,int n=-1){
        if(n==-1) n=a.size();
        assert((n&(n-1))==0);
        int zeros=__builtin_ctz(n);
        ensure_base(zeros);
        int shift=base-zeros;
        for(int i=0;i<n;i++)
            if(i<(rev[i]>>shift))
                swap(a[i],a[rev[i]>>shift]);
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
    vector<num> fa,fb;
    vector<ll> multiply(vector<int> &a, vector<int> &b){
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
        vector<ll> res(need);
        for(int i=0;i<need;i++) res[i]=fa[i].x+0.5;
        return res;
    }
    vector<int> multiply_mod(vector<int> &a,vector<int> &b,int m,int eq=0){
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
        vector<int> res(need);
        for(int i=0;i<need;i++){
            ll aa=fa[i].x+0.5;
            ll bb=fb[i].x+0.5;
            ll cc=fa[i].y+0.5;
            res[i]=(aa+((bb%m)<<15)+((cc%m)<<30))%m;
        }
        return res;
    }
    vector<int> square_mod(vector<int> &a,int m){
        return multiply_mod(a,a,m,1);
    }
};
const int G=3;  
const int N=400005;                    
int A[N],B[N],w[2][N],mem[N*100],*ptr=mem;      
inline int qpow(int x,int y) 
{
    int tmp=1;     
    for(;y;y>>=1,x=(ll)x*x%mod) if(y&1) tmp=(ll)tmp*x%mod;  
    return tmp;    
}      
inline int INV(int a) { return qpow(a,mod-2); }        
inline void ntt_init(int len) 
{
    int i,j,k,mid,x,y;      
    w[1][0]=w[0][0]=1,x=qpow(3,(mod-1)/len),y=qpow(x,mod-2);
    for (i=1;i<len;++i) w[0][i]=(ll)w[0][i-1]*x%mod,w[1][i]=(ll)w[1][i-1]*y%mod;         
}
void NTT(int *a,int len,int flag) 
{
    int i,j,k,mid,x,y;                
    for(i=k=0;i<len;++i) 
    {
        if(i>k)    swap(a[i],a[k]);  
        for(j=len>>1;(k^=j)<j;j>>=1);  
    }   
    for(mid=1;mid<len;mid<<=1)            
        for(i=0;i<len;i+=mid<<1) 
            for(j=0;j<mid;++j)          
            {
                x=a[i+j], y=(ll)w[flag==-1][len/(mid<<1)*j]*a[i+j+mid]%mod;  
                a[i+j]=(x+y)%mod;  
                a[i+j+mid]=(x-y+mod)%mod;   
            }   
    if(flag==-1)  
    {
        int rev=INV(len);   
        for(i=0;i<len;++i) a[i]=(ll)a[i]*rev%mod;   
    }
}              
inline void getinv(int *a,int *b,int len,int la) 
{
    if(len==1) { b[0]=INV(a[0]);   return; }
    getinv(a,b,len>>1,la);    
    int l=len<<1,i;   
    memset(A,0,l*sizeof(A[0]));              
    memset(B,0,l*sizeof(A[0]));    
    memcpy(A,a,min(la,len)*sizeof(a[0]));                                                      
    memcpy(B,b,len*sizeof(b[0]));             
    ntt_init(l);   
    NTT(A,l,1),NTT(B,l,1);      
    for(i=0;i<l;++i)  A[i]=((ll)2-(ll)A[i]*B[i]%mod+mod)*B[i]%mod;
    NTT(A,l,-1);                                 
    memcpy(b,A,len<<2);          
}  
struct poly 
{
    int len,*a;    
    poly(){}       
    poly(int l) {len=l,a=ptr,ptr+=l; }            
    inline void rev() { reverse(a,a+len); }       
    inline void fix(int l) {len=l,a=ptr,ptr+=l;}   
    inline void get_mod(int l) { for(int i=l;i<len;++i) a[i]=0;  len=l;  }
    inline poly dao() 
    {        
        poly re(len-1);   
        for(int i=1;i<len;++i)  re.a[i-1]=(ll)i*a[i]%mod;         
        return re;    
    }    
    inline poly Inv(int l) 
    {  
        poly b(l);              
        getinv(a,b.a,l,len);                                  
        return b;                        
    }                                                                    
    inline poly operator * (const poly &b) const 
    {
        poly c(len+b.len-1);   
        if(c.len<=500) 
        {         
            for(int i=0;i<len;++i)   
                if(a[i])   for(int j=0;j<b.len;++j)  c.a[i+j]=(c.a[i+j]+(ll)(a[i])*b.a[j])%mod;      
            return c; 
        }
        int n=1;    
        while(n<(len+b.len)) n<<=1; 
        memset(A,0,n<<2);  
        memset(B,0,n<<2);   
        memcpy(A,a,len<<2);                             
        memcpy(B,b.a,b.len<<2);            
        ntt_init(n);        
        NTT(A,n,1), NTT(B,n,1);     
        for(int i=0;i<n;++i) A[i]=(ll)A[i]*B[i]%mod;   
        NTT(A,n,-1);   
        memcpy(c.a,A,c.len<<2);  
        return c;       
    }    
    poly operator + (const poly &b) const 
    {
        poly c(max(len,b.len));    
        for(int i=0;i<c.len;++i)  c.a[i]=((i<len?a[i]:0)+(i<b.len?b.a[i]:0))%mod;   
        return c;    
    }
    poly operator - (const poly &b) const 
    {    
        poly c(len);       
        for(int i=0;i<len;++i)   
        {
            if(i>=b.len)   c.a[i]=a[i];  
            else c.a[i]=(a[i]-b.a[i]+mod)%mod;    
        } 
        return c;  
    }
    poly operator / (poly u) 
    {  
        int n=len,m=u.len,l=1;  
        while(l<(n-m+1)) l<<=1;                           
        rev(),u.rev();            
        poly v=u.Inv(l);    
        v.get_mod(n-m+1);        
        poly re=(*this)*v;   
        rev(),u.rev();    
        re.get_mod(n-m+1);         
        re.rev();  
        return re;   
    }      
    poly operator % (poly u) 
    {      
        poly re=(*this)-u*(*this/u);        
        re.get_mod(u.len-1);       
        return re;    
    }                     
}p[N<<2],pr;    
int xx[N],yy[N];              
#define lson now<<1  
#define rson now<<1|1           
inline void pushup(int l,int r,int now)
{
    int mid=(l+r)>>1;      
    if(r>mid)   p[now]=p[lson]*p[rson]; 
    else p[now]=p[lson];   
}
void build(int l,int r,int now,int *pp) 
{
    if(l==r) 
    {     
        p[now].fix(2);  
        p[now].a[0]=mod-pp[l];  
        p[now].a[1]=1;   
        return; 
    }  
    int mid=(l+r)>>1;   
    if(l<=mid)  build(l,mid,lson,pp);     
    if(r>mid)   build(mid+1,r,rson,pp);          
    p[now]=p[lson]*p[rson];   
}    
void get_val(int l,int r,int now,poly b,int *pp,int *t) 
{
    if(b.len<=500)     
    {   
        for(int i=l;i<=r;++i) 
        {
            ull s=0;             
            for(int j=b.len-1;j>=0;--j)     
            {
                s=((ull)s*pp[i]+b.a[j])%mod;  
                if(!(j&7))   s%=mod;       
            }
            t[i]=s%mod;   
        }
        return;  
    } 
    int mid=(l+r)>>1;     
    if(l<=mid)   get_val(l,mid,lson,b%p[lson],pp,t);  
    if(r>mid)    get_val(mid+1,r,rson,b%p[rson],pp,t);     
}   
poly solve_polate(int l,int r,int now,int *t) 
{
    if(l==r) 
    {
        poly re(1);   
        re.a[0]=t[l];   
        return re;   
    } 
    int mid=(l+r)>>1;    
    poly L,R;  
    L=solve_polate(l,mid,lson,t);   
    R=solve_polate(mid+1,r,rson,t);   
    return L*p[rson]+R*p[lson];           
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
    if (L==R) return (vi){h[L],M-1};
    int mid=(L+R)>>1;
    vi lp=solve(L,mid);
    vi rp=solve(mid+1,R);
    return FFT::multiply_mod(lp,rp,M);
}
vi chuo(vi &A,int NN){
    n=A.size(); m=NN+1;
    memset(f,0,sizeof(f));
    memset(a,0,sizeof(a));
    static int pp[N]; 
    pr.fix(n);
    for (int i=0;i<n;i++) pr.a[i]=A[i];
    for (int i=1;i<=m;i++) pp[i]=i-1;
    build(1,m,1,pp);
    get_val(1,m,1,pr,pp,pp);
    vi res(m);
    for (int i=0;i<m;i++) res[i]=pp[i+1];
    return res;
}
void work(){
    int n;
    memset(b,0,sizeof(b));
    scanf("%d",&n);
    for (int i=1;i<=n;i++) scanf("%d",&b[i]);
    reverse(b+1,b+n+1);
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
int main() {
    init();
    work();
	return 0;
}
