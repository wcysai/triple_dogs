#include<bits/stdc++.h>
using namespace std;
#define int long long
typedef long long ll;
const int maxn=1e6+10;
const int B=1000000;
int L[maxn][20],R[maxn][20],n,W;
int to[maxn];
set<int> S;
struct frac{
    ll a,b;
}dis[maxn];
bool cmp(frac u,frac v){
    return u.a*v.b<v.a*u.b;
}
void print(ll x,ll y){
    ll g=__gcd(x,y);
    printf("%lld/%lld",x/g,y/g);
}
void init(){
    for (int i=0;i<=B+1;i++){
        for (int j=0;j<20;j++)
            L[i][j]=R[i][j]=i;
    }
    S.insert(0); S.insert(B+1);
}
int sign(int x){
    if (x<0) return -1;
    return x>0;
}
frac intersect(int u,int v){
    if (sign(to[u]-to[v])*sign(u-v)>=0){
        return (frac){1,1};
    }
    return (frac){abs(u-v),abs(u-v)+abs(to[u]-to[v])};
}
signed main(){
    init();
    scanf("%lld%lld",&n,&W);
    for (int i=0;i<n;i++){
        int x,op;
        scanf("%lld",&x);
        scanf("%lld%lld",&to[x],&op);
        auto gt=S.lower_bound(x);
        int v=*gt; gt--;
        int u=*gt;
        frac l,r;
        if (cmp(intersect(u,x),dis[u])){
            l=intersect(u,x);
        } else {
            int uu=L[u][19];
            if (!cmp(intersect(uu,x),dis[uu])){
                l=(frac){1,1};
            } else {
                for (int i=18;i>=0;i--){
                    uu=L[u][i];
                    if (!cmp(intersect(uu,x),dis[uu])) u=uu;
                }
                u=L[u][0];
                l=intersect(u,x);
            }
        }
        if (cmp(intersect(v,x),dis[v])){
            r=intersect(v,x);
        } else {
            int vv=R[v][19];
            if (!cmp(intersect(vv,x),dis[vv])){
                r=(frac){1,1};
            } else {
                for (int i=18;i>=0;i--){
                    vv=R[v][i];
                    if (!cmp(intersect(vv,x),dis[vv])) v=vv;
                }
                v=R[v][0];
                r=intersect(v,x);
            }
        }
        frac one=(frac){1,1};
        if (!cmp(l,one)&&!cmp(r,one)){
            dis[x]=one;
            if (op==1) S.insert(x);
        } else if (cmp(l,r)){
            dis[x]=l;
            if (op==1){
                S.insert(x);
                L[x][0]=u;
                for (int i=1;i<=19;i++)
                    L[x][i]=L[L[x][i-1]][i-1];
            }
        } else {
            dis[x]=r;
            if (op==1){
                S.insert(x);
                R[x][0]=v;
                for (int i=1;i<=19;i++)
                    R[x][i]=R[R[x][i-1]][i-1];
            }
        }
        ll A=dis[x].a,B=dis[x].b;
        printf("(");
        print(A*W,B);
        printf(",");
        print((B-A)*x+A*to[x],B);
        printf(")\n");
    }
    return 0;
}