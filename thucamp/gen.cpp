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
int n,m,q,k,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    n=100000; m=200000;
    printf("%d %d\n",n,m);
    for(int i=0;i<m;i++){
        int u,v,w;
        u=wcy()%n+1; v=wcy()%n+1; w=wcy()%(1<<30);
        printf("%d %d %d\n",u,v,w);
    }
    q=200000;
    printf("%d\n",q);
    for(int i=0;i<q;i++){
        int u,v,w;
        u=wcy()%n+1; v=wcy()%n+1;
        while(u==v) {u=wcy()%n+1; v=wcy()%n+1;}
        w=wcy()%(1<<30);
        printf("%d %d %d\n",u,v,w);
    }
    return 0;
}

