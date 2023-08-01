#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 3000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k;
char str[10];
int mask[MAXN];
bool hl[MAXM];
int read_day()
{
    scanf("%s",str);
    if(str[0]=='M') return 0;
    else if(str[0]=='T'&&str[1]=='u') return 1;
    else if(str[0]=='W') return 2;
    else if(str[0]=='T') return 3;
    else if(str[0]=='F') return 4;
    else if(str[0]=='S'&&str[1]=='a') return 5;
    else return 6;
}
vector<int> pro[MAXN];
int id[MAXN];
int ans[MAXN];
vector<int> save;
bool used[MAXN];
/*struct segtree
{
    int ma[4*MAXN];
    void pushup(int k)
    {
        ma[k]=(ma[k*2]|ma[k*2+1]);
    }
    void build(int k,int l,int r)
    {
        if(l==r) {ma[k]=mask[pro[l][0]]; return;}
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos,int v)
    {
        if(l==r)
        {
            ma[k]=v;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,v); else update(k*2+1,mid+1,r,pos,v);
        pushup(k);
    }
    int query(int k,int l,int r,int pos,int d)
    {
        if(!(ma[k]&(1<<d))) return -1;
        if(r<pos) return -1;
        if(l==r) return l;
        int mid=(l+r)/2;
        int x=query(k*2,l,mid,pos,d);
        if(x!=-1) return x; else return query(k*2+1,mid+1,r,pos,d);
    }
}seg;*/
set<P> wpro[7];
int main()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;i++)
    {
        int t;
        scanf("%d",&t);
        for(int j=0;j<t;j++) mask[i]|=(1<<read_day());
    }
    for(int i=0;i<m;i++)
    {
        int h;
        scanf("%d",&h);
        if(h<MAXM) hl[h]=true;
    }
    for(int i=1;i<=k;i++)
    {
        int p;
        scanf("%d",&p);
        for(int j=0;j<p;j++)
        {
            int x;
            scanf("%d",&x);
            pro[i].push_back(x);
        }
    }
    for(int i=1;i<=k;i++)
    {
        int worker=pro[i][0];
        for(int j=0;j<7;j++)
            if(mask[worker]&(1<<j))
                wpro[j].insert(P(worker,i));
    }
    //seg.build(1,1,k);
    memset(used,false,sizeof(used));
    int cnt=0;
    for(int i=1;;i++)
    {
        if(hl[i]) continue;
        int x=(i-1)%7,last=1;
        save.clear();
        P p=P(0,0);
        while(true)
        {
            auto it=wpro[x].lower_bound(p);
            if(it==wpro[x].end()) break;
            int worker=it->F,y=it->S;
            for(int j=0;j<7;j++) if(mask[worker]&(1<<j)) wpro[j].erase(P(worker,y));
            save.push_back(y);
            id[y]++;
            if(id[y]==(int)pro[y].size()) 
            {
                ans[y]=i; cnt++;
            }
            p.F=worker+1;
        }
        for(auto proj:save)
        {
            if(id[proj]!=(int)pro[proj].size())
            {
                int worker=pro[proj][id[proj]];
                for(int j=0;j<7;j++) if(mask[worker]&(1<<j)) wpro[j].insert(P(worker,proj));
            }
        }
        if(cnt==k) break;
    }
    for(int i=1;i<=k;i++) printf("%d%c",ans[i],i==k?'\n':' ');
    return 0;
}

