#include<bits/stdc++.h>
#define pb push_back
using namespace std;
const int inf=18;
const int N=540;
typedef bitset<N> bs;
int dis[6][90][90];
bool vis[90];
string ans="JSCMXB";
bs R[6];
bool valid(int x,int y){
    return x>=0&&x<=9&&y>=0&&y<=8;
}
int gid(int x,int y){
    return x*9+y;
}
void add_edge(int o,int x,int y){
    dis[o][x][y]=1;
}
class cmp{
    public:
    bool operator()(bs &u,bs &v){
        int x=(u^v)._Find_first();
        if (x<N&&u[x]==0) return 1;
    }
};
map<bs,int,cmp> f,g;
int ck(bs T){
    int ret=0;
    for (int i=0;i<6;i++) if ((T&R[i]).count()) ret|=1<<i;
    return ret;
}
int solve(bs T,int dep){
    if (g.find(T)!=g.end()) return g[T];
    if (__builtin_popcount(ck(T))==1) return 0;
    int &ret=g[T],&best=f[T];
    ret=inf; best=-1;
    if (dep==3) return 1;
    for (int k=0;k<90;k++){
        bs S[19]; 
        int m=0;
        for (int i=0;i<=18;i++) S[i].reset();
        for (int i=0;i<6;i++)
            for (int j=0;j<90;j++)
                if (T[i*90+j]){
                    int x=dis[i][j][k];
                    m|=1<<x; S[x][i*90+j]=1;
                }
        if (__builtin_popcount(m)==1) continue;
        int now=0;
        for (int i=0;i<=18;i++) if ((m>>i)&1) now=max(now,solve(S[i],dep+1));
        if (now<ret) ret=now,best=k;
    }
    return ret;
}
int main(){
    for (int o=0;o<6;o++)
        for (int i=0;i<90;i++)
            for (int j=0;j<90;j++)
                dis[o][i][j]=(i==j)?0:inf;
    //J
    for (int i=0;i<=9;i++)
        for (int j=0;j<=8;j++){
            if (valid(i,j-1)) add_edge(0,gid(i,j),gid(i,j-1));
            if (valid(i,j+1)) add_edge(0,gid(i,j),gid(i,j+1));
            if (valid(i-1,j)) add_edge(0,gid(i,j),gid(i-1,j));
            if (valid(i+1,j)) add_edge(0,gid(i,j),gid(i+1,j));
        }
    //S
    for (int i=0;i<=9;i++)
        for (int j=0;j<=8;j++){
            if (valid(i-1,j-1)) add_edge(1,gid(i,j),gid(i-1,j-1));
            if (valid(i+1,j-1)) add_edge(1,gid(i,j),gid(i+1,j-1));
            if (valid(i-1,j+1)) add_edge(1,gid(i,j),gid(i-1,j+1));
            if (valid(i+1,j+1)) add_edge(1,gid(i,j),gid(i+1,j+1));
        }
    //C
    for (int i=0;i<=9;i++)
        for (int j=0;j<=8;j++){
            for (int k=0;k<=9;k++) if (k!=i) add_edge(2,gid(i,j),gid(k,j));
            for (int k=0;k<=8;k++) if (k!=j) add_edge(2,gid(i,j),gid(i,k));
        }
    //M
    for (int i=0;i<=9;i++)
        for (int j=0;j<=8;j++){
            if (valid(i-2,j-1)) add_edge(3,gid(i,j),gid(i-2,j-1));
            if (valid(i+2,j-1)) add_edge(3,gid(i,j),gid(i+2,j-1));
            if (valid(i-2,j+1)) add_edge(3,gid(i,j),gid(i-2,j+1));
            if (valid(i+2,j+1)) add_edge(3,gid(i,j),gid(i+2,j+1));
            if (valid(i-1,j-2)) add_edge(3,gid(i,j),gid(i-1,j-2));
            if (valid(i+1,j-2)) add_edge(3,gid(i,j),gid(i+1,j-2));
            if (valid(i-1,j+2)) add_edge(3,gid(i,j),gid(i-1,j+2));
            if (valid(i+1,j+2)) add_edge(3,gid(i,j),gid(i+1,j+2));
        }
    //X
    for (int i=0;i<=9;i++)
        for (int j=0;j<=8;j++){
            if (valid(i-2,j-2)) add_edge(4,gid(i,j),gid(i-2,j-2));
            if (valid(i+2,j-2)) add_edge(4,gid(i,j),gid(i+2,j-2));
            if (valid(i-2,j+2)) add_edge(4,gid(i,j),gid(i-2,j+2));
            if (valid(i+2,j+2)) add_edge(4,gid(i,j),gid(i+2,j+2));
        }
    //B
    for (int i=0;i<=9;i++)
        for (int j=0;j<=8;j++){
            if (valid(i+1,j)) add_edge(5,gid(i,j),gid(i+1,j));
            if (i>4&&valid(i,j-1)) add_edge(5,gid(i,j),gid(i,j-1));
            if (i>4&&valid(i,j+1)) add_edge(5,gid(i,j),gid(i,j+1));
        }
    
    for (int o=0;o<6;o++)
        for (int k=0;k<90;k++)
            for (int i=0;i<90;i++)
                for (int j=0;j<90;j++)
                    dis[o][i][j]=min(dis[o][i][j],dis[o][i][k]+dis[o][k][j]);
    
    for (int i=0;i<6;i++){
        R[i].reset();
        for (int j=0;j<90;j++) R[i][i*90+j]=1;
    }
    int n; bs T; 
    cin >> n; T.reset();
    for (int i=0;i<n;i++){
        int x,y; cin >> x >> y;
        for (int j=0;j<6;j++) T[j*90+gid(x,y)]=1;
    }
    cout << solve(T,0) << endl;
    return 0;
    while (__builtin_popcount(ck(T))>1){
        int k=f[T];
        cout << "? " << k/9 << " " << k%9 << endl;
        fflush(stdout);
        int x; cin >> x;
        bs S; S.reset();
        for (int i=0;i<6;i++)
            for (int j=0;j<90;j++)
                if (T[i*90+j]&&dis[i][j][k]==x) S[i*90+j]=1;
        T=S;
    }
    int tmp=ck(T);
    cout << "! ";
    for (int i=0;i<6;i++) 
        if ((tmp>>i)&1) cout << ans[i];
    cout << endl;
    return 0; 
}
