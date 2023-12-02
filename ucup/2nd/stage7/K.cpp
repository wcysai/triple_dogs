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
int l,r;
int main()
{
    scanf("%d%d",&l,&r);
    if(l==r) printf("%d\n",l);
    else if(l==r-1) printf("-1\n");
    else printf("%d\n",r-1);
    return 0;
}

