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
int n,k,a[MAXN];
int main()
{
    scanf("%d",&n);
    if(n&1){
        int num=(n-1)/2;
        printf("%d %d\n",1+2*(num/3),n);
    }
    else{
        int num=(n-2)/2;
        printf("%d %d\n",2+2*(num/3),n);
    }
    return 0;
}

