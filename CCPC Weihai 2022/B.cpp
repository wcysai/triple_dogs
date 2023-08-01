#include<bits/stdc++.h>
#define pb push_back
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int>pi;
const int maxn=1e6+10;
int n,m,s[maxn],t[maxn],pos[maxn],ans[maxn];
pi solve(int sum,int prod){
    if (sum<0) return (pi){-1,-1};
    ll d=(ll)sum*sum-(ll)prod*4;
    if (d<0) return (pi){-1,-1};
    ll sd=sqrt(d);
    if (sd*sd!=d) return (pi){-1,-1};
    ll a=sum-sd,b=sum+sd;
    if (a&1) return (pi){-1,-1};
    return (pi){a/2,b/2};
}
void print(vector<int> &a){
    int p[31];
    for (int i=0;i<a.size();i++) printf("%d ",a[i]);
    for (int i=a.size();i<n;i++) printf("1 "); puts("");
    for (int i=1;i<=m;i++) p[i]=i;
    for (int i=m;i;i--){
        int cur=p[pos[i]];
        ans[i]=cur;
        for (int j=pos[i]+1;j<=i;j++) p[j-1]=p[j];
    }
    int n1=m+1,n2=m;
    for (int i=1;i<=n-1;i++){
        if (s[i]-1==s[i+1]){
            printf("%d\n",n1++);
        } else {
            printf("%d\n",ans[n2--]);
        }
    }
}
void dfs(int x,vector<int> &a){
    if (x==m+1){print(a); exit(0);}
    set<int> S; S.clear();
    for (int i=0;i<x;i++){
        int v=a[i];
        if (S.find(v)!=S.end()) continue;
        S.insert(v);
        pi w=solve(v-t[x],v);
        if (w.F==-1) continue;
        pos[x]=i+1;
        vector<int> b; b.clear();
        for (int j=0;j<i;j++) b.pb(a[j]);
        b.pb(w.F); b.pb(w.S);
        for (int j=i+1;j<x;j++) b.pb(a[j]);
        dfs(x+1,b);
    }
}
int main(){
    cin >> n;
    for (int i=1;i<=n;i++) cin >> s[i];
    for (int i=n-1;i>=1;i--) if (s[i+1]!=s[i]-1){
        t[++m]=s[i+1]-s[i];
        if (t[m]<0) {puts("-1");return 0;}
    }
    if (m>=30){puts("-1");return 0;}
    vector<int> a(1); a[0]=s[n];
    dfs(1,a);
    puts("-1");
    return 0;
}