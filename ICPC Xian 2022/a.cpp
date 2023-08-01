#include<bits/stdc++.h>
#define F first
#define S second
#define pb push_back
using namespace std;
const int B=400;
typedef pair<int,int>pi;
int p[255][100005],b[100005];
int n,m,q,tot,pos[100005];
struct node{
    int t,x,y;
}a[100005];
bool cmp(node u,node v){
    if (u.y!=v.y) return u.y<v.y;
    return u.t<v.t;
}
bool cmp2(node u,node v){
    return u.t<v.t;
}
int main(){
    scanf("%d%d%d",&n,&m,&q);
    for (int i=1;i<=q;i++){
        int op; scanf("%d",&op); 
        a[i].t=i;
        if (op==1){
            scanf("%d%d",&a[i].x,&a[i].y);
        } else {
            scanf("%d",&a[i].x); a[i].y=-1;
        }
    }
    sort(a+1,a+q+1,cmp);
    for (int i=1;i<=q;i++) pos[a[i].t]=i;
    int r=(q+B-1)/B;
    for (int i=1;i<=r;i++)
        for (int j=1;j<=n;j++)
            p[i][j]=j;
    sort(a+1,a+q+1,cmp2);
    memset(b,-1,sizeof(b));
    for (int i=1;i<=q;i++){
        if (a[i].y==-1){
            int x=a[i].x;
            for (int j=1;j<=r;j++) x=p[j][x];
            printf("%d\n",x);
        } else {
            int u=(pos[i]+B-1)/B; b[pos[i]]=a[i].x;
            for (int j=u*B;j>(u-1)*B;j--){
                int x=b[j];
                if (x==-1) continue;
                p[u][x]=x; p[u][x+1]=x+1;
            }
            for (int j=u*B;j>(u-1)*B;j--){
                int x=b[j];
                if (x==-1) continue;
                swap(p[u][x],p[u][x+1]);
            }
        }
    }
    return 0;
}