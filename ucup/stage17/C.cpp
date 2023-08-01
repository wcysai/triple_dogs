#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T,n,k,a[MAXN];
int d[MAXN][MAXN],r[MAXN][MAXN];
vector<P> ans;
void solve_sons(int v){
    int sz=0;
    while(sz<n-1){
        int u=d[v][2+sz];
        if(u<v) ans.push_back(P(u,v));
        int cnt=0;
        for(int i=1;i<=n;i++){
            if(r[i][v]<r[i][u]) cnt++;
        }
        sz+=(n-cnt);
    }
}
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        ans.clear();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++) {
                scanf("%d",&d[i][j]);
                r[i][d[i][j]]=j;
            }
        }
        for(int i=1;i<=n;i++) solve_sons(i);
        for(auto p:ans) printf("%d %d\n",p.F,p.S);
    }
    return 0;
}

