#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 100000000000000LL
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,m,q,a[MAXN];
int c[MAXN],x[MAXN];
ll sumc[MAXN],sumx[MAXN];
bool vx[MAXN],vc[MAXN];
set<int> sc,sx;
void toggle_c(int id){
    vc[id]=!vc[id];
    if(vc[id]) sc.insert(id); else sc.erase(id);
}
void toggle_x(int id){
    vx[id]=!vx[id];
    if(vx[id]) sx.insert(id); else sx.erase(id);
}
bool on_cyc(int x){
    return x>=1&&x<=n;
}
bool on_line(int x){
    return (x>=n+1&&x<=n+m)||(x==1)||(x==k);
}
ll cyc_dist(int x,int y){
    //assert(x>=1&&x<=n); assert(y>=1&&y<=n);
    if(x>y) swap(x,y);
    ll d=INF;
    if(sc.lower_bound(x)==sc.end()||*sc.lower_bound(x)>=y) d=min(d,sumc[y-1]-sumc[x-1]);
    if(sc.lower_bound(y)==sc.end()&&(sc.begin()==sc.end()||*sc.begin()>=x)) d=min(d,sumc[n]-sumc[y-1]+sumc[x-1]);
    return d;
}
ll line_dist(int x,int y){
    if(k==1){
        if(y==1) swap(x,y);
        if(x==1){
            ll d=INF;
            if(sx.lower_bound(1)==sc.end()||*sc.lower_bound(1)>=y) d=min(d,sumx[y-1]);
            if(sx.lower_bound(y)==sc.end()) d=min(d,sumx[m+1]-sumx[y-1]);
            return d;
        }
    }
    //assert(on_line(x)); assert(on_line(y));
    if(x==1) x=n; else if(x==k) x=n+m+1; 
    if(y==1) y=n; else if(y==k) y=n+m+1;
    x-=n-1; y-=n-1; if(x>y) swap(x,y);
    ll d=INF;
    if(sx.lower_bound(x)==sx.end()||*sx.lower_bound(x)>=y) d=min(d,sumx[y-1]-sumx[x-1]);
    return d;
}
char ch[3];
int main()
{
    scanf("%d%d%d%d",&n,&k,&m,&q);
    for(int i=1;i<=n;i++) scanf("%d",&c[i]);
    for(int i=1;i<=m+1;i++) scanf("%d",&x[i]);
    for(int i=1;i<=n;i++) sumc[i]=sumc[i-1]+c[i];
    for(int i=1;i<=m+1;i++) sumx[i]=sumx[i-1]+x[i];
    memset(vx,false,sizeof(vx)); memset(vc,false,sizeof(vc));
    for(int i=0;i<q;i++){
        scanf("%s",ch);
        if(ch[0]=='q'){
            int x,y;
            scanf("%d%d",&x,&y);
            ll ans=INF;
            if(on_line(x)&&on_line(y)) 
            {
                ans=min(ans,line_dist(x,y));
                ans=min(ans,line_dist(x,1)+cyc_dist(1,k)+line_dist(k,y));
                ans=min(ans,line_dist(x,k)+cyc_dist(1,k)+line_dist(1,y));
            }
            else if(on_cyc(y)&&on_cyc(x)) 
            {
                ans=min(ans,cyc_dist(x,y));
                ans=min(ans,cyc_dist(x,1)+line_dist(1,k)+cyc_dist(k,y));
                ans=min(ans,cyc_dist(x,k)+line_dist(1,k)+cyc_dist(1,y));
            }
            if(on_line(y)&&on_cyc(x)) swap(x,y);
            if(on_cyc(y)&&on_line(x)){
                ans=min(ans,line_dist(x,1)+cyc_dist(1,y));
                ans=min(ans,line_dist(x,k)+cyc_dist(k,y));
            }
            if(ans==INF) printf("impossible\n"); else printf("%lld\n",ans);
        }
        else if(ch[0]=='x'){
            int x; scanf("%d",&x);
            toggle_x(x+1);
        }
        else{
            int x; scanf("%d",&x);
            toggle_c(x);
        }
    }
    return 0;
}

