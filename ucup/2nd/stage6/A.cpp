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
int sg[MAXN];
bool has[305];
int get_sum(int x){
    int sum=0;
    while(x){
        sum+=x%10; x/=10;
    }
    return sum;
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        memset(has,false,sizeof(has));
        int s=get_sum(i);
        for(int j=1;j<=s;j++){
            has[sg[i-j]]=true;
        }
        int now=0;
        while(has[now]) now++;
        sg[i]=now;
        if(!sg[i]) printf("%d\n",i);
    }
    return 0;
}

