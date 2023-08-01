#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
mt19937 wcy(time(NULL));
int n;
vector<P> G[MAXN];
int pos[MAXN][2];
int ans[MAXN];
P save[MAXN];
bool vis[MAXN];
P ask(int x,int y)
{
    printf("? %d %d\n",x,y);
    fflush(stdout);
    int p1,p2;
    scanf("%d%d",&p1,&p2);
    return P(p1,p2);
}
deque<int> cyc;
void dfs(int v)
{
    vis[v]=true;
    cyc.push_back(v);
    for(auto p:G[v])
        if(!vis[p.S]) 
        {
            cyc.push_back(p.F);
            dfs(p.S);
        }
}
void answer()
{
    printf("!");
    for(int i=1;i<=n;i++) printf(" %d",ans[i]);
    printf("\n");
    fflush(stdout);
    exit(0);
}
vector<pair<P,P> > trash;
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n/2;i++)
    {
        P p=ask(2*i-1,2*i);
        pos[i][0]=2*i-1; pos[i][1]=2*i; save[i]=p;
        G[p.F].push_back(P(i,p.S));
        G[p.S].push_back(P(i,p.F));
    }
    for(int i=1;i<=n/2;i++) vis[i]=false;
    for(int i=1;i<=n/2;i++)
    {
        if(!vis[i])
        {
            cyc.clear();
            dfs(i);
            if(cyc.size()==1) continue;
            else 
            {
                int last=cyc.back();
                for(auto p:G[last]) if(p.S==cyc[0]) {cyc.push_back(p.F); break;}
                assert(cyc.size()%2==0);
                bool cycl=true;
                while(cyc.size()>4)
                {
                    int sz=(int)cyc.size();
                    int x=cyc[0],y=cyc[2],z=cyc[4];
                    int id1=cyc[1],id2=cyc[3];
                    int r1=wcy()&1,r2=wcy()&1;
                    int pos1=pos[id1][r1],pos2=pos[id2][r2];
                    int ppos1=pos[id1][r1^1],ppos2=pos[id2][r2^1];
                    P p=ask(pos[id1][r1],pos[id2][r2]);
                    if(p.F==p.S)
                    {
                        ans[pos1]=ans[pos2]=p.S;
                        for(int j=0;j<3;j++) cyc.pop_front();
                        pos[id2][0]=ppos1; pos[id2][1]=ppos2;
                        cyc.push_front(x);
                    }
                    else if((p.F==x&&p.S==z)||(p.F==z&&p.S==x))
                    {
                        ans[ppos1]=ans[ppos2]=p.S;
                        for(int j=0;j<3;j++) cyc.pop_front();
                        pos[id2][0]=pos1; pos[id2][1]=pos2;
                        cyc.push_front(x);
                    }
                    else if(p.F==x||p.S==x)
                    {
                        if(p.F==x) {ans[ppos1]=y; ans[ppos2]=z;}
                        else {ans[ppos1]=z; ans[ppos2]=y;}
                        pos[id1][0]=p.F; pos[id1][1]=p.S;
                        for(int j=0;j<4;j++) cyc.pop_front();
                        cyc.push_back(x); cyc.push_back(id1); cyc.push_back(y);
                        cycl=false; break;
                    }
                    else 
                    {
                        if(p.F==z) {ans[ppos1]=y; ans[ppos2]=x;}
                        else {ans[ppos1]=x; ans[ppos2]=y;}
                        pos[id2][0]=p.F; pos[id2][1]=p.S;
                        for(int j=0;j<2;j++) cyc.pop_front();
                        cyc.push_back(x); 
                        cycl=false; break;
                    }
                }
                if(!cycl&&cyc.size()==4)
                {
                    int id1=cyc[1],id2=cyc[3];
                    while(true)
                    {
                        int r1=wcy()&1,r2=wcy()&1;
                        P p=ask(pos[id1][r1],pos[id2][r2]);
                        if(p.F==p.S) 
                        {
                            ans[pos[id1][r1]]=ans[pos[id2][r2]]=p.S;
                            int x=(cyc[0]==p.F?cyc[2]:cyc[0]);
                            ans[pos[id1][r1^1]]=ans[pos[id2][r2^1]]=x;
                            break;
                        }
                    }
                    break;
                }
                //chain
                while(cyc.size()>=5)
                {
                    int sz=(int)cyc.size();
                    int x=cyc[0],y=cyc[2],z=cyc[4];
                    int id1=cyc[1],id2=cyc[3];
                    int r1=wcy()&1,r2=wcy()&1;
                    int pos1=pos[id1][r1],pos2=pos[id2][r2];
                    int ppos1=pos[id1][r1^1],ppos2=pos[id2][r2^1];
                    P p=ask(pos[id1][r1],pos[id2][r2]);
                    if(p.F==p.S)
                    {
                        ans[pos1]=ans[pos2]=p.S;
                        for(int j=0;j<3;j++) cyc.pop_front();
                        pos[id2][0]=ppos1; pos[id2][1]=ppos2;
                        cyc.push_front(x);
                    }
                    else if((p.F==x&&p.S==z)||(p.F==z&&p.S==x))
                    {
                        ans[ppos1]=ans[ppos2]=p.S;
                        for(int j=0;j<3;j++) cyc.pop_front();
                        pos[id2][0]=pos1; pos[id2][1]=pos2;
                        cyc.push_front(x);
                    }
                    else if(p.F==x||p.S==x)
                    {
                        if(p.F==x) {ans[ppos1]=y; ans[ppos2]=z;}
                        else {ans[ppos1]=z; ans[ppos2]=y;}
                        pos[id1][0]=p.F; pos[id1][1]=p.S;
                        for(int j=0;j<4;j++) cyc.pop_front();
                        trash.push_back(make_pair(P(x,y),p));
                    }
                    else 
                    {
                        if(p.F==z) {ans[ppos1]=y; ans[ppos2]=x;}
                        else {ans[ppos1]=x; ans[ppos2]=y;}
                        pos[id2][0]=p.F; pos[id2][1]=p.S;
                        for(int j=0;j<2;j++) cyc.pop_front();
                        cyc.push_back(x); 
                        cycl=false; break;
                    }
                }
                if(cyc.size()==3) 
                {
                    int x=cyc[0],y=cyc[2];
                    int pos1=pos[cyc[1]][0],pos2=pos[cyc[1]][1];
                    trash.push_back(make_pair(P(x,y),P(pos1,pos2)));
                }
            }
        }
    }
    while(trash.size()>1)
    {
        auto p=trash.back(); trash.pop_back(); 
        auto q=trash.back(); trash.pop_back();
        int pos1,pos2,ppos1,ppos2;
        pos1=p.S.F; pos2=p.S.S; ppos1=q.S.F; ppos2=q.S.S; 
        if(wcy()&1) swap(pos1,pos2); 
        if(wcy()&1) swap(ppos1,ppos2);
        P res=ask(pos1,ppos1);
        int x=p.F.F,y=p.F.S,z=q.F.F,w=q.F.S;
        if(x==res.F) ans[pos2]=y; else ans[pos2]=x;
        if(w==res.S) ans[ppos2]=z; else ans[ppos2]=w;
        trash.push_back(make_pair(res,P(pos1,ppos1)));
    }
    if(trash.size())
    {
        auto p=trash.back();
        int x=p.F.F,y=p.F.S;
        int pos1=p.S.F,pos2=p.S.F;
        int ppos1,ppos2;
        for(int i=1;i<=n;i++)
        {
            if(ans[i]==x) ppos1=i;
            if(ans[i]==y) ppos2=i;
        }
        while(true)
        {
            if(wcy()&1) swap(pos1,pos2); 
            if(wcy()&1) swap(ppos1,ppos2);
            P res=ask(pos1,ppos1);
            if(res.F==res.S)
            {
                ans[pos1]=ans[ppos1]=res.F;
                ans[pos2]=ans[ppos2]=(x==res.F?y:x);
            }
            else 
            {
                swap(pos2,ppos1);
                continue;
            }
        }
    }
    answer();
    return 0;
}