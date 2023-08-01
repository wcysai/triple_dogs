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
int n,q,need;
int type[MAXN],p[MAXN],m[5];
int cnt[8];
set<P> removed[8],inside[8];
bool ins[MAXN];
ll ans;
int read_type(){
    string str; cin>>str;
    int mask=0;
    for(int i=0;i<(int)str.size();i++) 
        if(str[i]=='B') mask|=4; else if(str[i]=='S') mask|=2; else mask|=1;
    return mask;
}
int find_maxi()
{
    int res=INF;
    for(int mask=1;mask<(1<<4);mask++)
    {
        int mm=0,s=0,c=0;
        for(int j=0;j<4;j++) if(mask&(1<<j)) {mm|=m[j]; c++;}
        for(int j=1;j<=7;j++) if(mm&(1<<j)) s+=cnt[j];    
        res=min(res,s/c);
    }
    return res;
}
bool cmp(int x,int y)
{
    return p[x]>p[y];
}
int try_exchange(int x,int y)
{
    if(!removed[y].size()) return 0;
    if(!inside[x].size()) return 0;
    P p=*(--inside[x].end()),q=*removed[y].begin();
    if(p.F<=q.F) return 0;
    cnt[x]--; cnt[y]++;
    if(find_maxi()!=need) {cnt[x]++; cnt[y]--; return 0;}
    cnt[x]++; cnt[y]--;
    return p.F-q.F;
}
void exchange(int x,int y)
{
    P p=*(--inside[x].end()),q=*removed[y].begin();
    inside[x].erase(--inside[x].end()); removed[y].erase(removed[y].begin());
    removed[x].insert(p); inside[y].insert(q);
    ans-=(p.F-q.F);
    ins[p.S]=false; ins[q.S]=true;
    cnt[x]--; cnt[y]++;
}
int main()
{
    scanf("%d",&n);
    m[0]=(1<<1)|(1<<3)|(1<<5)|(1<<7);
    m[1]=(1<<2)|(1<<3)|(1<<6)|(1<<7);
    m[2]=(1<<4)|(1<<5)|(1<<6)|(1<<7);
    m[3]=(1<<1)|(1<<2)|(1<<3)|(1<<5)|(1<<6)|(1<<7);
    vector<int> v;
    for(int i=1;i<=n;i++)
    {
        type[i]=read_type(); scanf("%d",&p[i]); ans+=p[i];
        cnt[type[i]]++; v.push_back(i);
    }
    need=find_maxi();
    sort(v.begin(),v.end(),cmp);
    memset(ins,true,sizeof(ins));
    for(int i=0;i<n;i++)
    {
        int x=v[i];
        cnt[type[x]]--;
        if(find_maxi()==need) {removed[type[x]].insert(P(p[x],x)); ins[x]=false; ans-=p[x];}
        else {cnt[type[x]]++; inside[type[x]].insert(P(p[x],x));}
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++)
    {
        int x,y; scanf("%d%d",&x,&y);
        int last=p[x];
        p[x]=y; 
        if(ins[x])
        {
            ans+=y-last; 
            inside[type[x]].erase(P(last,x)); inside[type[x]].insert(P(p[x],x));
            P save=P(0,0);
            for(int j=1;j<=7;j++) 
            {
                int z=try_exchange(type[x],j);
                if(z>save.F) save=P(z,j);
            }
            if(save.F) exchange(type[x],save.S);
        }
        else
        {
            removed[type[x]].erase(P(last,x)); removed[type[x]].insert(P(p[x],x));
            P save=P(0,0);
            for(int j=1;j<=7;j++) 
            {
                int z=try_exchange(j,type[x]);
                if(z>save.F) save=P(z,j);
            }
            if(save.F) exchange(save.S,type[x]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}

