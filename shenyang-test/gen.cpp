#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,k,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    n=q=200000;
    printf("%d %d\n",n,q);
    for(int i=1;i<=n;i++) a[i]=wcy()%INF+1;
    for(int i=1;i<=n;i++) printf("%d%c",a[i],i==n?'\n':' ');
    for(int i=1;i<=q;i++){
        int pos=wcy()%n+1,val=wcy()%INF+1;
        printf("%d %d\n",pos,val);
    }
    return 0;
}

