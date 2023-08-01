#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN],x[MAXN],y[MAXN];
int dp[MAXN];
double check(double slope){
    vector<double> v,dis;
    for(int i=1;i<=n;i++){
        v.push_back(1.0*y[i]-1.0*slope*x[i]);
        dis.push_back(1.0*y[i]-1.0*slope*x[i]);
    }
    sort(dis.begin(),dis.end());
    dis.erase(unique(dis.begin(),dis.end()),dis.end());
    for(int i=0;i<n;i++) v[i]=lower_bound(dis.begin(),dis.end(),v[i])-dis.begin()+1;
    fill(dp,dp+n,INF);
    for(int i=0;i<n;i++) *lower_bound(dp,dp+n,v[i])=v[i];
    return lower_bound(dp,dp+n,INF)-dp>=k;
}
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) scanf("%d%d",&x[i],&y[i]);
    double l=-1e9,r=1e9;
    for(int i=0;i<60;i++){
        double mid=(l+r)/2.0;
        if(check(mid)) l=mid; else r=mid;
    }
    printf("%.10f\n",l);
    return 0;
}

