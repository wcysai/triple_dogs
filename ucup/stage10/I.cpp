#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 400005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
#define left dajadkao
#define right daosadk
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,l[MAXN],r[MAXN];
vector<P> rpos[MAXN],lpos[MAXN];
ll pre[MAXN],suf[MAXN];
int left[MAXN],right[MAXN],rightmost[MAXN],leftmost[MAXN];
ll rsum[MAXN],lsum[MAXN],ans[MAXN];
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d%d",&l[i],&r[i]);
        rpos[l[i]].push_back(P(l[i],1));
        rpos[r[i]+1].push_back(P(l[i],-1));
        lpos[r[i]].push_back(P(r[i],1));
        lpos[l[i]-1].push_back(P(r[i],-1));
    }
    for(int i=1;i<=n;i++) {rsum[r[i]]++; lsum[l[i]]++;}
    for(int i=1;i<=2*n;i++) {
        rsum[i]+=rsum[i-1];
        lsum[i]+=lsum[i-1];
    }
    multiset<int> ms;
    for(int i=1;i<=2*n;i++){
        for(auto p:rpos[i]){
            if(p.S==1) ms.insert(p.F);
            else ms.erase(ms.find(p.F));
        }
        left[i]=(*ms.begin());
    }
    for(int i=1;i<=2*n;i++){
        if(left[i]==i) leftmost[i]=i;
        else leftmost[i]=leftmost[left[i]];
    }
    for(int i=1;i<=2*n;i++){
        if(left[i]==i) pre[i]=0;
        else pre[i]=pre[left[i]]+(rsum[i-1]-rsum[leftmost[i]-1])+(rsum[i-1]-rsum[left[i]-1]);
    }
    ms.clear();
    for(int i=2*n;i>=1;i--){
        for(auto p:lpos[i]){
            if(p.S==1) ms.insert(p.F);
            else ms.erase(ms.find(p.F));
        }
        right[i]=*(--ms.end());
    }
    for(int i=2*n;i>=1;i--){
        if(right[i]==i) rightmost[i]=i;
        else rightmost[i]=rightmost[right[i]];
    }
    for(int i=2*n;i>=1;i--){
        if(right[i]==i) suf[i]=0;
        else suf[i]=suf[right[i]]+(lsum[rightmost[i]]-lsum[i])+(lsum[right[i]]-lsum[i]);
    }
    /*printf("left: ");
    for(int i=1;i<=2*n;i++) printf("%d%c",left[i],i==2*n?'\n':' ');
    printf("right: ");
    for(int i=1;i<=2*n;i++) printf("%d%c",right[i],i==2*n?'\n':' ');
    printf("pre: ");
    for(int i=1;i<=2*n;i++) printf("%d%c",pre[i],i==2*n?'\n':' ');
    printf("suf: ");
    for(int i=1;i<=2*n;i++) printf("%d%c",suf[i],i==2*n?'\n':' ');*/
    for(int i=1;i<=n;i++){
        ll cnt=n-1-rsum[l[i]-1]-(lsum[2*n]-lsum[r[i]]);
        ans[i]=cnt+pre[l[i]]+suf[r[i]];
        printf("%lld\n",ans[i]);
    }
    return 0;
}

