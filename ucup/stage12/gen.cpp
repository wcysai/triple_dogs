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
int n,m,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    n=2000; m=7000;
    printf("%d %d\n",n,m);
    for(int i=0;i<m;i++){
        int x=(wcy()%n+1),y=wcy()%n+1;
        while(x==y) {x=wcy()%n+1; y=wcy()%n+1;}
        printf("%d %d\n",x,y);
    }
    return 0;
}

