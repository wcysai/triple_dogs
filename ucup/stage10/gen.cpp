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
int T,n,k,a[2*MAXN];
mt19937 wcy(time(NULL));

int main()
{
    T=10; n=200000;
    printf("%d\n",n);
    printf("%d %d\n",1,3);
    for(int i=2;i<=n-1;i++) printf("%d %d\n",2*i-2,2*i+1); 
    printf("%d %d\n",2*n-2,2*n);
    return 0;
}

