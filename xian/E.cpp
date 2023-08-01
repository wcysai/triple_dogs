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
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    set<int> s;
    for(int i=0;i<n;i++){
        int d=(a[(i+1)%n]-a[i]+n)%n;
        s.insert(d);
    }
    if(s.size()!=1) puts("-1");
    else{
        int d=*s.begin();
        int ans=d;
        if(d==0&&a[0]!=0) ans=n+1;
        else{
            if(a[0]!=0) ans++;
        }
        printf("%d\n",ans);
    }
    return 0;
}

