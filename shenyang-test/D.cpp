#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN];
char s[MAXN],t[MAXN];
ll ans;
int lcs[MAXN][MAXN],tmp[MAXN][MAXN];
int cont[MAXN],cnt[MAXN];
void get_ans(){
    memset(lcs,0,sizeof(lcs));
    memset(tmp,0,sizeof(tmp));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if(s[i]==t[j]) lcs[i][j]=lcs[i-1][j-1]+1;
            else lcs[i][j]=0;
        }
    for(int i=n;i>=1;i--)
        for(int j=n;j>=i;j--){
            if(s[i]==s[j]) tmp[i][j]=tmp[i+1][j+1]+1;
            else tmp[i][j]=0;
        }
    for(int i=1;i<=n;i++){
        memset(cnt,0,sizeof(cnt));
        memset(cont,0,sizeof(cont));
        for(int j=1;j<=i-1;j++){
            int len=i-j;
            int r=len-1,l=max(1,len-tmp[j][i]);
            if(l<=r){cont[l]++; cont[r+1]--;}
        }
        for(int j=1;j<=m;j++){
            int len=lcs[i-1][j];
            cnt[1]++; cnt[len+1]--;
        }
        for(int j=1;j<=max(n,m);j++) cnt[j]+=cnt[j-1];
        for(int j=1;j<=max(n,m);j++) cont[j]+=cont[j-1];
        for(int j=1;j<=max(n,m);j++) ans+=1LL*cnt[j]*cont[j];
    }
}
int main()
{
    scanf("%s",s+1);
    scanf("%s",t+1);
    n=strlen(s+1); m=strlen(t+1);
    get_ans();
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ans+=lcs[i][j];
    swap(s,t);
    swap(n,m);
    reverse(s+1,s+n+1);
    reverse(t+1,t+m+1);
    get_ans();
    printf("%lld\n",ans);
    return 0;
}

