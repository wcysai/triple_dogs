#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 30005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int x,y,p,q;
queue<int> que;
int dist[MAXN];
int get_id(int side,int sheep,int wolf){
    return side*(x+1)*(y+1)+sheep*(y+1)+wolf;
}
int main()
{
    scanf("%d%d%d%d",&x,&y,&p,&q);
    for(int i=0;i<=2*(x+1)*(y+1);i++) dist[i]=INF;
    dist[0]=0; que.push(0);
    while(que.size()){
        int v=que.front(); que.pop();
        int side=v/((x+1)*(y+1)),sheep=(v/(y+1))%(x+1),wolf=v%(y+1);
        //printf("side=%d sheep=%d wolf=%d dist=%d\n",side,sheep,wolf,dist[v]);
        if(side==0){
            int curs=x-sheep,curw=y-wolf;
            for(int i=0;i<=min(curs,p);i++){
                for(int j=0;j<=curw&&i+j<=p;j++){
                    if((curs-i)&&(curw-j>curs-i+q)) continue;
                    int nxt=(x+1)*(y+1)+(i+sheep)*(y+1)+(j+wolf);
                    if(dist[nxt]==INF){
                        dist[nxt]=dist[v]+1;
                        que.push(nxt);
                    }
                }
            }
        }
        else{
            for(int i=0;i<=min(sheep,p);i++){
                for(int j=0;j<=wolf&&i+j<=p;j++){
                    if(sheep-i&&(wolf-j>sheep-i+q)) continue;
                    int nxt=(sheep-i)*(y+1)+(wolf-j);
                    if(dist[nxt]==INF){
                        dist[nxt]=dist[v]+1;
                        que.push(nxt);
                    }
                }
            }
        }
    }
    int ans=INF;
    for(int i=0;i<=y;i++) ans=min(ans,dist[(x+1)*(y+1)+x*(y+1)+i]);
    if(ans==INF) printf("-1\n"); else printf("%d\n",ans);
    return 0;
}

