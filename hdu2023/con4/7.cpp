#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define INF2 1000000000000000000LL
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef unsigned long long ll;
//to achieve best running time, sieve until 2/3 prime factors remaining
int T;
ll n;
int prime[MAXN],phi[MAXN],miu[MAXN];
bool is_prime[MAXN];
int sieve(int n)
{
    int p=0;
    for(int i=0;i<=n;i++) is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;
    for(int i=2;i<=n;i++)
    {
        if(is_prime[i]) prime[p++]=i;
        for(int j=0;j<p;j++)
        {
            if(prime[j]*i>n) break;
            is_prime[prime[j]*i]=false;
            if(i%prime[j]==0) break;
        }
    }
    return p;
}
namespace pollardrho 
{
    ll gcd(ll a, ll b) {return b ? gcd(b, a % b) : a;}

    ll mulmod(ll x,ll y,ll p)
    {
        ll z=(long double)x/p*y;
        ll res=(ll)x*y-(ll)z*p;
        return (res+p)%p;
    }

    ll powmod(ll b, ll e, ll m) 
    {
        ll r = 1;
        while (e) 
        {
            if (e & 1) r = mulmod(r, b, m);
            b = mulmod(b, b, m);
            e >>= 1;
        }
        return r;
    }

    bool test(ll n)
    {
        if (n < 3) return n==2;
        // ! The array a[] should be modified if the range of x changes.
        static const ll a[] = {2, 3, 5, 7, 11, 13, 17, 19, 23,  LLONG_MAX};//works for 1e18
        ll r = 0, d = n-1, x;
        while (~d & 1) d >>= 1, r++;
        for (int i=0; a[i] < n; i++)
        {
            x = powmod(a[i], d, n);
            if (x == 1 || x == n-1) goto next;
            for(int i=0;i<r;i++)
            {
                x = mulmod(x, x, n);
                if (x == n-1) goto next;
            }
            return false;
            next:;
        }
        return true;
    }

}
ll ub[61];
ll calc(ll a,int b){
    ll now=1;
    for(int i=1;i<=b;i++){
        if(INF2/a<now) return INF2+1;
        now=now*a;
    }
    return now;
}
ll find(ll x,int i){
    ll l=1,r=ub[i]+1; 
    while(r-l>1){
        ll mid=(l+r)/2;
        if(calc(mid,i)<=x) l=mid; else r=mid;
    }
    if(calc(l,i)==x) return l; else return -1;
}
int main(){
    for(int i=2;i<=60;i++){
        ll l=1,r=INF+1;
        while(r-l>1){
            ll mid=(l+r)/2;
            if(calc(mid,i)<=INF2) l=mid; else r=mid;
        }
        ub[i]=l;
    }
    int p=sieve(1000000);
    scanf("%d",&T);
    while(T--){
        scanf("%llu",&n);
        bool f=false;
        if(pollardrho::test(n)){
            printf("%llu ",n%MOD); f=true; continue;
        }
        for(int i=2;i<=60;i++){
            ll x=find(n,i);
            if(x==-1) continue;
            if(i==2&&pollardrho::test(x)) {printf("%llu ",n%MOD); f=true; break;}
            if(i>=3&&is_prime[x]) {printf("%llu ",n%MOD); f=true; break;}
        }
        if(!f) printf("1 ");
    }
    printf("\n");
    return 0;
}
