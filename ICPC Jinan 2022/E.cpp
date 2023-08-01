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
int T,n,k;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        if(k%2==0) {puts("Yes"); continue;}
        int rem=n%k;
        int lower=min(rem,k/2);
        if(lower-(rem-lower)>=n/k-1) puts("Yes"); else puts("No");
    }
    return 0;
}

