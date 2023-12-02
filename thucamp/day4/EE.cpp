#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1200005
#define MAXM 200005
#define INF 1000000005
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int tot,n,m,p[MAXN],r[MAXN],has[MAXN];
int ans[MAXN];
int q,a[MAXM],x[MAXM],y[MAXM];
int num;
vector<pair<int&,int> > backup;
void modify(int &ref,int v,bool save=true){
    if(save) backup.push_back({ref,ref});
    ref=v;
}
void rollback(int t){
    while((int)backup.size()>t){
        backup.back().F=backup.back().S;
        backup.pop_back();
    }
}
void init(int all){
    for(int i=1;i<=all;i++){
        p[i]=i; r[i]=0; has[i]=0; 
    }
    for(int i=1;i<=m;i++) has[i]=1;
    num=0;
}
int find(int x){
    while(p[x]!=x) x=p[x];
    return x;
}
bool unite(int x,int y,bool save=true){
    x=find(x); y=find(y);
    if(x==y) return false;
    int z=find(m+1);
    if(has[x]&&z==y) modify(num,num+1,save);
    if(has[y]&&z==x) modify(num,num+1,save);
    if(r[x]<r[y]){
        modify(p[x],y,save); modify(has[y],has[x]+has[y],save); 
    }
    else{
        modify(p[y],x,save); if(r[x]==r[y]) modify(r[x],r[x]+1,save);
        modify(has[x],has[x]+has[y],save);
    }
    return true;
}
vector<P> edges[4*MAXM];
void add_edge(int k,int l,int r,int x,int y,int u,int v)
{
    if(x>r||l>y) return;
    if(l>=x&&r<=y)
    {
        edges[k].push_back(P(u,v));
        return;
    }
    int mid=(l+r)/2;
    add_edge(k*2,l,mid,x,y,u,v);add_edge(k*2+1,mid+1,r,x,y,u,v);
}
void solve(int k,int l,int r)
{
    if(l>r) return;
    int t=(int)backup.size();
    int cnt=0;
    for(auto e:edges[k]) unite(e.F,e.S);
    if(l==r)
    {
        ans[l]=num;
        rollback(t);
        return;
    }
    int mid=(l+r)/2;
    solve(k*2,l,mid);solve(k*2+1,mid+1,r);
    rollback(t);
    //printf("cnt %d %d %d\n",l,r,cnt);
}
vector<int> row[MAXM],col[MAXM];
set<P> s;
unordered_map<int,int> id[MAXN];
unordered_map<int,P> state[MAXN];
//0:U 1:D 2:L 3:R
void try_add(int st,int ed,int z,int type){
    if(type==0){
        add_edge(1,0,q-1,st,ed,m+2+(z-1)*4+0,m+2+(z-1)*4+1);
        add_edge(1,0,q-1,st,ed,m+2+(z-1)*4+2,m+2+(z-1)*4+3);
    }
    else if(type==1){
        add_edge(1,0,q-1,st,ed,m+2+(z-1)*4+1,m+2+(z-1)*4+2);
        add_edge(1,0,q-1,st,ed,m+2+(z-1)*4+0,m+2+(z-1)*4+3);
    }
    else{
        add_edge(1,0,q-1,st,ed,m+2+(z-1)*4+0,m+2+(z-1)*4+2);
        add_edge(1,0,q-1,st,ed,m+2+(z-1)*4+1,m+2+(z-1)*4+3);
    }
}
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=0;i<q;i++) {
        scanf("%d%d%d",&a[i],&x[i],&y[i]);
        row[x[i]].push_back(y[i]);
        col[y[i]].push_back(x[i]);
        if(!id[x[i]][y[i]]) id[x[i]][y[i]]=++tot;
    }
    init(4*tot+m+1);
    for(int i=1;i<=m;i++){
        sort(col[i].begin(),col[i].end());
        col[i].erase(unique(col[i].begin(),col[i].end()),col[i].end());
        if(col[i].size())
        {
            unite(i,m+2+(id[col[i][0]][i]-1)*4,false);
            for(int j=0;j<(int)col[i].size()-1;j++) {
                int x=id[col[i][j]][i],y=id[col[i][j+1]][i];
                unite(m+2+(x-1)*4+1,m+2+(y-1)*4,false);
            }
            int x=id[col[i].back()][i];
            unite(m+2+(x-1)*4+1,m+1,false);
        }
        else{
            unite(i,m+1,false);
        }
    }
    for(int i=1;i<=n;i++){
        sort(row[i].begin(),row[i].end());
        row[i].erase(unique(row[i].begin(),row[i].end()),row[i].end());
        if(row[i].size()>1){
            for(int j=0;j<(int)row[i].size()-1;j++) {
                int x=id[i][row[i][j]],y=id[i][row[i][j+1]];
                unite(m+2+(x-1)*4+3,m+2+(y-1)*4+2,false);
            }
        }
    }
    for(int i=0;i<q;i++){
        P p=state[x[i]][y[i]];
        int z=id[x[i]][y[i]];
        int last=p.S;
        try_add(last,i-1,z,p.F);
        state[x[i]][y[i]]=P(a[i],i);
    }
    for(int i=1;i<=n;i++)
        for(auto p:state[i]){
            int x=i,y=p.F;
            int state=p.S.F,last=p.S.S;
            int z=id[x][y];
            try_add(last,q-1,z,state);
        }
    solve(1,0,q-1);
    for(int i=0;i<q;i++) printf("%d\n",ans[i]);
    return 0;
}

