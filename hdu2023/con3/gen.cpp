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
mt19937 wcy(time(NULL));
int main()
{
    int T=10000;
    printf("%d\n",T);
    while(T--){
        for(int i=1;i<=49;i++) printf("%c",'1'+(wcy()&1));
        printf("\n");
    }
    return 0;
}

