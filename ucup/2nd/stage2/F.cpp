#pragma GCC optimize(2)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int T;
int king_dx[8]={-1,-1,-1,0,0,1,1,1};
int king_dy[8]={-1,0,1,-1,1,-1,0,1};
vector<int> rG[64*64*64*2];
int deg[64*64*64*2];
int dp[64*64*64*2];  //-1 for initialization, 0 for draw, 1 for win
bool white_under_check(int pawn,int wking,int bking){
    int wx=wking/8,wy=wking%8,bx=bking/8,by=bking%8;
    return max(wx-bx,bx-wx)<=1&&max(wy-by,by-wy)<=1;
}
bool black_under_check(int pawn,int wking,int bking){
    int px=pawn/8,py=pawn%8,wx=wking/8,wy=wking%8,bx=bking/8,by=bking%8;
    if(max(wx-bx,bx-wx)<=1&&max(wy-by,by-wy)<=1) return true;
    if(by==py&&bx==px-1) return true;
    if(by==py&&bx==px-2&&px==6) return true;
    return false;
}
bool black_can_capture(int pawn,int wking,int bking){
    //assert(!white_under_check(bishop,knight,wking,bking));
    int px=pawn/8,py=pawn%8,wx=wking/8,wy=wking%8,bx=bking/8,by=bking%8;
    for(int i=0;i<8;i++){
        int nx=bx+king_dx[i],ny=by+king_dy[i];
        if(nx<0||nx>=8||ny<0||ny>=8) continue;
        if(black_under_check(pawn,wking,nx*8+ny)) continue;
        if(nx==px&&ny==py) return true;
    }
    return false;
}
bool white_can_promote(int pawn,int wking,int bking){
    //assert(!black_under_check(pawn,wking,bking));
    int px=pawn/8,py=pawn%8,wx=wking/8,wy=wking%8,bx=bking/8,by=bking%8;
    if(px==1&&(px-1)*8+py!=wking){
        if(black_can_capture((px-1)*8+py,wking,bking)) return false;
        return true;
    }
    return false;
}
bool black_no_valid_moves(int pawn,int wking,int bking){
   // assert(!white_under_check(bishop,knight,wking,bking));
    int px=pawn/8,py=pawn%8,wx=wking/8,wy=wking%8,bx=bking/8,by=bking%8;
    for(int i=0;i<8;i++){
        int nx=bx+king_dx[i],ny=by+king_dy[i];
        if(nx<0||nx>=8||ny<0||ny>=8) continue;
        if(black_under_check(pawn,wking,nx*8+ny)) continue;
        return false;
    }
    return true;
}
bool is_checkmate(int pawn,int wking,int bking){
    //assert(!white_under_check(bishop,knight,wking,bking));
    return black_under_check(pawn,wking,bking)&&black_no_valid_moves(pawn,wking,bking);
}
bool is_stalemate(int pawn,int wking,int bking){
    //assert(!white_under_check(bishop,knight,wking,bking));
    return (!black_under_check(pawn,wking,bking))&&black_no_valid_moves(pawn,wking,bking);
}
vector<int> black_valid_moves(int pawn,int wking,int bking){
    //assert(!white_under_check(pawn,wking,bking));
    int px=pawn/8,py=pawn%8,wx=wking/8,wy=wking%8,bx=bking/8,by=bking%8;
    vector<int> v;
    for(int i=0;i<8;i++){
        int nx=bx+king_dx[i],ny=by+king_dy[i];
        if(nx<0||nx>=8||ny<0||ny>=8) continue;
        if(nx==px&&ny==py) continue;
        //if(black_no_valid_moves(bishop,knight,wking,nx*8+ny)) continue;
        if(black_under_check(pawn,wking,nx*8+ny)) continue;
        //assert(!black_no_valid_moves(bishop,knight,wking,nx*8+ny));
        v.push_back(nx*8+ny);
    }
    return v;
}
vector<int> white_king_valid_moves(int pawn,int wking,int bking){
    //assert(!white_under_check(bishop,knight,wking,bking));
    //assert(!black_under_check(pawn,wking,bking));
    int px=pawn/8,py=pawn%8,wx=wking/8,wy=wking%8,bx=bking/8,by=bking%8;
    vector<int> v;
    for(int i=0;i<8;i++){
        int nx=wx+king_dx[i],ny=wy+king_dy[i];
        if(nx<0||nx>=8||ny<0||ny>=8) continue;
        if(nx==px&&ny==py) continue;
        if(white_under_check(pawn,nx*8+ny,bking)) continue;
        v.push_back(nx*8+ny);
    }
    return v;
}
vector<int> pawn_valid_moves(int pawn,int wking,int bking){
    //assert(!white_under_check(bishop,knight,wking,bking));
    //assert(!black_under_check(pawn,wking,bking));
    int px=pawn/8,py=pawn%8,wx=wking/8,wy=wking%8,bx=bking/8,by=bking%8;
    vector<int> v;
    if((pawn-8!=wking)&&(pawn-8!=bking)&&!white_under_check(pawn-8,wking,bking)){
        v.push_back(pawn-8);
    }
    if(px==6){
        if((pawn-16!=wking)&&(pawn-16!=bking)&&(pawn-8!=wking)&&(pawn-8!=bking)&&!white_under_check(pawn-16,wking,bking)){
        v.push_back(pawn-16);    
    }
    }
    return v;
}
int get_id(int pawn,int wking,int bking,int moves){
    int id=pawn*64*64*2+wking*64*2+bking*2+moves;
    return id;
}
char s[4][10];
int get_pos(int id){
    return ('8'-s[id][1])*8+(s[id][0]-'a');
}
int main()
{
    memset(dp,-1,sizeof(dp));
    queue<int> que;
    for(int pawn=8;pawn<56;pawn++)
        for(int wking=0;wking<64;wking++){
            if(wking==pawn) continue;
            for(int bking=0;bking<64;bking++){
                if(bking==pawn||bking==wking) continue;
                if(white_under_check(pawn,wking,bking)) continue;
                for(int moves=0;moves<2;moves++){
                    int id=get_id(pawn,wking,bking,moves);
                    if(moves==1){//black moves
                        if(is_stalemate(pawn,wking,bking)) {dp[id]=0; que.push(id); continue;}
                        if(is_checkmate(pawn,wking,bking)) {dp[id]=1; /*printf("checkmate %d %d %d\n",pawn,wking,bking);*/ que.push(id); continue;}
                        if(black_can_capture(pawn,wking,bking))  {dp[id]=0; que.push(id); continue;} 
                        vector<int> king=black_valid_moves(pawn,wking,bking);
                        for(auto x:king){
                            int nid=get_id(pawn,wking,x,0);
                            rG[nid].push_back(id); deg[id]++;
                        }

                    }
                        //count degrees
                    else{//white moves,previous is black
                        if(black_under_check(pawn,wking,bking)) continue;
                        if(white_can_promote(pawn,wking,bking)) {dp[id]=1; /*printf("promote %d %d %d\n",pawn,wking,bking);*/ que.push(id); continue;}
                        vector<int> king=white_king_valid_moves(pawn,wking,bking);
                        for(auto x:king){
                            int nid=get_id(pawn,x,bking,1);
                            rG[nid].push_back(id); deg[id]++;
                        }
                        vector<int> npawn=pawn_valid_moves(pawn,wking,bking);
                        for(auto x:npawn){
                            int nid=get_id(x,wking,bking,1);
                            rG[nid].push_back(id); deg[id]++;
                        }
                    }
                }
            }
        }
    //puts("done1");
    while(que.size()){
        int x=que.front(); que.pop();
        int pawn=((x/(64*64*2))&63),wking=((x/(64*2))&63),bking=((x/2)&63),moves=x&1;
        int id=get_id(pawn,wking,bking,moves);
       // if(dp[id]) printf("pawn=%d wking=%d bking=%d dp=%d\n",pawn,wking,bking,dp[id]);
        int bx=bking/8,by=bking%8;
        //assert(bx<4&&by<4);
       // assert(!white_under_check(bishop,knight,wking,bking));
        //if(dp[id]==-1) printf("bishop=%d knight=%d wking=%d bking=%d\n",bishop,knight,wking,bking);
      //  assert(dp[id]!=-1); assert(dp[id]!=INF);
        if(moves==0){//white to move, update black
            if(dp[x]==1){//winning for white
                for(auto to:rG[x]){
                    deg[to]--; if(deg[to]==0&&dp[to]==-1) {dp[to]=1; que.push(to);}
                }
            }
            else{
                for(auto to:rG[x]){
                    if(dp[to]==-1) {dp[to]=0; que.push(to);}
                }
            }
        }
        else{//black to move, update white
            if(dp[x]==1){//winning for white
                for(auto to:rG[x]){
                    if(dp[to]==-1) {dp[to]=1; que.push(to);}
                }
            }
            else{
                for(auto to:rG[x]){
                    deg[to]--; if(deg[to]==0&&dp[to]==-1) {dp[to]=0; que.push(to);}
                }
            }
        }
    }
    //puts("done2");
    scanf("%d",&T);
    while(T--){
        int pawn,wking,bking;
        for(int i=0;i<4;i++) scanf("%s",s[i]);
        pawn=get_pos(1); bking=get_pos(2); wking=get_pos(0);
        //printf("pawn=%d wking=%d bking=%d\n",pawn,wking,bking);
        int move=(s[3][0]=='w'?0:1);
        int id=get_id(pawn,wking,bking,move);
        //assert(bx<4&&by<4);
        //printf("dp=%d\n",dp[id]);
        if(dp[id]==-1||dp[id]==0) printf("Draw\n"); else printf("Win\n");
    }
    return 0;
}
