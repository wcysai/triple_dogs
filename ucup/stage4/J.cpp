#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN];
int bit[MAXN],c,all,odd;
int deg[MAXN];
int sum(int i){
    int s=0;
    while(i>0){
        s+=bit[i];
        i-=i&-i;
    }
    return s;
}
void add(int i,int x){
    while(i<=n){
        bit[i]+=x;
        i+=i&-i;
    }
}
void solve(){
    if(all==1) printf("%d\n",n);
    else if(c==n) puts("-1");
    else if(odd) printf("%d\n",n-1);
    else printf("%d\n",n-2);
}
int main()
{
    scanf("%d%d",&n,&q);
    c=all=odd=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++){
        int s=sum(a[i]);
        int cnt=(i-1-s)+(a[i]-1-s);
        all+=(i-1-s);
        add(a[i],1);
        deg[a[i]]=cnt&1;
        odd+=(deg[a[i]]&1);
        if(a[i]==i) c++;
    }
    all=(all&1);
    for(int i=1;i<=q;i++){
        int u,v;
        scanf("%d%d",&u,&v);
        odd-=(deg[a[u]]&1); odd-=(deg[a[v]]&1);
        if(a[u]==u) c--; if(a[v]==v) c--;
        all^=1;
        if((u-v)&1) {deg[a[u]]^=1; deg[a[v]]^=1;}
        swap(a[u],a[v]);
        if(a[u]==u) c++; if(a[v]==v) c++;
        odd+=(deg[a[u]]&1); odd+=(deg[a[v]]&1);
        solve();
    }
    return 0;
}

