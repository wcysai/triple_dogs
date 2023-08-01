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
int T,n,k,a[5][MAXN];
mt19937 wcy(time(NULL));
int main()
{
    T=5;
    printf("%d\n",T);
    while(T--){
        n=50000;
        printf("%d\n",n);
        for(int i=1;i<=n;i++){
            for(int j=0;j<5;j++){
                int x=wcy()%n+1;
                printf("%d ",x);
            }
            int x=wcy()%10000+1;
            printf("%d\n",x);
        }
    }
    return 0;
}

