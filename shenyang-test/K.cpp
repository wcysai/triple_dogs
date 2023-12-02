#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXM 16000005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,k,a[MAXN];
ll neg;
int root,tot,poscnt;
int cnt[MAXM];
ll sum[MAXM];
int lson[MAXM],rson[MAXM];
void pushup(int k){
    sum[k]=sum[lson[k]]+sum[rson[k]];
    cnt[k]=cnt[lson[k]]+cnt[rson[k]];
}
void update(int &k,int l,int r,int p,int v){
    //printf("update k=%d l=%d r=%d p=%d v=%d cnt=%d sum=%lld\n",k,l,r,p,v,cnt[k],sum[k]);
    if(!k) k=++tot;
    if(l==r) {sum[k]+=1LL*v*l; cnt[k]+=v; return;}
    int mid=(l+r)/2;
    if(p<=mid) update(lson[k],l,mid,p,v);
    else update(rson[k],mid+1,r,p,v);
    pushup(k);
}
int query(int k,int l,int r,ll need){
    //printf("k=%d l=%d r=%d need=%d cnt=%d sum=%lld\n",k,l,r,need,cnt[k],sum[k]);
    if(sum[k]<need) return cnt[k];
    if(!need) return 0;
    if(l==r) return need/l;
    int mid=(l+r)/2;
    if(sum[lson[k]]>=need) return query(lson[k],l,mid,need); else return cnt[lson[k]]+query(rson[k],mid+1,r,need-sum[lson[k]]);
}
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]); 
        if(a[i]>0) { update(root,1,INF,a[i],1); }
        else neg-=a[i]; 
    }
    for(int i=1;i<=q;i++){
        int x,v;
        scanf("%d%d",&x,&v);
        if(a[x]>0) update(root,1,INF,a[x],-1);
        if(a[x]<0) neg+=a[x];
        a[x]=v;
        if(a[x]>0) update(root,1,INF,a[x],1);
        if(a[x]<0) neg-=a[x];
        int res=query(root,1,INF,neg);
        printf("%d\n",res+1); 
    }
    return 0;
}

