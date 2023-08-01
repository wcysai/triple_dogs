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
int n,k,a[MAXN];
int p[MAXN];
char str[MAXN];
int main()
{
    scanf("%s",str+1);
    n=strlen(str+1);
    for(int i=1;i<=n;i++) p[i]=i;
    int len=INF,cnt=0;
    do{
        if(p[1]!=1) break;
        bool f=true;
        for(int i=1;i<=n;i++) if(str[p[i]]==(i==n?str[p[1]]:str[p[i+1]])) {f=false; break;}
        if(!f) continue;
        if(f){
            int s=0;
            for(int i=1;i<=n;i++){
                int x=p[i],y=(i==2*n?p[1]:p[i+1]);
                s+=max(x-y,y-x);
            }
            if(s<len) {len=s; cnt=1;}
            else if(s==len) cnt++;
        }
    }while(next_permutation(p+1,p+n+1));
    printf("cnt=%d\n",cnt/2);
    return 0;
}

