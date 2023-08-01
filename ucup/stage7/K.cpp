#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000009
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
//|A-B|*|B|
int solve(int n,vector<int> &v){
    if(n==0) return v[0];
    vector<int> tmp1,tmp2;
    for(int i=0;i<(1<<(n-1));i++) {
        int z=v[i]-v[i+(1<<(n-1))];
        if(z<0) z+=MOD;
        tmp1.push_back(z);
        tmp2.push_back(v[i+(1<<(n-1))]);
    }
    int x=solve(n-1,tmp1);
    int y=solve(n-1,tmp2);
    return 1LL*x*y%MOD;
}
int main()
{
    scanf("%d",&n);
    vector<int> v; v.resize((1<<n));
    for(int i=0;i<(1<<n);i++) scanf("%d",&v[i]);
    printf("%d\n",solve(n,v));
    return 0;
}

