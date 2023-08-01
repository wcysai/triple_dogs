#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<ll,int>pi;
const int D=56;
int val(pi x){
    return (x.F>>x.S)&1;
}
pi nxt(pi x){
    if (x.S>0) return (pi){x.F,x.S-1};
    int d=63-__builtin_clzll(x.F+1);
    return (pi){x.F+1,d};
}
bool cmp(pi x,pi y){
    if (x==y) return 0;
    if (val(x)!=val(y)) return val(x)>val(y);
    return cmp(nxt(x),nxt(y));
}
pi c1(ll x){
    if (x==1) return (pi){0,0}; x--;
    for (int i=1;i<=D;i++){
        ll tmp=((ll)i)<<(i-1);
        if (x>tmp) {x-=tmp; continue;}
        ll now=1ll<<(i-1);
        now+=(x-1)/i;
        return (pi){now,i-1-(x-1)%i};
    }
    return (pi){-1,-1};
}
int main(){
    int T; scanf("%d",&T);
    while (T--){
        ll l,r; int n;
        scanf("%lld%lld%d",&l,&r,&n); r=r-n+1;
        pi ans=c1(l);
        ll L=c1(l).F,R=c1(r).F;
        if (R-L<=1){
            for (ll x=l+1;x<=r;x++){
                pi cur=c1(x);
                if (cmp(cur,ans)) ans=cur;
            }
        } else {
            while (c1(l).F==L){
                pi cur=c1(l);
                if (cmp(cur,ans)) ans=cur;
                l++;
            }
            while (c1(r).F==R){
                pi cur=c1(r);
                if (cmp(cur,ans)) ans=cur;
                r--;
            }
            L=c1(l).F; R=c1(r).F;
            for (int d=1;d<=D;d++){
                ll Lc,Rc;
                Lc=1ll<<(d-1);
                Rc=(1ll<<d)-1;
                if (max(Lc,L)<=min(Rc,R)){
                    pi cur=(pi){min(Rc,R),d-1};
                    if (cmp(cur,ans)) ans=cur;
                } 
                Rc--; 
                Lc=max(Lc,L); Rc=min(Rc,R);
                if (Lc>Rc) continue;
                for (int j=1;j<d;j++){
                    ll now=(((Rc+1)>>j)<<j)-1;
                    pi cur;
                    if (now<Lc) cur=(pi){Rc,j-1}; else cur=(pi){now,j-1};
                    if (cmp(cur,ans)) ans=cur;
                }
            }
        }
        while (n--){
            printf("%d",val(ans)); 
            ans=nxt(ans);
        }
        puts("");
    }
    return 0;
}