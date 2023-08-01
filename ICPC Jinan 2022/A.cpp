#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,m,a[MAXN];
int compute(int x,int y)
{
    int ans=max(x-y,y-x);
    int cnt=0;
    while(x>1)
    {
        x=x/2;
        cnt++;
        ans=min(ans,cnt+max(x-y,y-x));
    }
    return ans;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        vector<int> dis;
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        for(int i=1;i<=n;i++)
        {
            int x=a[i];
            while(x)
            {
                dis.push_back(x);
                x/=2;
            }
        }
        sort(dis.begin(),dis.end());
        dis.erase(unique(dis.begin(),dis.end()),dis.end());
        ll ans=INF;
        for(auto x:dis)
        {
            ll s=0;
            vector<int> tmp;
            for(int i=1;i<=n;i++) tmp.push_back(compute(a[i],x));
            sort(tmp.begin(),tmp.end());
            for(int i=0;i<n-m;i++) s+=tmp[i];
            ans=min(ans,s);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

