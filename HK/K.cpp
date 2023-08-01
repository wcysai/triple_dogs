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
int l,r,b,k;
int main(){
    scanf("%d%d%d%d",&l,&r,&b,&k);
    int need=(l+b-1)/b;
    printf("%lld\n",1LL*need*b*k);
    return 0;
}

