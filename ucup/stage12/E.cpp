#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 998244353
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[5][MAXN],tmp[5];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
vector<P> v;
int main()
{
    scanf("%d",&n);
    for(int i=0;i<5;i++){
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
            v.push_back(P(a[i][j],i));
        }
    }
    sort(v.begin(),v.end());
    int ans=0;
    for(int i=0;i<(int)v.size();i++){
        vector<int> cnt;
        for(int j=0;j<5;j++){
            if(j==v[i].S) continue;
            cnt.push_back(tmp[j]);
        }
        int x=0;
        add(x,1LL*cnt[0]*cnt[1]%MOD*(n-cnt[2])%MOD*(n-cnt[3])%MOD);
        add(x,1LL*cnt[0]*cnt[2]%MOD*(n-cnt[1])%MOD*(n-cnt[3])%MOD);
        add(x,1LL*cnt[0]*cnt[3]%MOD*(n-cnt[1])%MOD*(n-cnt[2])%MOD);
        add(x,1LL*cnt[1]*cnt[2]%MOD*(n-cnt[0])%MOD*(n-cnt[3])%MOD);
        add(x,1LL*cnt[1]*cnt[3]%MOD*(n-cnt[2])%MOD*(n-cnt[0])%MOD);
        add(x,1LL*cnt[2]*cnt[3]%MOD*(n-cnt[0])%MOD*(n-cnt[1])%MOD);
        add(ans,1LL*x*v[i].F%MOD);
        tmp[v[i].S]++;
    }
    printf("%d\n",ans);
    return 0;
}

