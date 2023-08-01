#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int n,m,u,v,w,ans,res;
int exgcd(int a,int b,int &x,int &y){
    int d=a;
    if (b!=0){
        d=exgcd(b,a%b,y,x);
        y-=(a/b)*x;
    } else {
        x=1;
        y=0;
    }
    return d;
}
int main(){
    cin >> n >> m;
    for (int i=0;i<n;i++){
        int x; cin >> x;
        w=(w+x)%m;
    }
    u=n; v=1ll*n*(n+1)/2%m;
    ans=w%__gcd(__gcd(u,v),m);
    cout << ans << endl;
    int x,y;
    int g=exgcd(u,v,x,y);
    x=(x%m+m)%m; y=(y%m+m)%m;
    int xx,yy;
    int gg=exgcd(g,m,xx,yy);
    xx=(xx%m+m)%m; yy=(yy%m+m)%m;
    x=1ll*x*xx%m; y=1ll*y*xx%m;
    int req=(ans-w+m)%m/gg;
    x=1ll*x*req%m; y=1ll*y*req%m;
    cout << x << ' ' << y << endl;
    //cout << (1ll*x*u+1ll*y*v+w)%m << endl;
}