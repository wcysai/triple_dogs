#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100001
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,q;
int u[MAXN],v[MAXN],deg[MAXN],order[MAXN];
unordered_set<int> from[MAXN];
unordered_set<int> same[MAXN],dif[MAXN];
bool in[MAXN];
map<P,int> id;
unordered_set<int> nonempty;
string str;
bool cmp(int x,int y){
    return deg[x]<deg[y];
}
void flip(int v){
    in[v]=!in[v];
    swap(same[v],dif[v]);
    if(dif[v].size()) nonempty.insert(v);
    else if(nonempty.find(v)!=nonempty.end()) nonempty.erase(v);
    for(auto x:from[v]){
        if(in[x]==in[v]){
            dif[x].erase(v);
            same[x].insert(v);
            if(!dif[x].size()) nonempty.erase(x);
        }
        else{
            same[x].erase(v);
            dif[x].insert(v);
            if(dif[x].size()==1) nonempty.insert(x);
        }
    }
}
mt19937_64 gen(1);
void query(){
    if(!nonempty.size()){
        //printf("0\n"); 
        return;
    }
    int u=*(nonempty.begin());
    int v=*(dif[u].begin());
    //erase edge(u,v)
    int num=id[P(u,v)];
    //printf("%d\n",num);
    from[v].erase(u);
    dif[u].erase(v);
    if(!dif[u].size()) nonempty.erase(u);
}
int main()
{
    scanf("%d%d",&n,&m);
    for(int i=0;i<m;i++){
        u[i]=gen()%n+1;
        v[i]=gen()%n+1;
        if (u[i]==v[i]) u[i]=u[i]%n+1;
        //scanf("%d%d",&u[i],&v[i]);
        deg[u[i]]++; deg[v[i]]++;
    }
    vector<int> vv;
    for(int i=1;i<=n;i++) vv.push_back(i);
    sort(vv.begin(),vv.end(),cmp);
    for(int i=0;i<n;i++) order[vv[i]]=i;
    for(int i=0;i<m;i++){
        if(order[u[i]]>order[v[i]]) swap(u[i],v[i]);
        from[u[i]].insert(v[i]); id[P(v[i],u[i])]=i+1;
        same[v[i]].insert(u[i]);
    }
    scanf("%d",&q);
    for(int i=0;i<q;i++){
        //cin>>str; 
        int v;
        if(gen()%3){
            v=gen()%n+1;
            flip(v);
        }
        else{
            query();
        }
    }
    return 0;
}
