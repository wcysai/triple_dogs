#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef pair<int,int> P;
int T,n,k,a[MAXN];
P p[MAXN];
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&n,&k);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);
        sort(a+1,a+n+1);
        set<int> zeroes;
        map<int,int> mp;
        for(int i=1;i<=k;i++) 
        {
            int x,y;
            scanf("%d%d",&x,&y);
            if(!y) zeroes.insert(x); else mp[x]=y;
        }
        zeroes.insert(INF+1);
        int ans=0;
        for(int i=1;i<=n;i++)
        {
            auto it=zeroes.lower_bound(a[i]);
            int to;
            if(it==zeroes.begin())
            {
                to=0;
            }
            else {it--; to=(*it)+1;}
            if(mp.find(to)!=mp.end())
            {
                mp[to]--;
                if(!mp[to]) zeroes.insert(to);
            }
            ans^=((a[i]-to)&1);
        }
        if(ans) puts("Pico"); else puts("FuuFuu");
    }
    return 0;
}