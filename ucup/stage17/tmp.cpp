#include <bits/stdc++.h>
#define MOD 998244353
using namespace std;
typedef vector<int> vi; 
typedef long long ll;
int n;
ll m;

void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void dec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
int pow_mod(int a,int i){
    int s=1;
    while(i){
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
 
vi rev;
vi roots{0,1};
void dft(vi &a) {
    int n=a.size();
    assert((n&(n-1))==0);
    if (int(rev.size()) != n) {
        int k=__builtin_ctz(n)-1;
        rev.resize(n);
        for (int i=0; i<n; i++) {
            rev[i]=rev[i>>1]>>1|(i&1)<<k;
        }
    }
    for (int i=0; i<n; i++) {
        if (rev[i]<i) {
            swap(a[i],a[rev[i]]);
        }
    }
    if (int(roots.size())<n) {
        int k=__builtin_ctz(roots.size());
        roots.resize(n);
        while((1<<k)<n) {
            int e=pow_mod(3,(MOD-1)>>(k+1));
            for (int i=1<<(k-1);i<(1<<k); i++) {
                roots[2*i]=roots[i];
                roots[2*i+1]=1LL*roots[i]*e%MOD; 
            }
            k++;
        }
    }
    for (int k=1;k<n;k*=2) {
        for (int i=0;i<n;i+=2*k) {
            for (int j=0;j<k;j++) {
                int u=a[i+j];
                int v=1LL*a[i+j+k]*roots[k+j]%MOD;
                a[i+j]=u; add(a[i+j],v);
                a[i+j+k]=u; dec(a[i+j+k],v);
            }
        }
    }
}
void idft(vi &a) {
    int n=a.size();
    reverse(a.begin()+1,a.end());
    dft(a);
    int inv=pow_mod(n,MOD-2);
    for (int i=0;i<n;i++) {
        a[i]=1LL*a[i]*inv%MOD;
    }
}
struct Poly {
    vi a;
    Poly() {}
    Poly(const vi &a) : a(a) {}
    Poly(const initializer_list<int> &a) : a(a) {}
    int size() const {
        return a.size();
    }
    void resize(int n) {
        a.resize(n);
    }
    int operator[](int idx) const {
        if (idx<0||idx>=size()) {
            return 0;
        }
        return a[idx];
    }
    int &operator[](int idx) {
        return a[idx];
    }
    Poly mulxk(int k) const {
        auto b=a;
        b.insert(b.begin(),k,0);
        return Poly(b);
    }
    Poly modxk(int k) const {
        k=min(k,size());
        return Poly(vi(a.begin(),a.begin()+k));
    }
    Poly divxk(int k) const {
        if (size()<=k) {
            return Poly();
        }
        return Poly(vi(a.begin()+k,a.end()));
    }
    friend Poly operator+(const Poly &a,const Poly &b) {
        vi res(max(a.size(),b.size()));
        for (int i=0;i<int(res.size());i++) {
            res[i]=a[i]; add(res[i],b[i]);
        }
        return Poly(res);
    }
    friend Poly operator-(const Poly &a,const Poly &b) {
        vi res(max(a.size(),b.size()));
        for (int i=0;i<int(res.size());i++) {
            res[i]=a[i]; dec(res[i],b[i]); 
        }
        return Poly(res);
    }
    friend Poly operator*(Poly a,Poly b) {
        if (a.size()==0||b.size()==0) {
            return Poly();
        }
        int sz=1,tot=a.size()+b.size()-1;
        while(sz<tot)
            sz *= 2;
        a.a.resize(sz); b.a.resize(sz);
        dft(a.a); dft(b.a);
        for (int i=0;i<sz;i++) {
            a.a[i]=1LL*a[i]*b[i]%MOD;
        }
        idft(a.a);
        a.resize(tot);
        return a;
    }
    friend Poly operator*(int a,Poly b) {
        for (int i=0;i<int(b.size());i++) {
            b[i]=1LL*b[i]*a%MOD;
        }
        return b;
    }
    friend Poly operator*(Poly a,ll b) {
        for (int i=0; i<int(a.size()); i++) {
            a[i]=1LL*a[i]*(b%MOD)%MOD;
        }
        return a;
    }
    Poly &operator+=(Poly b) {
        return (*this)=(*this)+b;
    }
    Poly &operator-=(Poly b) {
        return (*this)=(*this)-b;
    }
    Poly &operator*=(Poly b) {
        return (*this)=(*this)*b;
    }
    Poly deriv() const {
        if (a.empty()) {
            return Poly();
        }
        vi res(size()-1);
        for (int i=0; i<size()-1; ++i) {
            res[i]=1LL*(i+1)*a[i+1]%MOD;
        }
        return Poly(res);
    }
    Poly integr() const {
        vi res(size()+1);
        for (int i=0; i<size(); ++i) {
            res[i+1]=1LL*a[i]*pow_mod(i+1,MOD-2)%MOD;
        }
        return Poly(res);
    }
    Poly inv(int m) const {
        Poly x{pow_mod(a[0],MOD-2)};
        int k=1;
        while (k<m) {
            k *= 2;
            x=(x*(Poly{2}-modxk(k)*x)).modxk(k);
        }
        return x.modxk(m);
    }
    Poly log(int m) const {
        return (deriv()*inv(m)).integr().modxk(m);
    }
    Poly exp(int m) const {
        Poly x{1};
        int k=1;
        while (k<m) {
            k*=2;
            x=(x*(Poly{1}-x.log(k)+modxk(k))).modxk(k);
        }
        return x.modxk(m);
    }
    Poly pow(ll k,int m) const {
        if(k==0){
            Poly p; p.resize(m);
            p.a[0]=1;
            return p;
        }
        int i=0;
        while (i<size()&&a[i]==0) {
            i++;
        }
        if (i==size()||1LL*i*k>=m) {
            return Poly(vi(m));
        }
        int v=a[i];
        auto f=divxk(i)*pow_mod(v,MOD-2);
        return (f.log(m-i*k)*k).exp(m-i*k).mulxk(i*k)*pow_mod(v,k%(MOD-1));
    }
    Poly sqrt(int m) const {
        Poly x{1};
        int k=1;
        while (k<m) {
            k*=2;
            x=(x+(modxk(k)*x.inv(k)).modxk(k))*((MOD+1)/2);
        }
        return x.modxk(m);
    }
    Poly mulT(Poly b) const {
        if (b.size()==0) {
            return Poly();
        }
        int n=b.size();
        reverse(b.a.begin(),b.a.end());
        return ((*this)*b).divxk(n-1);
    }
    vi eval(vi x) const {
        if (size()==0) {
            return vi(x.size(),0);
        }
        const int n=max(int(x.size()),size());
        vector<Poly> q(4*n);
        vi ans(x.size());
        x.resize(n);
        function<void(int,int,int)> build=[&](int p,int l,int r) {
            if (r-l==1) {
                q[p]=Poly{1,MOD-x[l]};
            } else {
                int m=(l+r) / 2;
                build(2*p,l,m);
                build(2*p+1,m,r);
                q[p]=q[2*p]*q[2*p+1];
            }
        };
        build(1,0,n);
        function<void(int,int,int,const Poly &)> work=[&](int p,int l,int r,const Poly &num) {
            if (r-l==1) {
                if (l<int(ans.size())) {
                    ans[l]=num[0];
                }
            } else {
                int m=(l+r)/2;
                work(2*p,l,m,num.mulT(q[2*p+1]).modxk(m-l));
                work(2*p+1,m,r,num.mulT(q[2*p]).modxk(r-m));
            }
        };
        work(1,0,n,mulT(q[1].inv(n)));
        return ans;
    }
};
int main(){
    scanf("%d%lld",&n,&m);
    vector<int> a; a.resize(n); 
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    Poly v(a); v=v.pow(m,n);
    for(auto x:v.a) printf("%d ",x);
    printf("\n");
    return 0;
}
