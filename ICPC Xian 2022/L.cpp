#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
using namespace std;
typedef long long ll;
int q,n;
vector<int> G[MAXN];
vector<int> vec;
int maxi,p[MAXN],cnt[MAXN];
int main()
{
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;i++) G[i].clear();
        for(int i=2;i<=n;i++) 
        {
            scanf("%d",&p[i]);
            G[p[i]].push_back(i);
        }
        vector<int> leaves;
        for(int i=1;i<=n;i++) 
        {
            cnt[i]=(int)G[i].size();
            if(cnt[i]==0) leaves.push_back(i);
        }
        int ans=(int)leaves.size();
        int c=0;
        while(leaves.size())
        {
            vector<int> tmp;
            for(auto x:leaves)
            {
                if(x!=1) 
                {
                    cnt[p[x]]--;
                    if(cnt[p[x]]==0) {tmp.push_back(p[x]);}
                }
            }
            swap(tmp,leaves);
            c++;
            ans=min(ans,c+(int)leaves.size());
        }
        printf("%d\n",ans);
    }
    return 0;
}