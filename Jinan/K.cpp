#include<bits/stdc++.h>
#define MAXN 500005
using namespace std;
typedef long long ll;
int T,n,sz;
ll k;
vector<int> dis;
int a[MAXN];
struct segtree{
    int cnt[4*MAXN]; ll sum[4*MAXN];
    void pushup(int k){
        cnt[k]=cnt[k*2]+cnt[k*2+1];
        sum[k]=sum[k*2]+sum[k*2+1];
    }
    void build(int k,int l,int r){
        if(l==r) {
            cnt[k]=sum[k]=0;
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos,int v){
        if(l==r){
            cnt[k]+=v; sum[k]+=dis[l-1]*v;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,v); else update(k*2+1,mid+1,r,pos,v);
        pushup(k);
    }
    int find_rk(int k,int l,int r,int num){
        if(l==r){
            return l;
        }
        int mid=(l+r)/2;
        if(cnt[k*2]>=num) return find_rk(k*2,l,mid,num); else return find_rk(k*2+1,mid+1,r,num-cnt[k*2]);
    }
    ll get_sum(int k,int l,int r,int num){
        if(l==r){
            return 1LL*num*dis[l-1];
        }
        int mid=(l+r)/2;
        if(cnt[k*2]>=num) return get_sum(k*2,l,mid,num); else return sum[k*2]+get_sum(k*2+1,mid+1,r,num-cnt[k*2]);
    }
}seg;
void add(int v){
    seg.update(1,1,sz,v,1);
}
void dec(int v){
    seg.update(1,1,sz,v,-1);
}
ll query(){
    int num=seg.cnt[1]; ll sum=seg.sum[1];
    if(num<=1) return 0;
    int x=(num+1)/2;
    int mid=seg.find_rk(1,1,sz,x);
    ll slow=seg.get_sum(1,1,sz,x);
    //printf("x=%d mid=%d slow=%d\n",x,mid,slow);
    return (1LL*x*dis[mid-1]-slow)+((sum-slow)-1LL*(num-x)*dis[mid-1]);
}
int main(){
    scanf("%d",&T);
    while(T--){
        dis.clear();
        scanf("%d%lld",&n,&k);
        for(int i=1;i<=n;i++) {
            scanf("%d",&a[i]); a[i]-=i; dis.push_back(a[i]);
        }
        sort(dis.begin(),dis.end());
        dis.erase(unique(dis.begin(),dis.end()),dis.end());
        sz=(int)dis.size();
        for(int i=1;i<=n;i++) a[i]=lower_bound(dis.begin(),dis.end(),a[i])-dis.begin()+1;
        seg.build(1,1,sz);
        int ans=0,l=1;
        for(int i=1;i<=n;i++){
            add(a[i]);
            //printf("l=%d i=%d query=%lld\n",l,i,query());
            while(l<=i&&query()>k) {dec(a[l]); l++;}
            //printf("l=%d i=%d query=%lld\n",l,i,query());
            ans=max(ans,i-l+1);
        }
        printf("%d\n",ans);
    }
    return 0;
}
