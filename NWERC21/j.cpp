#include<bits/stdc++.h>
using namespace std;
int x[1005],y[1005],vis[360];
int main(){
    int n; cin >> n;
    for (int i=0;i<n;i++){
        cin >> x[i] >> y[i];
        y[i]+=180;
    }
    x[n]=x[0],y[n]=y[0];
    for (int i=0;i<n;i++){
        int u=y[i],v=y[i+1];
        if (u>v) swap(u,v);
        if (v-u<=180){
            for (int j=u;j<v;j++) vis[j]=1;
        } 
        if (v-u>=180){
            for (int j=0;j<u;j++) vis[j]=1;
            for (int j=v;j<360;j++) vis[j]=1;
        }
    }
    int p=-1;
    for (int i=0;i<360;i++) if (!vis[i]) {p=i;break;}
    if (p==-1) puts("yes");
    else {
        double ans=0.5+p-180;
        printf("no %.1f\n",ans);
    }
}