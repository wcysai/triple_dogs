#include<bits/stdc++.h>
#define pb push_back
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> pp;
const int maxn=1e6+10;
struct node{
    ll x,y;
    ll operator^(const node &u){
        return x*u.y-y*u.x;
    }
    node operator-(const node &u){
        return (node){x-u.x,y-u.y};
    }
    void read(){
        scanf("%lld%lld",&x,&y);
    }
};
typedef pair<node,int> pi;
ll sqr(ll x){
    return x*x;
}
ll dis(node u){
    return sqr(u.x)+sqr(u.y);
}
vector<node> a,b;
int n,cnt1,cnt2;
ll ans;
int fo;
node p,q,o;
int sign(ll x){
    if (x<0) return -1;
    return x>0;
}
bool cmp(pi x,pi y){
    node &u=x.F,&v=y.F;
    int op=sign((u-o)^(v-o));
    if (op==0) return dis(u-o)<dis(v-o);
    return op==fo;
}
int c[maxn],x[maxn],y[maxn];
void add(int &x,int y){
    while (x<maxn) c[x]+=y,x+=x&(-x);
}
int qry(int x){
    int ret=0;
    while (x) ret+=c[x],x-=x&(-x);
    return ret;
}
ll solve(vector<node> &A){
    int n=A.size();
    vector<pi> tmp; tmp.resize(n);
    for (int i=0;i<n;i++) tmp[i]=(pi){A[i],i};
    o=p; fo=1; sort(tmp.begin(),tmp.end(),cmp);
    for (int i=0;i<n;i++) x[tmp[i].S]=i+1;
    o=q; fo=-1; sort(tmp.begin(),tmp.end(),cmp);
    for (int i=0;i<n;i++) y[tmp[i].S]=i+1;
    memset(c,0,sizeof(c));
    vector<pp> tt; tt.resize(n);
    for (int i=0;i<n;i++) tt[i]=(pp){x[i],y[i]};
    sort(tt.begin(),tt.end());
    ll ret=0;
    for (int i=0;i<n;i++){
        ret+=qry(tt[i].S-1);
        add(tt[i].S,1);
    }
    return ret;
}
int main(){
    p.read(); q.read();
    scanf("%d",&n);
    for (int i=1;i<=n;i++){
        node x; x.read();
        int op=sign((x-p)^(q-p));
        if (op==-1) a.pb(x);
        else if (op==1) b.pb(x);
        else if (dis(x-p)<dis(x-q)) cnt1++;
        else cnt2++;
    }
    ans+=1ll*cnt1*(cnt1-1)/2;
    ans+=1ll*cnt2*(cnt2-1)/2;
    ans+=solve(a); swap(p,q);
    ans+=solve(b);
    printf("%lld\n",ans);
    return 0;
}