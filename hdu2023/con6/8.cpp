#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 3005
#define INF 1000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,a[MAXN];
ll sum[MAXN];
int pos[MAXN][MAXN];
int dp[MAXN][MAXN];
int stl[MAXN][MAXN],str[MAXN][MAXN];
int sl[MAXN],tl[MAXN];
int sr[MAXN],tr[MAXN];
void addl(int id,int i){
    while(sl[id]<tl[id]&&dp[id][stl[id][tl[id]-1]]>=dp[id][i]) tl[id]--;
	stl[id][tl[id]++]=i;
}
void addr(int id,int i){
    while(sr[id]<tr[id]&&dp[str[id][tr[id]-1]][id]>=dp[i][id]) tr[id]--;
	str[id][tr[id]++]=i;
}
int queryl(int id,int i){
    while(sl[id]<tl[id]&&stl[id][sl[id]]<i) sl[id]++;
    return dp[id][stl[id][sl[id]]];
}
int queryr(int id,int i){
    while(sr[id]<tr[id]&&str[id][sr[id]]>i) sr[id]++;
    //printf("id=%d i=%d pos=%d\n",id,i,str[id][sr[id]]);
    return dp[str[id][sr[id]]][id];
}
int main()
{
    scanf("%d",&T); 
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
        for(int l=1;l<=n-1;l++){
            int p=l-1;
            for(int r=l+1;r<=n;r++){
                while(p+1<r&&sum[p+1]-sum[l-1]<sum[r]-sum[p+1]) p++;
                pos[l][r]=p;
            }
        }
        for(int i=1;i<=n;i++) dp[i][i]=-a[i]; 
        for(int i=1;i<=n;i++) {sl[i]=tl[i]=sr[i]=tr[i]=0; addl(i,i); addr(i,i);}
        for(int len=2;len<=n;len++){
            for(int l=1;l+len-1<=n;l++){
                int r=l+len-1,p=pos[l][r];//can be [x+1,r] for l<=x<=pos and [l,x] for pos+1<=x<=r-1
                int val=INF;
                if(p!=r-1){//rb can be [p+1,r-1] 
                    val=min(val,queryl(l,p+1));
                    //printf("val=%d\n",val);
                }
                if(p!=l-1){//lb can be [l+1,p+1]
                    val=min(val,queryr(r,p+1));
                    //printf("val=%d\n",val);
                }
                dp[l][r]=-val;
                //printf("l=%d r=%d p=%d dp=%d\n",l,r,p,dp[l][r]);
                addl(l,r); addr(r,l);
            }
        }
        if(dp[1][n]>0) printf("Alice %d\n",dp[1][n]); else printf("Bob %d\n",-dp[1][n]);
    }
    return 0;
}

