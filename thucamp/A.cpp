#include<bits/stdc++.h>
#define MAXN 200005
#define INF 2000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
vector<P> G[MAXN];
int n,m,q,curans,bas[MAXN][30];
int p[MAXN],val[MAXN];
struct edge{
    int u,v,cost;
};
vector<edge> E;
bool cmp(edge x,edge y){
    return x.cost<y.cost;
}
struct query{
    int s,t,w,id;
};
int ans[MAXN];
vector<query> save[MAXN];
void init(int n){
    for(int i=1;i<=n;i++){
        p[i]=i; val[i]=0;
    }
}
int find(int x){
    if(p[x]==x) return x;
    else{
        int fa=find(p[x]);
        val[x]^=val[p[x]];
        p[x]=fa;
        return fa;
    }
}
int get_val(int x){
    int tmp=find(x);
    return val[x];
}
bool ins(int id,int x){
    //printf("add base %d %d\n",id,x);
    for(int i=29;i>=0;i--){
        if(x&(1<<i)){
            if(!bas[id][i]){
                bas[id][i]=x;
                return true;
            }
            x^=bas[id][i];
        }
    }
    return false;
}
bool check(int id,int x){
    for(int i=29;i>=0;i--){
        if(x&(1<<i)){
            if(!bas[id][i]) return false;
            x^=bas[id][i];
        }
    }
    return true;
}
void go_over(int id){
    vector<query> tmp;
    for(auto z:save[id]){
        int x=find(z.s),y=find(z.t);
        if(x!=y) {tmp.push_back(z); continue;}
        int val=(get_val(z.s)^get_val(z.t)^z.w);
        if(check(id,val)){
            ans[z.id]=min(ans[z.id],curans);
        }
        tmp.push_back(z);
    }
    swap(tmp,save[id]);
}

void merge(int x,int y,int z){
    int u=find(x),v=find(y);
    if(save[u].size()>save[v].size()) {swap(x,y); swap(u,v);}
   // printf("x=%d y=%d u=%d v=%d\n",x,y,u,v);
    bool fu=false,fv=false;
    vector<int> vu,vv;
    for(int i=29;i>=0;i--)
        if(bas[u][i])
            vu.push_back(bas[u][i]);
    for(int i=29;i>=0;i--)
        if(bas[v][i])
            vv.push_back(bas[v][i]);
    for(auto x:vu)
        if(ins(v,x)) fv=true; 
    for(auto x:vv)
        if(ins(u,x)) fu=true; 
    vector<query> need;
    for(auto i:save[u]) {
        int a=find(i.s),b=find(i.t);
    //    printf("u=%d v=%d a=%d b=%d\n",u,v,a,b);
        if(a!=u) swap(a,b);
        assert(a==u);
        if(a==u&&b==v) need.push_back(i);
    }
    assert(val[u]==0);
    p[u]=v; val[u]^=(val[x]^val[y]^z);
    if(fu) go_over(u);
    if(fv) go_over(v);
    for(auto i:save[u]) save[v].push_back(i);
    save[u].clear(); save[u].shrink_to_fit();
    for(auto i:need){
        int val=(get_val(i.s)^get_val(i.t)^i.w);
     //   printf("need s=%d t=%d w=%d vals=%d valt=%d val=%d id=%d\n",i.s,i.t,i.w,get_val(i.s),get_val(i.t),val,i.id);
        if(check(v,val)){
            //assert(ans[i.id]==INF);
            ans[i.id]=min(ans[i.id],curans);
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    assert(n<=200000);
    for(int i=0;i<m;i++){
        int u,v,w;
        scanf("%d%d%d",&u,&v,&w);
        E.push_back((edge){u,v,w});
    }
    init(n);
    sort(E.begin(),E.end(),cmp);
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        int f,t,h;
        scanf("%d%d%d",&f,&t,&h);
        assert(h<(1<<30));
        save[f].push_back((query){f,t,h,i});
        save[t].push_back((query){f,t,h,i});
    }
    for(int i=0;i<q;i++) ans[i]=INF;
    for(int i=0;i<m;i++){
        int u=E[i].u,v=E[i].v,w=E[i].cost;
        //printf("u=%d v=%d w=%d x=%d y=%d\n",u,v,w,find(u),find(v));
        curans=w;
        if(find(u)==find(v)){
            //puts("here");
            int z=(get_val(u)^get_val(v)^w);
            //printf("z=%d\n",z);
            if(ins(find(u),z)) go_over(find(u));
        }
        else{
            merge(u,v,w);
        }
        //for(int j=1;j<=n;j++) printf("%d ",p[j]); printf("\n");
        //for(int j=1;j<=n;j++) printf("%d ",val[j]); printf("\n");
    }
    for(int i=0;i<q;i++) printf("%d\n",ans[i]==INF?-1:ans[i]);
    return 0;
}
/*
7 9
1 1 128
1 2 1 
1 3 8
2 3 73
2 4 2
2 5 4
3 6 16
3 7 32
3 4 75
5
2 3 73
2 3 9
2 7 104
4 7 100
4 7 107
*/
