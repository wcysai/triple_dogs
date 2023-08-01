#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
ll m,d,c,l,v,x,i;
ll cnt[4][10],ans[4000];
string d0[10]={
    "","I","II","III","IV","V","VI","VII","VIII","IX"
};
string d1[10]={
    "","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"
};
string d2[10]={
    "","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"
};
string d3[4]={
    "","M","MM","MMM"
};
void print(int x){
    cout << d3[x/1000] << d2[(x/100)%10] << d1[(x/10)%10] << d0[x%10];
}
bool check(ll tot){
    ll M,D,C,L,V,X,I,nt;
    M=m; D=d; C=c; L=l; V=v; X=x; I=i;
    memset(cnt,0,sizeof(cnt));
    if (M>tot*4) return 0;
    if (M>tot*3){
        ll num=M-tot*3;
        cnt[3][3]+=tot;
        cnt[2][9]+=num;
        C-=num; if (C<0) return 0;
    } else {
        ll num=M/3;
        cnt[3][3]+=num; M-=num*3;
        if (M>0) cnt[3][M]++;
    }
    
    nt=tot-cnt[2][9];
    if (C>nt*3+tot) return 0;
    if (C>nt*3){
        ll num=C-nt*3;
        cnt[2][3]+=nt;
        cnt[1][9]+=num;
        X-=num; if (X<0) return 0;
    } else {
        ll num=C/3;
        cnt[2][3]+=num; C-=num*3;
        if (C>0) cnt[2][C]++;
    }

    nt=tot-cnt[1][9];
    if (X>nt*3+tot) return 0;
    if (X>nt*3){
        ll num=X-nt*3;
        cnt[1][3]+=nt;
        cnt[0][9]+=num;
        I-=num; if (I<0) return 0;
    } else {
        ll num=X/3;
        cnt[1][3]+=num; X-=num*3;
        if (X>0) cnt[1][X]++;
    }

    nt=tot-cnt[0][9];
    if (I>nt*3) return 0;
    else {
        ll num=I/3;
        cnt[0][3]+=num; I-=num*3;
        if (I>0) cnt[0][I]++;
    }

    for (int i=0;i<4;i++){
        cnt[i][0]=tot;
        for (int j=1;j<=9;j++) cnt[i][0]-=cnt[i][j];
    }

    for (int i=0;i<=2;i++){
        ll tmp; 
        if (i==2) tmp=D; else if (i==1) tmp=L; else tmp=V;
        for (int j=0;j<=3;j++){
            ll res=min(tmp,cnt[i][j]);
            cnt[i][j]-=res; cnt[i][j+5]+=res;
            tmp-=res;
        }
        if (tmp>0) return 0;
    }

    return 1;
}
void build(){
    memset(ans,0,sizeof(ans));
    for (int i=3999;i;i--){
        int c0=i%10,c1=(i/10)%10,c2=(i/100)%10,c3=i/1000;
        ll res=min(min(cnt[0][c0],cnt[1][c1]),min(cnt[2][c2],cnt[3][c3]));
        ans[i]=res;
        cnt[0][c0]-=res;
        cnt[1][c1]-=res;
        cnt[2][c2]-=res;
        cnt[3][c3]-=res;
    }
}
int main(){
    cin >> m >> d >> c >> l >> x >> v >> i;
    ll L=0,R=1e18;
    while (R-L>1){
        ll mid=(L+R)>>1;
        if (check(mid)) R=mid; else L=mid;
    }
    cout << R << endl;
    check(R); build();
    int nc=0; for (int i=1;i<=3999;i++) if (ans[i]) nc++;
    cout << nc << endl;
    for (int i=1;i<=3999;i++){
        if (ans[i]){
            print(i);
            cout << " " << ans[i] << endl;
        }
    }
}