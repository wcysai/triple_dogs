#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 55
#define MAXM 2005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,q,tot,a[MAXN];
char s[MAXN];
int f[MAXN];
map<vector<int>,int> id;
int len[MAXN];
int dp[MAXN][MAXN];
int solve1(){
    for(int i=1;i<=n;i++) dp[i][i]=(s[i]-'0');
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            dp[i][j]=max(-dp[i+1][j]+s[i]-'0',-dp[i][j-1]+s[j]-'0');
        }
    }
    return dp[1][n];
}
int solve2(){
    vector<int> v;
    for(int i=1;i<=n;i++){
        v.push_back(s[i]-'0');
        int sz=(int)v.size();
        if(sz>=2&&v[sz-1]==2&&v[sz-2]==2){
            v.pop_back(); v.pop_back();
        }
        if(sz>=3&&v[sz-1]==1&&v[sz-2]==1&&v[sz-3]==1){
            v.pop_back(); v.pop_back();
        }
    }
    if(!v.size()) return 0;
    n=(int)v.size();
    for(int i=1;i<=n;i++) dp[i][i]=v[i-1];
    for(int len=2;len<=n;len++){
        for(int i=1;i+len-1<=n;i++){
            int j=i+len-1;
            dp[i][j]=max(-dp[i+1][j]+v[i-1],-dp[i][j-1]+v[j-1]);
        }
    }
    return dp[1][n];
}
int main()
{
    f[1]=1; f[2]=1;
    int sum=0;
    for(int i=3;i<=50;i++) {f[i]=f[i-2]+f[i-3]; sum+=f[i];}
    printf("%d\n",sum);
    scanf("%d",&T);
    while(T--){
        scanf("%s",s+1);
        n=strlen(s+1);
        int x=solve1(),y=solve2();
        printf("x=%d y=%d\n",x,y);
        assert(x==y);
    }
    return 0;
}

