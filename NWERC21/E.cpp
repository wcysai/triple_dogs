#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=300007;
int n;
int a[N],b[N],p[N],q[N];
struct BIT{
    int C[N];
    void init(){memset(C,0,sizeof(C));}
int lowbit(int u){return u&(-u);}
void update(int u,int w){
    for (int i=u;i<N;i+=lowbit(i)) C[i]+=w;
}
int query(int u){
    int ans=0;
    for (int i=u;i;i-=lowbit(i)) ans+=C[i];
    return ans;
}
}bb[2];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n;
    bb[0].init(), bb[1].init();
    for (int i=1;i<=n;++i) cin>>a[i];
    for (int i=1;i<=n;++i) cin>>b[i];
    for (int i=1;i<=n;++i) p[i]=i, q[i]=i, bb[0].update(i,1), bb[1].update(i,1);
    sort(p+1,p+n+1,[&](int u,int v){return a[u]<a[v]||(a[u]==a[v]&&u<v);});
    sort(q+1,q+n+1,[&](int u,int v){return b[u]<b[v]||(b[u]==b[v]&&u<v);});
    int idx=1;
    int ans=0,sum=0;
    vector<pair<int,int>> fk;
    for (int i=1;i<=n;++i){
        if (i<n&&a[p[i]]==a[p[i+1]]) continue;
        for (int j=idx;j<=i;++j){
            int nowL=bb[0].query(p[j]), nowR=bb[1].query(q[j]);
            if (nowL<nowR) continue;
            ans+=abs(bb[0].query(p[j])-bb[1].query(q[j]));
            int prv=q[j];
            vector<int> fkk;
            fkk.push_back(prv);
            while (fk.size()<200000){
                if (nowL==nowR) break;
                if (nowL<nowR){
                    int L=1,R=n;
                    while (L<R){
                        int md=(L+R)>>1;
                        if (bb[1].query(md)>=nowR-1) R=md;
                        else L=md+1;
                    }
                    fkk.push_back(L);
                    // cerr<<nowL<<":"<<nowR<<endl;
                    nowR--;
                }
                else{
                    int L=1,R=n;
                    while (L<R){
                        int md=(L+R)>>1;
                        if (bb[1].query(md)>=nowR+1) R=md;
                        else L=md+1;
                    }
                    fkk.push_back(L);
                    nowR++;
                }
            }
            reverse(fkk.begin(),fkk.end());
            for (int i=1;i<fkk.size();++i){
                if (fk.size()>=200000) break;
                fk.push_back({fkk[i-1],fkk[i]});
            }
        }
        for (int j=i;j>=idx;--j){
            int nowL=bb[0].query(p[j]), nowR=bb[1].query(q[j]);
            if (nowL>nowR) continue;
            ans+=abs(bb[0].query(p[j])-bb[1].query(q[j]));
            int prv=q[j];
            vector<int> fkk;
            fkk.push_back(prv);
            while (fk.size()<200000){
                if (nowL==nowR) break;
                if (nowL<nowR){
                    int L=1,R=n;
                    while (L<R){
                        int md=(L+R)>>1;
                        if (bb[1].query(md)>=nowR-1) R=md;
                        else L=md+1;
                    }
                    fkk.push_back(L);
                    // cerr<<nowL<<":"<<nowR<<endl;
                    nowR--;
                }
                else{
                    int L=1,R=n;
                    while (L<R){
                        int md=(L+R)>>1;
                        if (bb[1].query(md)>=nowR+1) R=md;
                        else L=md+1;
                    }
                    fkk.push_back(L);
                    nowR++;
                }
            }
            reverse(fkk.begin(),fkk.end());
            for (int i=1;i<fkk.size();++i){
                if (fk.size()>=200000) break;
                fk.push_back({fkk[i-1],fkk[i]});
            }
        }
        for (int j=idx;j<=i;++j) bb[0].update(p[j],-1), bb[1].update(q[j],-1);
        idx=i+1;
    }
    cout<<ans<<"\n";
    assert(fk.size()<=200000);
    for (auto c:fk) cout<<c.first<<" "<<c.second<<endl;
}