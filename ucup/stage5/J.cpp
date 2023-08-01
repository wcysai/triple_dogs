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
bool hasa[11],hasb[11];
vector<int> v1,v2;
void dfs(int now,int x,int y){
    hasa[x]=true; hasb[y]=true;
    v1.push_back(x); v2.push_back(y);
    if(now==10) {
        for(auto z:v1) printf("%d ",z);
        puts("");
        for(auto z:v2) printf("%d ",z);
        puts("");
        exit(0);
    }
    if(x+3<=10&&!hasa[x+3]&&y+1<=10&&!hasb[y+1]) dfs(now+1,x+3,y+1);
    if(x+3<=10&&!hasa[x+3]&&y-1>0&&!hasb[y-1]) dfs(now+1,x+3,y-1);
    if(x-3>0&&!hasa[x-3]&&y+1<=10&&!hasb[y+1]) dfs(now+1,x-3,y+1);
    if(x-3>0&&!hasa[x-3]&&y-1>0&&!hasb[y-1]) dfs(now+1,x-3,y-1);
    if(x+1<=10&&!hasa[x+1]&&y+3<=10&&!hasb[y+3]) dfs(now+1,x+1,y+3);
    if(x+1<=10&&!hasa[x+1]&&y-3>0&&!hasb[y-3]) dfs(now+1,x+1,y+3);
    if(x-1>0&&!hasa[x-1]&&y+3<=10&&!hasb[y+3]) dfs(now+1,x-1,y+3);
    if(x-1>0&&!hasa[x-1]&&y-3>0&&!hasb[y-3]) dfs(now+1,x-1,y-3);
    hasa[x]=hasb[y]=false;
    v1.pop_back(); v2.pop_back();
}
void solve(int x,int y){
    memset(hasa,false,sizeof(hasa)); memset(hasb,false,sizeof(hasb));
    hasa[x]=hasb[y]=true;
    dfs(1,x,y);
}
int main()
{
    for(int i=1;i<=10;i++)
        for(int j=1;j<=10;j++)
            solve(i,j);
    return 0;
}

