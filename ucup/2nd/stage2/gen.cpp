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
int n,m,q,a[MAXN];
mt19937 wcy(time(NULL));
bool in[MAXN];
int main()
{
    n=100000; m=100000; q=100000;
    printf("%d %d\n",n,m);
    set<P> s;
    while(s.size()<m){
        int u=0,v=0;
        while(u==v||s.count(P(u,v))){
            u=wcy()%n+1; v=wcy()%n+1;
            if(u>v) swap(u,v);
        }
        s.insert(P(u,v));
        printf("%d %d\n",u,v);
    }
    printf("%d\n",q);
    for(int i=0;i<q/2;i++){
        int v=wcy()%n+1;
        if(in[v]){
            printf("- %d\n",v);
            in[v]=false;
        }
        else{
            printf("+ %d\n",v);
            in[v]=true;
        }
    }
    for(int i=0;i<q/2;i++) printf("?\n");
    return 0;
}

