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
int n,m,a[MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=2;i<=n;i++) a[i]=max(a[i],a[i-1]-m);
    for(int i=n-1;i>=1;i--) a[i]=max(a[i],a[i+1]-m);
    for(int i=1;i<=n;i++) printf("%d%c",a[i],i==n?'\n':' ');
    return 0;
}

