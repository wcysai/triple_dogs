#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m;
bool diag[3*MAXN],offdiag[3*MAXN];
int main()
{
    scanf("%d%d",&n,&m);
    if(n==1&&m==1){
        printf("1\n");
        printf("1 1\n");
        return 0;
    }
    if(n==m){
        printf("%d\n",2*n-2);
        for(int i=1;i<=n;i++) printf("%d %d\n",1,i);
        for(int i=2;i<=n-1;i++) printf("%d %d\n",n,i);
        return 0;
    }
    bool swapped=false;
    if(n>m){
        swap(n,m); 
        swapped=true;
    }
    vector<P> ans;
    
    for(int i=1;i<=n;i++){
        ans.push_back(P(i,1));
        diag[i+1]=true;
        offdiag[i-1+m]=true;
    }
    for(int i=1;i<=n;i++){
        ans.push_back(P(i,m));
        diag[i+m]=true;
        offdiag[i]=true;
    }
    if((n%2==0)&&(m%2==0)){
        for(int i=1;i<=m-n-2;i++){
            ans.push_back(P(n/2,i+n/2+1));
        }
    }
    else if(n&1){
        for(int i=1;i<=m-n-1;i++){
            ans.push_back(P((n+1)/2,i+n/2+1));
        }
    }
    else{
        for(int i=1;i<=m-n-2;i+=2){
            ans.push_back(P(n/2,i+n/2+1));
            ans.push_back(P(n/2+1,i+n/2+1));
        }
    }
    printf("%d\n",(int)ans.size());
    for(auto p:ans){
        if(swapped) printf("%d %d\n",p.S,p.F);
        else printf("%d %d\n",p.F,p.S);
    }
    return 0;
}

