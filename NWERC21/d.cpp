#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int maxn=2e6+5;
const int inf=1e7;
const int N=1e6;
int n,p,L,R,xl,xr,yl,yr,ans;
int A,B;
vector<int> a[maxn];
int main(){
    scanf("%d",&n); 
    L=N*2; R=0;
    A=B=inf;
    bool ok1=0,ok2=0;
    for (int i=0;i<n;i++){
        int x,y; scanf("%d%d",&x,&y);
        if (x+y!=A){
            if (A==inf) A=x+y; else ok1=1;
        }
        if (x-y!=B){
            if (B==inf) B=x-y; else ok2=1;
        }
        a[x+N].pb(y);
        L=min(L,x+N);
        R=max(R,x+N);
    }
    for (int i=L;i<=R;i++) sort(a[i].begin(),a[i].end());
    xl=xr=a[L][0]-1;
    yl=yr=a[L][a[L].size()-1]+1;
    ans=yl-xl+1;
    for (int i=L+1;i<=R;i++){
        ans+=2;
        //int ox=(yl==yr&&xr==yl-2);
        //int oy=(xl==xr&&yl==xr+2);
        xl--;
        xr++;
        yl--;
        yr++;
        if (a[i].size()){
            int u=a[i][0];
            int v=a[i][a[i].size()-1];
            xr=min(xr,u-1);
            yl=max(yl,v+1);
        }
        if (xr<xl){
            ans+=xl-xr;
            xl=xr;
        } 
        if (yr<yl){
            ans+=yl-yr;
            yr=yl;
        }
    }
    ans+=yl-xr-1;
    if (n>1&&(!ok1||!ok2)) ++ans;
    cout << ans << endl;
}