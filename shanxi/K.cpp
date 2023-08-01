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
int n,c[MAXN],d[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d%d",&c[i],&d[i]);
    ll cost=0;  int mini=c[1];
    for(int i=1;i<=n-1;i++){
        cost+=1LL*mini*(d[i+1]-d[i]);
        mini=min(mini,c[i+1]);
    }
    printf("%lld\n",cost);
    return 0;
}

