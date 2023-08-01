#include<bits/stdc++.h>
#define MAXN 100000
using namespace std;
int n,p[MAXN],r[MAXN];
void init(int n)
{
    for(int i=1;i<=n;i++)
    {
        p[i]=i;
        r[i]=0;
    }
}
int find(int x)
{
    if(p[x]==x) return x;
    else return p[x]=find(p[x]);
}
void unite(int x,int y)
{
    x=find(x);
    y=find(y);
    if(x==y) return;
    if(r[x]<r[y]) p[x]=y;
    else
    {
        p[y]=x;
        if(r[x]==r[y]) r[x]++;
    }
}
bool same(int x,int y)
{
    return find(x)==find(y);
}
int main()
{
    scanf("%d",&n);
    init(n);
    for(int i=0;i<n;i++){
        int x,y;
        scanf("%d%d",&x,&y);
        if(!same(x,y)){
            printf("N\n");
            unite(x,y);
        }
        else printf("Y\n");
    }
    return 0;
}

