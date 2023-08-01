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
int main()
{
    scanf("%d",&m);
    while(m--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        int inv=0;
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                if(a[i]>a[j]) inv++;
        printf("%d\n",inv);
    }
    return 0;
}

