#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 500005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,unsigned> P;
int n,m;
unsigned p,q,mask;
struct qry{
    vector<P> v;
    void init(){
        v.clear(); v.push_back(P(0,0));
    }
    unsigned get_ans(int x){
        int id=upper_bound(v.begin(),v.end(),P(x,(unsigned)(-1)))-v.begin()-1;
        return v[id].S;
    }
};
qry merge(qry &a,qry &b){
    qry c;
    int now=0,i=0,j=0;
    c.v.push_back(P(0,a.v[0].S+b.v[0].S));
    //for(auto p:a.v) printf("(%d,%u)",p.F,p.S);
    //printf("\n");
    //for(auto p:b.v) printf("(%d,%u)",p.F,p.S);
    //printf("\n");
    while(i+1<(int)a.v.size()||j+1<(int)b.v.size()){
        unsigned nxt=-1;
        if(i+1<(int)a.v.size()&&a.v[i+1].F<nxt) nxt=a.v[i+1].F;
        if(j+1<(int)b.v.size()&&b.v[j+1].F<nxt) nxt=b.v[j+1].F;
        while(i+1<(int)a.v.size()&&a.v[i+1].F<=nxt) i++;
        while(j+1<(int)b.v.size()&&b.v[j+1].F<=nxt) j++;
        //printf("nxt=%u i=%d j=%d\n",nxt,i,j);
        c.v.push_back(P(nxt,a.v[i].S+b.v[j].S));
    }
    //for(auto p:c.v) printf("(%d,%u)",p.F,p.S);
    //printf("\n");
    return c;
}
struct bit{
    vector<qry> b[21];
    void init(){
        for(int i=0;i<=20;i++) b[i].clear(); 
    }
    void resolve(){
        for(int i=0;i<=18;i++){
            if((int)b[i].size()==2){
                qry z=merge(b[i][0],b[i][1]);
                b[i].clear();
                b[i+1].push_back(z);
            }
            else break;
        }
    }
    void add(int x,int y){
        qry tmp; 
        if(x==0){
            tmp.v.push_back(P(0,y));
        }
        else{
            tmp.v.push_back(P(0,0));
            tmp.v.push_back(P(x,y));
        }
        b[0].push_back(tmp);
        resolve();
    }
    unsigned sum(int y){
        unsigned z=0;
        for(int i=0;i<=19;i++){
            if(b[i].size()) z+=b[i][0].get_ans(y);
        }
        return z;
    }
}bit0,bit1;
int main()
{
    scanf("%d%d",&n,&m);
    mask=(1<<m)-1;
    unsigned x=0;
    for(int i=1;i<=n;i++){
        scanf("%u%u",&p,&q);
        p+=x; q+=x; p&=mask; q&=mask;
        unsigned l=min(p,q),r=max(p,q);
        //printf("l=%d r=%d\n",l,r);
        qry tmp; 
        if(l==0){
            tmp.v.push_back(P(0,-i*(l-1))); 
        }
        else {tmp.v.push_back(P(0,0)); tmp.v.push_back(P(l,-i*(l-1)));}
        tmp.v.push_back(P(r+1,i*(r-l+1)));
        bit0.b[0].push_back(tmp); bit0.resolve();
        tmp.v.clear();
        if(l==0){
            tmp.v.push_back(P(0,i)); 
        }
        else {tmp.v.push_back(P(0,0)); tmp.v.push_back(P(l,i));}
        tmp.v.push_back(P(r+1,0));
        bit1.b[0].push_back(tmp); bit1.resolve();
        unsigned sum=bit1.sum(r)*r+bit0.sum(r);
        //printf("sum=%d\n",sum);
        if(l>0) sum-=bit1.sum(l-1)*(l-1)+bit0.sum(l-1);
        x+=sum;
    }
    printf("%d\n",x&((1<<30)-1));
    return 0;
}

