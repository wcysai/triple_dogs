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
int t,n,k;
ll a[MAXN];
int cnt[60];
bool check(int x){
    memset(cnt,0,sizeof(cnt));
    for(int i=n-x+1;i<=n;i++){
        if(a[i]) cnt[a[i]-1]++;
    }
    for(int i=n-x;i>=1;i--){
        int pos=-1;
        for(int j=a[i];j<=40;j++) if(cnt[j]){
            pos=j; break;
        }
        if(pos!=-1){
            if(a[i]==pos) cnt[a[i]]--;  else{
                for(int j=a[i];j<pos;j++) cnt[j]++; 
                cnt[pos]--;
            }
            if(a[i]) cnt[a[i]-1]++;
        }
        else return false;
    }
    return true;
}
int main()
{
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) {
            scanf("%lld",&a[i]);
            a[i]=__builtin_ctzll(a[i]);
        }
        sort(a+1,a+n+1);
        int l=0,r=n;
        while(r-l>1){
            int mid=(l+r)/2;
            if(check(mid)) r=mid; else l=mid;
        }
        printf("%d\n",r);
    }
    return 0;
}

