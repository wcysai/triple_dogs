#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,a[MAXN];
vector<int> pos[MAXN];
vector<pair<P,int> > upd[MAXN]; 
struct segtree{
    int cnt[4*MAXN],len[4*MAXN],ans[4*MAXN];
    void pushup(int k){
        if(cnt[k]) ans[k]=len[k];
        else{
            ans[k]=ans[k*2]+ans[k*2+1];
        }
    }
    void build(int k,int l,int r){
        len[k]=r-l+1;
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int x,int y,int v){
        if(l>=x&&r<=y) {cnt[k]+=v; if(l==r) ans[k]=(cnt[k]?1:0); else pushup(k); return;}
        if(l>y||x>r) return;
        int mid=(l+r)/2;
        update(k*2,l,mid,x,y,v); update(k*2+1,mid+1,r,x,y,v);
        pushup(k);
    }
    int query(){
        return ans[1];
    }
}seg;
int main()
{
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) {scanf("%d",&a[i]); pos[a[i]].push_back(i);}
    for(int i=1;i<=1000000;i++){
        if(pos[i].size()>=k){
            for(int j=k-1;j<(int)pos[i].size();j++){
                int r1=pos[i][j],r2=(j==(int)pos[i].size()-1?n:pos[i][j+1]-1);
                int l1=(j==k-1?1:pos[i][j-k]+1),l2=pos[i][j-k+1];
                upd[l1].push_back(make_pair(P(r1,r2),1));
                upd[l2+1].push_back(make_pair(P(r1,r2),-1));
            }
        }
    }
    ll ans=0;
    seg.build(1,1,n);
    for(int i=1;i<=n;i++){
        for(auto p:upd[i]) seg.update(1,1,n,p.F.F,p.F.S,p.S);
        ans+=seg.query();
    }
    printf("%lld\n",1LL*n*(n+1)/2-ans);
    return 0;
}

