#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
int main()
{
    scanf("%d%d",&n,&m);
    int x=n&1,y=m&1;
    int ans=n/2+m/2+1;
    if(x==0&&y==0) ans--;
    printf("%d\n",ans);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++){
            if((i==1&&(j%2==y))||(j==1&&(i%2==x))) printf("1"); else printf("0");
            printf("%c",j==m?'\n':' ');
        }
    return 0;
}

