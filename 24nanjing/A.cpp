#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 1005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef vector<bool> vec;
typedef vector<vec> mat;
int T,n,m,k,a[MAXN],tot,ans;
char str[MAXN][MAXN];
int vis[MAXN][MAXN];
vector<P> shifts;
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
bool check(){
    bool flag=false;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(vis[i][j]==tot) continue;
            if(str[i][j]!='.') continue;
            bool f=true;
            for(auto p:shifts){
                int nx=i+p.F,ny=j+p.S;
                if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&str[nx][ny]=='.'); else f=false;
            }
            if(f) return false;
        }
    }
    return true;
}
int main()
{
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++) scanf("%s",str[i]+1);
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                vis[i][j]=0;
        tot=ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=m;j++){
                if(str[i][j]=='.'&&!vis[i][j]){ 
                    ++tot;
                    shifts.clear();
                    queue<P> que;
                    que.push(P(i,j)); vis[i][j]=tot; shifts.push_back(P(0,0));
                    while(que.size()){
                        P p=que.front(); que.pop();
                        int x=p.F,y=p.S;
                        for(int k=0;k<4;k++){
                            int nx=x+dx[k],ny=y+dy[k];
                            if(nx>=1&&nx<=n&&ny>=1&&ny<=m&&str[nx][ny]=='.'&&!vis[nx][ny]){
                                vis[nx][ny]=tot;
                                shifts.push_back(P(nx-i,ny-j));
                                que.push(P(nx,ny));
                            }
                        }
                    }
                    if(check()) ans+=(int)shifts.size();
                }
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}

