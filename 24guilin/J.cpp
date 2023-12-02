#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 185
#define MAXS 400005
#define INF 1000000000
#define MOD1 998244353
#define MOD2 100000009
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,a[MAXN][MAXN],inva[MAXN][MAXN];
bool has[MAXS],nhas[MAXS];
int fact1[MAXN],fact2[MAXN];
int tmp[MAXN],ttmp[MAXN];
int perm[MAXS][10];
void add1(int &a,int b) {a+=b; if(a>=MOD1) a-=MOD1;}
void add2(int &a,int b) {a+=b; if(a>=MOD2) a-=MOD2;}
ll compute_hash(){
    int res1=0,res2=0;
    for(int k=1;k<=n-1;k++){
        int inv=0;
        for(int kk=k+1;kk<=n;kk++) if(tmp[kk]<tmp[k]) inv++;
        add1(res1,1LL*fact1[n-k]*inv%MOD1);
        add2(res2,1LL*fact2[n-k]*inv%MOD2);
    }
    return 1LL*res1*MOD2+res2;
}
unordered_set<ll> us;
void dfs(int now,bool chosen=false){
    if(now==m+1){
        if(!chosen) return;
        ll h=compute_hash(); us.insert(h);
        return;
    }
    dfs(now+1,chosen);
    for(int i=1;i<=n;i++) ttmp[i]=tmp[a[now][i]];
    for(int i=1;i<=n;i++) tmp[i]=ttmp[i];
    dfs(now+1,true);
    for(int i=1;i<=n;i++) ttmp[i]=tmp[inva[now][i]];
    for(int i=1;i<=n;i++) tmp[i]=ttmp[i];
}
int main()
{
    fact1[0]=fact2[0]=1;
    for(int i=1;i<=180;i++) fact1[i]=1LL*fact1[i-1]*i%MOD1;
    for(int i=1;i<=180;i++) fact2[i]=1LL*fact2[i-1]*i%MOD2;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++){
            scanf("%d",&a[i][j]);
            inva[i][a[i][j]]=j;
        }
    if(n<=9){
        for(int i=1;i<=n;i++) tmp[i]=i;
        int tot=0;
        do{
            for(int i=1;i<=n;i++) perm[tot][i]=tmp[i];
            tot++;
        }while(next_permutation(tmp+1,tmp+n+1));
        has[0]=true;
        bool id=false;
        for(int i=1;i<=m;i++){
            memset(nhas,false,sizeof(nhas));
            for(int j=0;j<fact1[n];j++){
                if(has[j]){
                    nhas[j]=true;
                    int res=0;
                    for(int k=1;k<=n;k++) tmp[k]=perm[j][a[i][k]];
                    for(int k=1;k<=n-1;k++){
                        int inv=0;
                        for(int kk=k+1;kk<=n;kk++) if(tmp[kk]<tmp[k]) inv++;
                        res+=fact1[n-k]*inv;
                    }
                    if(res==0) id=true;
                    nhas[res]=true;
                }
            }
            swap(has,nhas);
        }
        int ans=0;
        for(int i=0;i<fact1[n];i++) if(has[i]) ans++;
        if(!id) ans--;
        printf("%d\n",ans);
    }
    else{
        for(int i=1;i<=n;i++) tmp[i]=i;
        dfs(1); printf("%d\n",(int)us.size());
    }
    return 0;
}

