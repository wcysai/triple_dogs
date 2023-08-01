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
int n=200000;
mt19937 wcy(time(NULL));
int main()
{
    printf("%d\n",n);
    for(int i=1;i<=n;i++) printf("%d ",wcy()%INF);
    for(int i=0;i<n-1;i++) printf("-");
    printf("\n");
    return 0;
}

