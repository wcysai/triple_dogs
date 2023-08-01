#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 105
#define MAXX 10005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,x,a[MAXN];
int dp[MAXN][MAXX];
void upd(int &x,int y) {x=max(x,y);}
int main()
{
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    vector<int> v; int tmp=x;
    while(tmp){
        v.push_back(tmp%10);
        tmp/=10;
    }
    memset(dp,-1,sizeof(dp));
    sort(v.begin(),v.end());
    do{
        int now=0;
        for(int j=0;j<v.size();j++) now=now*10+v[j];
        dp[0][now]=0;
    }while(next_permutation(v.begin(),v.end()));
    for(int i=0;i<n;i++){
        for(int j=0;j<10000;j++){
            if(dp[i][j]==-1) continue;
            if(j>=a[i+1]){
                v.clear(); int tmp=j-a[i+1];
                while(tmp){
                    v.push_back(tmp%10);
                    tmp/=10;
                }
                sort(v.begin(),v.end());
                do{
                    int now=0;
                    for(int j=0;j<v.size();j++) now=now*10+v[j];
                    upd(dp[i+1][now],dp[i][j]+1);
                }while(next_permutation(v.begin(),v.end()));
            }
            upd(dp[i+1][j],dp[i][j]);
        }
    }
    int ans=0;
    for(int j=0;j<10000;j++) upd(ans,dp[n][j]);
    printf("%d\n",ans);
    return 0;
}

