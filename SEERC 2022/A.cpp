#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
string s,t;
int nxt[26][MAXN];
int main()
{
    cin>>s>>t;
    n=(int)s.size(); m=(int)t.size();
    for(int i=0;i<26;i++) nxt[i][n]=n;
    for(int i=n-1;i>=0;i--)
    {
        for(int j=0;j<26;j++) nxt[j][i]=nxt[j][i+1];
        nxt[s[i]-'a'][i]=i;
    }
    int cnt=1,now=0;
    for(int i=0;i<m;i++)
    {
        int ch=t[i]-'a';
        if(nxt[ch][now]==n) {now=0; cnt++;}
        now=nxt[ch][now]+1;
    }
    printf("%d\n",cnt);
    return 0;
}

