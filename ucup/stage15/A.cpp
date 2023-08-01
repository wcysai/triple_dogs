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
int n,k,a[MAXN],cnt;
int ask(int x){
    //cnt++;
    //printf("cnt=%d\n",cnt);
    printf("? %d\n",x);
    fflush(stdout);
    int z; scanf("%d",&z);
    return z;
}
void answer(int x){
    printf("! %d\n",x);
    fflush(stdout);
    exit(0);
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=min(n,20);i++){
        if(ask(i)==i-1) answer(i);
    }
    int l=21,r=n+1,cur=20;
    while(r-l>1){
        int mid=(l+r)/2;
        int z=ask(mid);
        if(cur==z) answer(mid);
        else if(z<cur) r=mid;
        else l=mid+1;
        cur=z;
    }
    answer(l);
    return 0;
}

