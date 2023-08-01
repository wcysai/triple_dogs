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
int t,n,k,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    t=5; n=200000;
    printf("%d\n",t);
    while(t--){
        printf("%d\n",n);
        for(int i=2;i<=n;i++){
            int fa=wcy()%(i-1)+1;
            int w=wcy()%n+1;
            printf("%d %d %d\n",fa,i,w);
        }
    }
    return 0;
}

