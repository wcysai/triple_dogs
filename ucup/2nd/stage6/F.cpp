#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN],st[MAXN];
ll max_sum,min_sum;
struct segtree{
    int maxi[4*MAXN],mini[4*MAXN];
    void pushup(int k){
        maxi[k]=max(maxi[k*2],maxi[k*2+1]);
        mini[k]=min(mini[k*2],mini[k*2+1]);
    }
    void build(int k,int l,int r){
        if(l==r){
            maxi[k]=mini[k]=a[l];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos,int v){
        if(l==r){
            maxi[k]+=v; mini[k]+=v;
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,v); else update(k*2+1,mid+1,r,pos,v);
        pushup(k);
    }
    int find_pos(int k,int l,int r,int pos,int is_prev,int is_larger){
        //printf("l=%d r=%d pos=%d is_prev=%d is_larger=%d mini=%d maxi=%d\n",l,r,pos,is_prev,is_larger,mini[k],maxi[k]);
        if(is_larger&&maxi[k]<=a[pos]) return -1; 
        if(!is_larger&&mini[k]>=a[pos]) return -1; 
        if(is_prev){
            if(l>=pos) return -1;
        }
        else{
            if(r<=pos) return -1;
        }
        if(l==r) return l;
        int mid=(l+r)/2;
        if(is_prev){
            int x=find_pos(k*2+1,mid+1,r,pos,is_prev,is_larger);
            if(x!=-1) return x;
            else return find_pos(k*2,l,mid,pos,is_prev,is_larger);
        }
        else{
            int x=find_pos(k*2,l,mid,pos,is_prev,is_larger);
            if(x!=-1) return x;
            else return find_pos(k*2+1,mid+1,r,pos,is_prev,is_larger);
        }
    }
}seg;
int L1[MAXN],L2[MAXN],R1[MAXN],R2[MAXN];
string str;
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    seg.build(1,1,n);
    int t=0;
	for(int i=1;i<=n;i++)
	{
		while(t>0&&a[st[t-1]]>=a[i]) t--;
		L1[i]=t==0?0:st[t-1];
		st[t++]=i;
	}
    t=0;
	for(int i=1;i<=n;i++)
	{
		while(t>0&&a[st[t-1]]<=a[i]) t--;
		L2[i]=t==0?0:st[t-1];
		st[t++]=i;
	}
	t=0;
	for(int i=n;i>=1;i--){
		while(t>0&&a[st[t-1]]>a[i]) t--;
		R1[i]=t==0?n+1:st[t-1];
		st[t++]=i;
	}
	t=0;
	for(int i=n;i>=1;i--){
		while(t>0&&a[st[t-1]]<a[i]) t--;
		R2[i]=t==0?n+1:st[t-1];
		st[t++]=i;
    }
    for(int i=1;i<=n;i++) max_sum+=1LL*a[i]*(R2[i]-i)*(i-L2[i]);
    for(int i=1;i<=n;i++) min_sum+=1LL*a[i]*(R1[i]-i)*(i-L1[i]);
    //printf("%lld %lld\n",max_sum,min_sum);
    for(int i=0;i<q;i++){
        cin>>str;
        int pos;
        scanf("%d",&pos);
        if(str[0]=='+'){
            //compute cont to max_sum
            int l=seg.find_pos(1,1,n,pos,1,1);
            int r=seg.find_pos(1,1,n,pos,0,1);
            //printf("+ l=%d r=%d\n",l,r);
            if(l==-1) l=0; 
            if(r==-1) r=n+1;
            max_sum+=1LL*(r-pos)*(pos-l);
            //compute cont to min_sum
            a[pos]++; seg.update(1,1,n,pos,1);
            l=seg.find_pos(1,1,n,pos,1,0);
            r=seg.find_pos(1,1,n,pos,0,0);
            if(l==-1) l=0; 
            if(r==-1) r=n+1;
            //printf("+ l=%d r=%d\n",l,r);
            min_sum+=1LL*(r-pos)*(pos-l);
        }
        else{
            //compute cont to min_sum
            int l=seg.find_pos(1,1,n,pos,1,0);
            int r=seg.find_pos(1,1,n,pos,0,0);
            //printf("- l=%d r=%d\n",l,r);
            if(l==-1) l=0; 
            if(r==-1) r=n+1;
            min_sum-=1LL*(r-pos)*(pos-l);
            //compute cont to max_sum
            a[pos]--; seg.update(1,1,n,pos,-1);
            l=seg.find_pos(1,1,n,pos,1,1);
            r=seg.find_pos(1,1,n,pos,0,1);
            //printf("- l=%d r=%d\n",l,r);
            if(l==-1) l=0; 
            if(r==-1) r=n+1;
            max_sum-=1LL*(r-pos)*(pos-l);
        }
        //printf("%lld %lld\n",max_sum,min_sum);
        printf("%lld\n",max_sum-min_sum);
    }
    return 0;
}

