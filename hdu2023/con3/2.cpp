#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 50005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k;
int a[MAXN][5],v[MAXN];
int dp[MAXN];
int ord[MAXN],rk[MAXN];
bool cmp(int x,int y){
    return dp[x]>dp[y];
}
struct Bitset
{
    int sz;
	vector<unsigned> a;
	void reset()
	{
        a.clear(); a.resize(sz);
	}
	void flip(int x)
	{
		a[x>>5]^=1<<(x&31);
	}
	void set(int x)
	{
		a[x>>5]|=1<<(x&31);
	}
	void reset(int x)
	{
		a[x>>5]&=~(1<<(x&31));
	}
	int test(int x)
	{
		return (a[x>>5]>>(x&31))&1;
	}
	Bitset operator ~()const
	{
		Bitset ret;
		for(int i=0;i<sz;i++)ret.a[i]=~a[i];
		return ret;
	}
	Bitset operator &(const Bitset &b)const
	{
		Bitset ret; ret.sz=sz; ret.a.resize(sz);
		for(int i=0;i<sz;i++)ret.a[i]=a[i]&b.a[i];
		return ret;
	}
	Bitset operator |(const Bitset &b)const
	{
		Bitset ret;
		for(int i=0;i<sz;i++)ret.a[i]=a[i]|b.a[i];
		return ret;
	}
	Bitset operator ^(const Bitset &b)const
	{
		Bitset ret;
		for(int i=0;i<sz;i++)ret.a[i]=a[i]^b.a[i];
		return ret;
	}
	Bitset operator <<(const int t)const
	{
		Bitset ret;
		unsigned last=0;
		int high=t>>5,low=t&31;
		for(int i=0;i+high<sz;i++)
		{
			ret.a[i+high]=last|(a[i]<<low);
			if(low)last=a[i]>>(32-low);
		}
		return ret;
	}
	Bitset operator >>(const int t)const
	{
		Bitset ret;
		unsigned last=0;
		int high=t>>5,low=t&31;
		for(int i=sz-1;i>=high;i--)
		{
			ret.a[i-high]=last|(a[i]>>low);
			if(low)last=a[i]<<(32-low);
		}
		return ret;
	}
	int find_first()const
	{
		for(int i=0;i<sz;i++)
		{
            if(a[i]){
                for(int j=0;j<32;j++) if(a[i]&(1<<j)) return i*32+j;
            }
		}
		return -1;
	}
}bs[MAXN],bb;
void cdq(int l,int r){
    if(l>=r) return;
    int mid=(l+r)/2;
    cdq(l,mid);
    int len=mid+1-l;
    for(int i=l;i<=mid;i++) ord[i-l]=i;
    sort(ord,ord+len,cmp);
    for(int i=0;i<len;i++) rk[ord[i]]=i;
    for(int i=mid+1;i<=r;i++) {bs[i].sz=(len+31)/32; bs[i].reset();}
    bb.sz=(len+31)/32; 
    for(int i=0;i<5;i++){
        bb.reset();
        vector<P> tmpa;
        vector<P> tmpb;
        for(int j=l;j<=mid;j++)
            tmpa.push_back(P(a[j][i],rk[j]));
        sort(tmpa.begin(),tmpa.end());
        for(int j=mid+1;j<=r;j++) tmpb.push_back(P(a[j][i],j));
        sort(tmpb.begin(),tmpb.end());
        int now=0;
        for(int j=0;j<r-mid;j++){
            while(now<(int)tmpa.size()&&tmpa[now].F<=tmpb[j].F){
                bb.set(tmpa[now].S);
                now++;
            }
            if(i==0) bs[tmpb[j].S]=bb; else bs[tmpb[j].S]=bs[tmpb[j].S]&bb;
        }
    }
    for(int i=mid+1;i<=r;i++)  {int x=bs[i].find_first(); if(x!=-1) dp[i]=max(dp[i],v[i]+dp[ord[x]]);}
    cdq(mid+1,r);
}
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            for(int j=0;j<5;j++) scanf("%d",&a[i][j]);
            scanf("%d",&v[i]); 
            dp[i]=v[i];
        }
     //   puts("done");
        cdq(1,n);
    //    puts("ok");
        for(int i=1;i<=n;i++) printf("%d\n",dp[i]);
    }
    return 0;
}

