#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,m,k,a[MAXN];
char s[MAXN];
mt19937 wcy(time(NULL));
int num[500];
void add(int &a,int b) {a+=b; if(a>=MOD) a-=MOD;}
struct mat{
    int a[2][2];
    void mult(mat &x){
        int tmp[2][2];
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                tmp[i][j]=0;
        for(int k=0;k<2;k++)
            for(int i=0;i<2;i++)
                for(int j=0;j<2;j++)
                    add(tmp[i][j],1LL*a[i][k]*x.a[k][j]%MOD);
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                a[i][j]=tmp[i][j];
    }
};
int pow_mod(int a,int i){
    int s=1;
    while(i){
        if(i&1) s=1LL*s*a%MOD;
        a=1LL*a*a%MOD;
        i>>=1;
    }
    return s;
}
mat A[8];
void gen(int id){
    A[id].a[0][0]=wcy()%MOD; A[id].a[0][1]=wcy()%(MOD-1)+1;
    A[id].a[1][0]=wcy()%(MOD-1)+1; A[id].a[1][1]=0;
    A[4+id].a[1][0]=pow_mod(A[id].a[0][1],MOD-2);
    A[4+id].a[1][1]=1LL*pow_mod(A[id].a[1][0],MOD-2)*(MOD-1LL*A[4+id].a[1][0]*A[id].a[0][0]%MOD)%MOD;
    A[4+id].a[0][0]=0;
    A[4+id].a[0][1]=pow_mod(A[id].a[1][0],MOD-2);
}
struct segtree{
    mat node[4*MAXN];
    void pushup(int k){
        node[k]=node[k*2]; node[k].mult(node[k*2+1]);
    }
    void build(int k,int l,int r){
        if(l==r){
            node[k]=A[num[s[l]]];
            return;
        }
        int mid=(l+r)/2;
        build(k*2,l,mid); build(k*2+1,mid+1,r);
        pushup(k);
    }
    void update(int k,int l,int r,int pos){
        if(l==r){
            node[k]=A[num[s[l]]];
            return;
        }
        int mid=(l+r)/2;
        if(pos<=mid) update(k*2,l,mid,pos); else update(k*2+1,mid+1,r,pos);
        pushup(k);
    }
    mat query(int k,int l,int r,int x,int y){
        if(l>y||x>r){
            mat tmp; tmp.a[0][0]=tmp.a[1][1]=1; tmp.a[1][0]=tmp.a[0][1]=0;
            return tmp;
        }
        if(l>=x&&r<=y) return node[k];
        int mid=(l+r)/2;
        mat lhs=query(k*2,l,mid,x,y); mat rhs=query(k*2+1,mid+1,r,x,y);
        lhs.mult(rhs);
        return lhs;
    }
}seg;
string str;
int main()
{
    for(int i=0;i<4;i++) gen(i);
    num[(int)'(']=0; num[(int)')']=4; num[(int)'[']=1; num[']']=5;
    num[(int)'{']=2; num[(int)'}']=6; num[(int)'<']=3; num['>']=7;
    scanf("%d",&n);
    scanf("%s",s+1);
    scanf("%d",&m);
    seg.build(1,1,n);
    for(int i=0;i<m;i++){
        int type;
        scanf("%d",&type);
        if(type==1){
            int x;
            scanf("%d",&x); cin>>str;
            s[x]=str[0];
            seg.update(1,1,n,x);
        }
        else{
            int l,r;
            scanf("%d%d",&l,&r);
            mat A=seg.query(1,1,n,l,r);
            if(A.a[0][0]!=1||A.a[1][1]!=1||A.a[0][1]!=0||A.a[1][0]!=0) printf("No\n");
            else printf("Yes\n");
        }
    }
    return 0;
}

