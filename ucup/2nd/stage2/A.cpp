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
int n,k,a[MAXN];
char str[MAXN];
int nxt[MAXN][26],pre[MAXN][26];
int ans;
string s="spbsu";
void solve(int x,int y){
    int now=x,res=0,tmp=1;
    for(int i=y-1;i>=0;i--){
        now=pre[now-1][s[i]-'a'];
        if(now==0) return;
        res+=x-now-tmp;
        tmp++;
    }
    tmp=1; now=x;
    for(int i=y+1;i<5;i++){
        now=nxt[now+1][s[i]-'a'];
        if(now==n+1) return;
        res+=now-x-tmp;
        tmp++;
    }
    ans=min(ans,res);
}
int main()
{
    scanf("%d",&n);
    scanf("%s",str+1);
    for(int j=0;j<26;j++) nxt[n+1][j]=n+1;
    for(int j=0;j<26;j++) pre[0][j]=0;
    for(int i=n;i>=1;i--)
        for(int j=0;j<26;j++) 
            nxt[i][j]=(str[i]=='a'+j?i:nxt[i+1][j]);
    for(int i=1;i<=n;i++)
        for(int j=0;j<26;j++)
            pre[i][j]=(str[i]=='a'+j?i:pre[i-1][j]);
    ans=INF;
    for(int i=1;i<=n;i++)
        for(int j=0;j<5;j++)
            if(str[i]==s[j]) solve(i,j);
    printf("%d\n",ans);
    return 0;
}

