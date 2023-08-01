#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5;
ll f[26][26],g[26][26],ans;
ll t[maxn][26],sz[maxn];
int n,q,id[26],cnt=0,rt=0;
char s[maxn],ord[30];
int nxt(int p,int x){
    if (t[p][x]==-1) t[p][x]=++cnt;
    return t[p][x];
}
int main(){
    memset(t,-1,sizeof(t));
    scanf("%d%d",&n,&q);
    for (int i=1;i<=n;i++){
        scanf("%s",s);
        int len=strlen(s);
        int pos=rt;
        for (int j=0;j<len;j++){
            int x=s[j]-'a';
            for (int k=0;k<x;k++){
                int pp=t[pos][k];
                if (pp==-1) continue;
                f[k][x]+=sz[pp];
            }
            for (int k=x+1;k<26;k++){
                int pp=t[pos][k];
                if (pp==-1) continue;
                g[x][k]+=sz[pp];
            }
            sz[pos]++;
            pos=nxt(pos,x);
        }
        for (int k=0;k<26;k++) {
            int pp=t[pos][k];
            if (pp==-1) continue;
            ans+=sz[pp];
        }
        sz[pos]++;
    }
    while (q--){
        scanf("%s",ord);
        for (int i=0;i<26;i++) id[ord[i]-'a']=i;
        ll Ans=ans;
        for (int i=0;i<26;i++)
            for (int j=i+1;j<26;j++)
                if (id[i]<id[j]) Ans+=g[i][j]; else Ans+=f[i][j];
        printf("%lld\n",Ans);
    }
    return 0;
}