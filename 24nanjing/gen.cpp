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
int n,q,k,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    printf("%d\n",1);
    n=q=100000;
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d%c",wcy()%1000000+1,i==n?'\n':' ');
    printf("%d\n",q);
    for(int i=1;i<=n;i++){
        int pos=wcy()%n+1;
        int v=wcy()%1000000+1;
        printf("%d %d\n",pos,v);
    }
    return 0;
}

