#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define MAXLOGN 19
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int q,n,k,added;
P p[MAXN];
int a[MAXN],b[MAXN];
vector<int> save[MAXN];
int cnt[MAXN];
ll pre[MAXN];
ll sum[MAXN];
ll t;
void update(int i,int val){
    while(i<=n){
        cnt[i]++;
        sum[i]+=val;
        i+=i&-i;
    }
    added++;
}
int get_cnt(int i){
    int s=0;
    while(i>0){
        s+=cnt[i];
        i-=i&-i;
    }
    return s;
}
ll get_sum(int i){
    ll s=0;
    while(i>0){
        s+=sum[i];
        i-=i&-i;
    }
    return s;
}
ll bisearch(int num){
    int c=0,pos=0;
    ll s=0;
    for(int i=MAXLOGN;i>=0;i--){
        if(pos+(1<<i)<=n&&c+cnt[pos+(1<<i)]<=num){
            c+=cnt[pos+(1<<i)];
            s+=sum[pos+(1<<i)];
            pos+=(1<<i);
        }
    }
    return s;
}
int check(int num,int k){
    int val=get_cnt(num);
    if(added-val<k-num) return -1;
    ll s=bisearch(val+k-num);
    //printf("num=%d val=%d s=%lld res=%lld\n",num,val,s,pre[num]+s-get_sum(val));
    return (pre[num]+s-get_sum(num)<=t?val+k-num:-1);
}
int main()
{
    scanf("%d",&q);
    while(q--){
        scanf("%d%lld",&n,&t);
        for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
        for(int i=1;i<=n;i++) {p[i].F=a[i]; p[i].S=i;}
        sort(p+1,p+n+1);
        for(int i=1;i<=n;i++) save[i].clear();
        for(int i=1;i<=n;i++) save[b[p[i].S]].push_back(i);
        for(int i=1;i<=n;i++) cnt[i]=sum[i]=0;
        for(int i=1;i<=n;i++) pre[i]=pre[i-1]+p[i].F;
        int ans=0;
        int bestk=0;
        added=0;
        for(int k=1;k<=n;k++){
            //printf("k=%d\n",k);
            for(auto x:save[k]) update(x,p[x].F); 
            int l=-1,r=k;
            while(r-l>1){
                int mid=(l+r)/2;
                //printf("mid=%d check=%d\n",mid,check(mid,k));
                if(check(mid,k)!=-1) r=mid; else l=mid;
            }
            int res=check(r,k);
            if(res>ans){
                ans=res;
                bestk=k;
            }
        }
        printf("%d\n%d\n",ans,bestk);
        if(ans){
            vector<P> v1,v2;
            for(int i=1;i<=bestk;i++)
                for(auto x:save[i]) v1.push_back(p[x]);
            for(int i=bestk+1;i<=n;i++)
                for(auto x:save[i]) v2.push_back(p[x]);
            sort(v1.begin(),v1.end()); sort(v2.begin(),v2.end());
            for(int i=0;i<ans;i++) printf("%d ",v1[i].S);
            for(int i=0;i<bestk-ans;i++) printf("%d ",v2[i].S);
            printf("\n");
        }
    }
    return 0;
}

