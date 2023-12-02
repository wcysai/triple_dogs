#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,t,x[MAXN],y[MAXN],xh,yh,xe,ye;
double a[MAXN][MAXN],dist[MAXN][MAXN];
vector<int> inter;
int main()
{
    scanf("%d%d",&n,&t);
    scanf("%d%d%d%d",&xh,&yh,&xe,&ye);
    for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
    double ans=sqrt(1.0*(xh-xe)*(xh-xe)+1.0*(yh-ye)*(yh-ye));
    for(int i=1;i<=n;i++){
        int dh=min(max(x[i]-xh,xh-x[i]),max(y[i]-yh,yh-y[i]));
        int de=min(max(x[i]-xe,xe-x[i]),max(y[i]-ye,ye-y[i]));
        if(dh+de+t<ans){
            ans=dh+de+t; inter.clear();
            inter.push_back(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int dh=min(max(x[i]-xh,xh-x[i]),max(y[i]-yh,yh-y[i]));
            int de=min(max(x[j]-xe,xe-x[j]),max(y[j]-ye,ye-y[j]));
            if(dh+de+2*t<ans){
                ans=dh+de+2*t; inter.clear();
                inter.push_back(i); inter.push_back(j);
            }
        }
    }
    printf("%.10f\n",ans);
    if(inter.size()==0){
        printf("1\n");
        printf("0 %d %d\n",xe,ye);
    }
    else if(inter.size()==1){
        int i=inter[0];
        printf("3\n");
        int dx=max(x[i]-xh,xh-x[i]),dy=max(y[i]-yh,yh-y[i]);
        if(dx<dy) printf("%d %d %d\n",0,x[i],yh); else printf("%d %d %d\n",0,xh,y[i]);
        dx=max(x[i]-xe,xe-x[i]); dy=max(y[i]-ye,ye-y[i]);
        if(dx<dy) printf("%d %d %d\n",i,x[i],ye); else printf("%d %d %d\n",i,xe,y[i]);
        printf("0 %d %d\n",xe,ye);
    }
    else{
        int i=inter[0],j=inter[1];
        printf("4\n");
        int dx=max(x[i]-xh,xh-x[i]),dy=max(y[i]-yh,yh-y[i]);
        int curx,cury;
        if(dx<dy) 
        {
            printf("%d %d %d\n",0,x[i],yh); 
            curx=x[i]; cury=yh;
        }
        else 
        {
            printf("%d %d %d\n",0,xh,y[i]);
            curx=xh; cury=y[i];
        }
        printf("%d %d %d\n",i,x[j],y[i]); 
        dx=max(x[j]-xe,xe-x[j]); dy=max(y[j]-ye,ye-y[j]);
        if(dx<dy) printf("%d %d %d\n",j,x[j],ye); else printf("%d %d %d\n",j,xe,y[j]);
        printf("0 %d %d\n",xe,ye);
    }
    return 0;
}

