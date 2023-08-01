#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,MOD,cur;
char s[MAXN];
int pre[127][127],suf[127][127];
void madd(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
void mdec(int &a,int b) {a-=b; if(a<0) a+=MOD;}
void add(int c){
    for(int i=33;i<=126;i++) 
    {
        madd(cur,1LL*pre[i][0]*suf[i][c]%MOD);
        madd(pre[i][c],pre[i][0]);
    }
    madd(pre[c][0],1);
}
void dec(int c){
    mdec(suf[c][0],1);
    for(int i=33;i<=126;i++) 
    {
        mdec(cur,1LL*suf[i][0]*pre[i][c]%MOD);
        mdec(suf[i][c],suf[i][0]);
    }
}
void printpre(){
    puts("pre");
    for(int i=33;i<=126;i++)
        for(int j=33;j<=126;j++){
            if(pre[i][j]) printf("%c%c %d\n",(char)i,(char)j,pre[i][j]);
        }
}
void printsuf(){
    puts("suf");
    for(int i=33;i<=126;i++)
        for(int j=33;j<=126;j++){
            if(suf[i][j]) printf("%c%c %d\n",(char)i,(char)j,suf[i][j]);
        }
}
int main()
{
    scanf("%s",s+1);
    n=strlen(s+1);
    scanf("%d",&MOD);
    for(int i=n;i>=1;i--){
        int c=(int)s[i];
        for(int j=33;j<=126;j++) madd(suf[j][c],suf[j][0]); 
        madd(suf[c][0],1);
    }
    //printsuf();
    int ans=0;
    for(int i=1;i<=n;i++){
        dec((int)s[i]);
        //printsuf();
        //printf("cur=%d\n",cur);
        madd(ans,cur);
        add((int)s[i]);
        //printpre();
        //printf("cur=%d\n",cur);
    }
    printf("%d\n",ans);
    return 0;
}

