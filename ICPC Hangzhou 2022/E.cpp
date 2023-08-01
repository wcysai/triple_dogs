#include<bits/stdc++.h>
#define int long long
using namespace std;

int n,m;

set<vector<int>> st;
map<vector<int>,tuple<int,int,vector<int>>> mp;
int p[1007];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // int n=5;
    // vector<int> p(n,0);
    // for (int i=0;i<n;++i) p[i]=i;
    // do{
    //     vector<int> q=p;
    //     queue<vector<int>> que;
    //     que.push(q);
    //     st.clear();
    //     st.insert(q);
    //     while (que.size()){
    //         auto ret=que.front();
    //         que.pop();
    //         for (int x=1;x<n;++x){
    //             for (int y=1;x+y<n;++y){
    //                 vector<int> fk;
    //                 for (int i=y;i>0;--i) fk.push_back(ret[n-i]);
    //                 for (int i=x;i<n-y;++i) fk.push_back(ret[i]);
    //                 for (int i=0;i<x;++i) fk.push_back(ret[i]);
    //                 if (st.find(fk)!=st.end()) continue;
    //                 st.insert(fk), que.push(fk), mp[fk]={x,y,ret};
    //             }
    //         }
    //     }
    //     vector<int> aaa;
    //     for (int i=0;i<n;++i) aaa.push_back(i);
    //     if (st.find(aaa)==st.end()){
    //         cout<<"NO\n";
    //     }
    // }while (next_permutation(p.begin(),p.end()));
    int _;
    cin>>_;
    while (_--){
        auto solve=[&](){
            mt19937 rng(12345);
            int n;
            // n=7;
            cin>>n;
            for (int i=1;i<=n;++i) cin>>p[i];
            // for (int i=1;i<=n;++i) p[i]=i;
            // shuffle(p+1,p+n+1,rng);
            auto upd=[&](int x,int y){
                vector<int> fk;
                for (int i=y;i>0;--i) fk.push_back(p[n-i+1]);
                for (int i=x;i<n-y;++i) fk.push_back(p[i+1]);
                for (int i=0;i<x;++i) fk.push_back(p[i+1]);
                for (int i=1;i<=n;++i) p[i]=fk[i-1];
            };
            if (n==3){
                if (p[1]>p[3]) cout<<"1\n1 1\n";
                else cout<<"0\n";
                return;
            }
            vector<int> len, val;
            vector<pair<int,int>> ans;
            while (1){
                // for (int i=1;i<=n;++i){
                //     cout<<p[i]<<" ";
                // }
                // cout<<endl;
                len.clear(), val.clear();
                p[n+1]=1e9;
                int prv=0;
                for (int i=1;i<=n;++i){
                    if (p[i+1]==p[i]+1) continue;
                    len.push_back(i-prv), prv=i, val.push_back(p[i]); 
                }
                int w=len.size();
                if (len.size()<=6) break;
                vector<int> fuck=val;
                sort(fuck.begin(),fuck.end());
                map<int,int> true_val;
                for (int i=0;i<w;++i) true_val[fuck[i]]=i;
                for (int i=0;i<w;++i) val[i]=true_val[val[i]];
                int fst=val[0];
                int idx=-1;
                for (int i=0;i<w;++i) if (val[i]==fst-1) idx=i; 
                if (idx!=-1&&idx!=w-1){
                    int yy=0;
                    for (int i=idx+1;i<w;++i) yy+=len[i];
                    ans.push_back({len[0],yy});
                    upd(len[0],yy);
                    continue;
                }
                bool okk=0;
                for (int x=1;x<=4;++x){
                    for (int y=1;y<=4&&x+y<w;++y){
                        int vx=val[x-1], vy=val[w-y];
                        if (vy&&vx!=vy-1){
                            int xxx=0, yyy=0;
                            for (int i=0;i<x;++i) xxx+=len[i];
                            for (int j=1;j<=y;++j) yyy+=len[w-j];
                            ans.push_back({xxx,yyy});
                            upd(xxx,yyy);
                            okk=1; break;
                        }
                    }
                    if (okk) break;
                }
                assert(okk);
            }
            if (len.size()<=3){
                len.clear(), val.clear();
                int prv=0;
                for (int i=1;i<=n-3;++i){
                    if (p[i+1]==p[i]+1&&i<n-3) continue;
                    len.push_back(i-prv), prv=i, val.push_back(p[i]);
                }
                for (int i=2;i>-1;--i) len.push_back(1), val.push_back(p[n-i]);
            }
            vector<int> q=val;
            queue<vector<int>> que;
            que.push(q);
            st.clear();
            st.insert(q);
            while (que.size()){
                auto ret=que.front();
                que.pop();
                int w=val.size();
                for (int x=1;x<w;++x){
                    for (int y=1;x+y<w;++y){
                        vector<int> fk;
                        for (int i=y;i>0;--i) fk.push_back(ret[w-i]);
                        for (int i=x;i<w-y;++i) fk.push_back(ret[i]);
                        for (int i=0;i<x;++i) fk.push_back(ret[i]);
                        if (st.find(fk)!=st.end()) continue;
                        st.insert(fk), que.push(fk), mp[fk]={x,y,ret};
                    }
                }
            }
            vector<int> aaa=val;
            sort(aaa.begin(),aaa.end());
            assert(st.find(aaa)!=st.end());
            vector<pair<int,int>> ans2;
            while (1){
                bool ok=1;
                for (int i=0;i<val.size();++i){
                    if (aaa[i]==val[i]) continue;
                    ok=0;
                }
                if (ok) break;
                auto [x,y,v]=mp[aaa];
                aaa=v;
                ans2.push_back({x,y});
            }
            reverse(ans2.begin(),ans2.end());
            for (auto [x,y]:ans2){
                vector<int> fk;
                int w=len.size();
                int xx=0, yy=0;
                for (int i=0;i<x;++i) xx+=len[i];
                for (int j=1;j<=y;++j) yy+=len[w-j];
                upd(xx,yy);
                ans.push_back({xx,yy});
                for (int i=y;i>0;--i) fk.push_back(len[w-i]);
                for (int i=x;i<w-y;++i) fk.push_back(len[i]);
                for (int i=0;i<x;++i) fk.push_back(len[i]);
                len=fk;
            }
            // for (auto [u,v]:ans2) ans.push_back({u,v}), upd(u,v);
            cout<<ans.size()<<"\n";
            for (auto [u,v]:ans) cout<<u<<" "<<v<<"\n";
            for (int i=1;i<=n;++i) assert(p[i]==i);
            // cout<<endl;
        };
        solve();
    }
}
