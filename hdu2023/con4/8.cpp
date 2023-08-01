#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int maxn=1e6+3;
const int M=998244353;
int f[maxn],phi[maxn];
vector<int> p[maxn];
char s[maxn];
void add(int &x,int y){x+=y;if(x>=M)x-=M;}
int exgcd(int a,int b,int &x,int &y){
    if (!b) return x=1,y=0,a;
    int d=exgcd(b,a%b,x,y),t=x;
    return x=y,y=t-a/b*y,d;
}
int sol(int l,int r,int d,int x){
    int u,v;
    int gg=exgcd(d,x,u,v);//u=d^(-1)
    if (l%gg) return 0;
    l/=gg; r/=gg; d/=gg; x/=gg; 
    u=(u%x+x)%x;
    int w=(x-l%x)%x;
    w=1ll*w*u%x;
    int len=(r-l)/d;
    if (w>len) return 0;
    return (len-w)/x+1;
}
int sol2(int l,int r,int d,int x){
    int ret=0;
    for (auto y:p[x]) add(ret,1ll*phi[y]*sol(l,r,d,y)%M);
    return ret;
}
void getfail(char *s){
    int m=strlen(s+1);
    f[0]=f[1]=0;
    for (int i=2;i<=m;i++){
        int j=f[i-1];
        while (j>0&&s[j+1]!=s[i]) j=f[j]; 
        if (s[j+1]==s[i]) f[i]=j+1; else f[i]=0;
    }
}
int ans[maxn];
void solve(){
    scanf("%s",s+1);
    int n=strlen(s+1);
    getfail(s);
    for (int i=1;i<=n;i++){
        int cur=f[i]; ans[i]=0;
        while (cur>0){
            int d=cur-f[cur];
            add(ans[i],sol2(d+cur%d,cur,d,i));
            cur%=d;
        }
    }
    int ss=1;
    for (int i=1;i<=n;i++) ss=1ll*ss*(ans[i]+1)%M;
    cout << ss << endl;
}
int main(){
    for (int i=1;i<maxn;i++) phi[i]=i;
    for (int i=1;i<maxn;i++)
        for (int j=2;j*i<maxn;j++) phi[i*j]-=phi[i];
    for (int i=1;i<maxn;i++)
        for (int j=1;j*i<maxn;j++) p[i*j].pb(i);
    int _; scanf("%d",&_);
    while (_--) solve();
}
