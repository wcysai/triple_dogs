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
int n,q,a[MAXN];
mt19937 wcy(time(NULL));
int main()
{
    scanf("%d%d",&n,&q);
    printf("%d %d\n",n,q);
    for(int i=1;i<=n;i++) a[i]=wcy()%200001-100000;
    for(int i=1;i<=n;i++) printf("%d%c",a[i],i==n?'\n':' ');
    for(int i=0;i<q;i++){
        int pos=wcy()%n+1,x=wcy()%2;
        if(x) printf("+ %d\n",pos); else printf("- %d\n",pos);
    }
    return 0;
}

