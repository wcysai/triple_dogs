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
int n,m,q,a[MAXN],b[MAXN];
int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++) scanf("%d%d",&a[i],&b[i]);
    for(int i=0;i<q;i++){
        int type;
        scanf("%d",&type);
        if(type==1){
            int x,y;
            scanf("%d%d",&x,&y);
            b[x]=y;
        }
        else{
            int x;
            scanf("%d",&x);
            int id=0;
            for(int i=1;i<=n;i++){
                if(b[i]==1&&a[i]>a[id]) id=i; 
            }
            if(id==x) {printf("%d\n",1); continue;}
            int cnt=0;
            for(int i=1;i<=n;i++){
                if(i==id) continue;
                if(a[i]>a[x]) cnt++;
            }
            if(cnt>=m-(id?1:0)) printf("%d\n",0); else printf("%d\n",1); 
        }
    }
    return 0;
}

