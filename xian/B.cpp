#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,q,a[MAXN];
struct node{
    int pred,mini,pretag;
    /*info before return operation
     * pred: shift before first return
     * mini: minimum pos before first return
     * pretag: the position of tag before first return (if no tag, pretag=INF)
     */
    int sufd,suftag;
    bool ret;
    /*
     * sufd: shift after first return (counting from the return)
     * suftag: the position of tag after first return (if no tag, suftag=INF)
     * ret: if return exist
     */
    void init(){
        pred=mini=0; pretag=suftag=INF;
        sufd=0; 
        ret=false;
    }
};
node merge(node &x,node &y){
    node tmp;
    if(!x.ret&&!y.ret){
        tmp.ret=false;
        tmp.sufd=0; tmp.suftag=INF;
        tmp.pred=x.pred+y.pred; tmp.mini=min(x.mini,x.pred+y.mini);
        int xtag=(x.pretag>y.mini+x.pred?INF:x.pretag);
        int ytag=(y.pretag==INF?INF:y.pretag+x.pred);
        tmp.pretag=min(xtag,ytag);
    }
    else if(x.ret){
        tmp.ret=true;
        tmp.pred=x.pred; tmp.mini=x.mini; tmp.pretag=x.pretag;
        if(y.ret){
            int xtag=(x.suftag>y.mini+x.sufd?INF:x.suftag);
            int ytag=(y.pretag==INF?INF:y.pretag+x.sufd);
            int ntag=min(xtag,ytag);
            int pos=x.sufd+y.pred;
            int ztag=(y.suftag==INF?INF:y.suftag+min(pos,ntag));
            tmp.suftag=ztag; tmp.sufd=min(pos,ntag)+y.sufd;
        }
        else{
            int xtag=(x.suftag>y.mini+x.sufd?INF:x.suftag);
            int ytag=(y.pretag==INF?INF:y.pretag+x.sufd);
            int ntag=min(xtag,ytag);
            int pos=x.sufd+y.pred;
            tmp.suftag=(pos>=ntag?ntag:INF); tmp.sufd=x.sufd+y.pred;
        }
    }
    else{
        tmp.ret=true; tmp.pred=x.pred+y.pred; tmp.mini=min(x.mini,x.pred+y.mini);
        int xtag=(x.pretag>y.mini+x.pred?INF:x.pretag);
        int ytag=(y.pretag==INF?INF:y.pretag+x.pred);
        tmp.pretag=min(xtag,ytag);
        tmp.suftag=y.suftag; tmp.sufd=y.sufd;
    }
    return tmp;
}
struct segtree{
    node a[4*MAXN];
    void pushup(int k){
        a[k]=merge(a[k*2],a[k*2+1]);
    }
    void build(int k,int l,int r){
        a[k].init();
        if(l==r) return;
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
    }
    void update(int k,int l,int r,int pos,int type){
        //if(k==1) {printf("k=%d l=%d r=%d pos=%d type=%d\n",k,l,r,pos,type);}
        if(l==r){
            if(type==0){//clear
                a[k].init();
            }
            else if(type==1){//add
                a[k].pretag=a[k].suftag=INF; a[k].pred=1; a[k].mini=0; a[k].sufd=0; a[k].ret=false;
            }
            else if(type==2){//dec
                a[k].pretag=a[k].suftag=INF; a[k].pred=-1; a[k].mini=-1; a[k].sufd=0; a[k].ret=false;
            }
            else if(type==3){//add tag
                a[k].pretag=0; a[k].suftag=INF; a[k].pred=0; a[k].mini=0; a[k].sufd=0; a[k].ret=false;
            }
            else{//go back
                a[k].pretag=INF; a[k].suftag=INF; a[k].pred=0; a[k].mini=0; a[k].sufd=0; a[k].ret=true;
            }
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos,type); else update(k*2+1,mid+1,r,pos,type);
        pushup(k);
    }
    node query(int k,int l,int r,int x,int y){
        if(l>=x&&r<=y) return a[k];
        if(l>y||r<x){
            node tmp; tmp.init();
            return tmp;
        }
        int mid=(l+r)/2;
        node lhs=query(k*2,l,mid,x,y); node rhs=query(k*2+1,mid+1,r,x,y);
        node tmp=merge(lhs,rhs);
        return tmp;
    }
    void print(int k,int l,int r){
        if(l==r) {
            printf("l=%d r=%d pred=%d mini=%d pretag=%d sufd=%d suftag=%d ret=%d\n",l,r,a[k].pred,a[k].mini,a[k].pretag,a[k].sufd,a[k].suftag,a[k].ret);
            return;
        }
        int mid=(l+r)/2;
        print(k*2,l,mid); print(k*2+1,mid+1,r);
        printf("l=%d r=%d pred=%d mini=%d pretag=%d sufd=%d suftag=%d ret=%d\n",l,r,a[k].pred,a[k].mini,a[k].pretag,a[k].sufd,a[k].suftag,a[k].ret);
    }
}seg;
vector<P> upd[MAXN];
vector<P> ans;
int main()
{
    scanf("%d%d",&n,&q);
    seg.build(1,1,q);
    for(int i=1;i<=q;i++){
        int op,l,r;
        scanf("%d%d%d",&op,&l,&r);
        assert(l<=r);
        if(op==5) upd[l].push_back(P(5,i));
        else{
            upd[l].push_back(P(op,i));
            upd[r+1].push_back(P(0,i));
        }
    }
    for(int i=1;i<=n;i++){
        sort(upd[i].begin(),upd[i].end());
        for(auto p:upd[i]){
            if(p.F==5){
                node tmp=seg.query(1,1,q,1,p.S);
                if(tmp.ret){
                    int res=(tmp.pretag==INF?500000+tmp.pred:500000+tmp.pretag)+tmp.sufd;
                    ans.push_back(P(p.S,res));
                }
                else{
                    int res=500000+tmp.pred;
                    ans.push_back(P(p.S,res));
                }
            }
            else seg.update(1,1,q,p.S,p.F);
            //seg.print(1,1,q);
        }
    }
    sort(ans.begin(),ans.end());
    for(auto p:ans) printf("%d\n",p.S);
    return 0;
}

