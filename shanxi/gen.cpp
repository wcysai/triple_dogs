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
int n,m,k,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    n=100000; m=500000;
    printf("%d %d %d\n",100000,500000,12);
    for(int i=2;i<=100000;i++) printf("%d %d\n",i/2,i);
    for(int i=0;i<m;i++){
        int u=wcy()%n+1,v=wcy()%n+1;
        while(u==v) v=wcy()%n+1;
        int w=wcy()%(INF+1);
        printf("%d %d %d\n",u,v,w);
    }
    return 0;
}

