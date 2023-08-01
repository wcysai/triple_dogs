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
int t,l,r;
int p[100];
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&l,&r);
        int len=r-l+1;
        if(len%2==0){
            for(int i=l;i<=r;i++){
                if((i-l)&1) printf("%d",i-1); else printf("%d",i+1); 
                if(i==r) printf("\n"); else printf(" ");
            }
        }
        else if(len>=3){
            if(__gcd(l,l+2)==1){
                printf("%d %d %d ",l+1,l+2,l);
                for(int i=l+3;i<=r;i++){
                    if((i-l)&1) printf("%d",i+1); else printf("%d",i-1); 
                    if(i==r) printf("\n"); else printf(" ");
                }
                if(len==3) printf("\n");
            }
            else puts("-1");
        }
        else if(l==1) puts("1"); else puts("-1");
    }
    return 0;
}

