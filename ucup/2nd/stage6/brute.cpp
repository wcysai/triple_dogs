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
ll calc(){
    ll max_sum=0,min_sum=0;
    for(int i=1;i<=n;i++) {
        int maxi=-INF,mini=INF;
        for(int j=i;j<=n;j++){
            maxi=max(maxi,a[j]);
            mini=min(mini,a[j]);
            max_sum+=maxi; min_sum+=mini;
        }
    }
    printf("%lld %lld\n",max_sum,min_sum);
    return max_sum-min_sum;
}
string str;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=0;i<q;i++){
        cin>>str;
        int x;
        scanf("%d",&x);
        if(str[0]=='+') a[x]++; else a[x]--;
        printf("%lld\n",calc());
    }
    return 0;
}

