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
int n,m,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    n=5000;
    for(int i=1;i<=n;i++) a[i]=wcy()%n+1;
    sort(a+1,a+n+1);
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d%c",a[i],i==n?'\n':' ');
    return 0;
}

