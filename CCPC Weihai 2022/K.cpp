#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000001
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n;
vector<P> v;
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d",&n);
        v.clear();
        int lb=INF,rb=1;//l<=lb r>=rb
        multiset<int> s;
        for(int i=0;i<n;i++)
        {
            int t,k,x;
            scanf("%d%d%d",&t,&k,&x);
            int l=2*x/k;
            l-=(k-1);
            l/=2;
            int r=(2*x-1)/k+1;
            r+=(k-1);
            r=(r+1)/2;
            //printf("i=%d l=%d r=%d\n",i,l,r);
            if(t==1)
            {
                lb=min(lb,l);
                rb=max(rb,r);
            }
            else
            {
                if(l<=0) continue;
                v.push_back(P(l+1,r-1));
                s.insert(r-1);
            }
        }
        sort(v.begin(),v.end());
        if(lb<=0) {puts("0"); continue;}
        int now=1; 
        ll ans=0;
        for(auto p:v)
        {
            if(p.F>now)
            {
                if(s.size()==0) {ans=-1; break;}
                int res=max(0,(*(s.begin())-rb+1));
                //printf("res=%d\n",res);
                ans+=1LL*(min(lb+1,p.F)-now)*res;
                now=p.F;
                if(now>lb) break;
            }
            if(p.F==now) s.erase(s.find(p.S));
        }
        if(now<=lb) ans=-1;
        printf("%lld\n",ans);
    }
    return 0;
}