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
int T,n,k,a[3][2][MAXN],b[2][MAXN],c[2][MAXN];
bool flipped[MAXN];
int val[3];
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
            for(int k=0;k<2;k++)
                for(int j=0;j<3;j++)
                    scanf("%d",&a[j][k][i]);
        for(int i=1;i<=n;i++) flipped[i]=false;
        set<P> s[3];
        for(int i=1;i<=n;i++)
            for(int j=0;j<3;j++)
                s[j].insert(P(a[j][0][i],i));
        int ans=INF;
        while(true){
            for(int i=0;i<3;i++){
                auto it1=s[i].begin();
                auto it2=s[i].end(); it2--;
                val[i]=(it2->F)-(it1->F);
            }
            ans=min(ans,max(max(val[0],val[1]),val[2]));
            int id=0;
            for(int i=1;i<3;i++) if(val[i]>val[id]) id=i;
            auto it1=s[id].begin();
            int x=it1->S;
            if(flipped[x]) break;
            flipped[x]=true;
            for(int i=0;i<3;i++){
                s[i].erase(P(a[i][0][x],x));
                s[i].insert(P(a[i][1][x],x));
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

