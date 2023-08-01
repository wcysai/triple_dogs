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
typedef long double db;
int n,k,a[MAXN];
int main()
{
    scanf("%d",&n);
    db s=0.0;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&a[i]);
        s+=a[i];
    }
    s/=(n+1);
    for(int i=1;i<=n;i++) printf("%.10Lf%c",i==1?2.0*s:s,i==n?'\n':' ');
    return 0;
}

