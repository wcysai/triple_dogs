#include<bits/stdc++.h>
#define MAXN 5005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,w;
string str[MAXN];
int dp[MAXN];
P pre[MAXN];
vector<string> v[MAXN];
int cnt;
bool check(int x)
{
    dp[0]=0;
    for(int i=1;i<=n;i++)
    {
        dp[i]=INF;
        int maxi=0;
        for(int j=1;j<=min(i,x);j++)
        {
            maxi=max(maxi,(int)str[i-j+1].size());
            if(dp[i-j]+maxi+(dp[i-j]?1:0)<dp[i])
            {
                dp[i]=dp[i-j]+maxi+(dp[i-j]?1:0);
                pre[i]=P(i-j,maxi);
            }
        }
        if(dp[i]>w) return false;
    }
    return true;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0); 
    cin>>n>>w;
    for(int i=1;i<=n;i++) cin>>str[i];
    int l=0,r=n;
    while(r-l>1)
    {
        int mid=(l+r)/2;
        if(check(mid)) r=mid; else l=mid;
    }
    check(r);
    int now=n;
    vector<int> len;
    while(now)
    {
        len.push_back(pre[now].S); now=pre[now].F; 
    }  
    reverse(len.begin(),len.end());
    cout<<r<<" "<<(int)len.size()<<endl;
    for(int i=0;i<len.size();i++) cout<<len[i]<<((i==(int)len.size()-1)?"\n":" ");
    now=n;
    while(now)
    {
        for(int j=pre[now].F+1;j<=now;j++) v[j-pre[now].F-1].push_back(str[j]);
        int x=now-pre[now].F-1;
        for(int j=x+1;j<r;j++) v[j].push_back("");
        now=pre[now].F; 
    }
    for(int i=0;i<r;i++)
    {
        reverse(v[i].begin(),v[i].end());
        for(int j=0;j<(int)len.size();j++)
        {
            cout<<v[i][j];
            for(int k=0;k<=len[j]-(int)v[i][j].size();k++) cout<<" ";
        }
        cout<<endl;
    }
    return 0;
}
/*
9 30
algorithm
contest
eindhoven
icpc
nwerc
programming
regional
reykjavik
ru
*/