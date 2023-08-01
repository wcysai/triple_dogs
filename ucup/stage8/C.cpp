#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 4005
#define MAXM 8000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,tot,tot2,tot3;
int x[MAXN],y[MAXN],cnt[MAXN],tt[MAXN];
ll d[MAXN][MAXN];
int u[MAXM],v[MAXM];
ll f[MAXM],g[MAXM];
bool act[MAXN];
struct node{
    int id;
};
bool operator<(const node &a,const node &b){
    int x=a.id,y=b.id;
    if(f[x]*g[y]!=f[y]*g[x]) return f[x]*g[y]>f[y]*g[x];
    if(min(tt[u[x]],tt[v[x]])!=min(tt[u[y]],tt[v[y]])) return min(tt[u[x]],tt[v[x]])>min(tt[u[y]],tt[v[y]]);
    return max(tt[u[x]],tt[v[x]])>max(tt[u[y]],tt[v[y]]);
}
priority_queue<node> pque;
void add_entry(int a,int b,ll num,ll den){
    tot2++;
    u[tot2]=a; v[tot2]=b; f[tot2]=num; g[tot2]=den;
    pque.push((node){tot2});
}
void merge(int a,int b){
    act[a]=false; act[b]=false;
    tot++; act[tot]=true; cnt[tot]=cnt[a]+cnt[b];
    tot3++; tt[tot]=tot3;
    ll sum=0;
    for(int i=1;i<=tot-1;i++){
        if(i==a||i==b) continue;
        if(!act[i]) continue;
        ll s=d[i][a]+d[i][b];
        d[i][tot]=d[tot][i]=s;
        add_entry(i,tot,s,cnt[i]*cnt[tot]);
    }
}
int main(){
    scanf("%d",&n);
    tot=n; tot2=0; tot3=n;
    for(int i=1;i<=n;i++) {
        scanf("%d%d",&x[i],&y[i]);
        cnt[i]=1; tt[i]=i; act[i]=true;
    }
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            d[i][j]=d[j][i]=1LL*(x[i]-x[j])*(x[i]-x[j])+1LL*(y[i]-y[j])*(y[i]-y[j]);
            add_entry(i,j,d[i][j],1);
        }
    for(int i=1;i<=n-1;i++){
        node val=pque.top(); pque.pop();
        while(((int)pque.size()>0)&&((!act[u[val.id]])||(!act[v[val.id]]))){
            val=pque.top(); pque.pop();
        }
        merge(u[val.id],v[val.id]);
        printf("%d\n",cnt[tot]);
    }
    return 0;
}

