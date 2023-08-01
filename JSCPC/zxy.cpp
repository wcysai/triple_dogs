#include<bits/stdc++.h>
using namespace std;

map<vector<int>,int> dp;

int n,t;

int solve(vector<int> &d){
    // cout<<d.size()<<endl;
    // for (auto c:d) cerr<<c<<" ";
    // cerr<<endl;
    if (d.size()==0) return 0;
    if (dp.find(d)!=dp.end()) return dp[d];
    int m=d.size();
    int ans=0;
    for (int i=0;i<m;++i){
        vector<int> fk;
        for (int j=0;j<m;++j) if (i!=j) fk.push_back(d[j]);
        if (d[i]<=2*t+1) ans=max(ans,d[i]-solve(fk));
        else{
            for (int k=0;k<=d[i];++k){
                if (k>d[i]-(2*t+1)-k) break;
                vector<int> tmp=fk;
                if (k) tmp.push_back(k);
                if (d[i]-(2*t+1)-k) tmp.push_back(d[i]-2*t-1-k);
                sort(tmp.begin(), tmp.end());
                ans=max(ans,2*t+1-solve(tmp));
            }
        } 
    }
    return dp[d]=ans;
}
set<vector<int>> zeros;
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // freopen("input.txt","r",stdin);
    // freopen("answer.txt","w",stdout);
    // int T=15*15*15*15;
    // cout<<T<<endl;
    int T;
    cin>>T;
    while (T--){
        cin>>n>>t;
        // n=4, t=1;
        vector<int> a(n,0);
        for (auto &c:a) cin>>c;
        // int tmp=T;
        // for (int i=0;i<=3;++i){
        //     a[i]=1+tmp%15, tmp/=15;
        // }
        // cout<<n<<" "<<t<<endl;
        // for (auto c:a) cout<<c<<" ";
        // cout<<endl;
        cout<<solve(a)<<endl;
        // sort(a.begin(), a.end());
        // if (!solve(a)&&zeros.find(a)==zeros.end()){
        //     zeros.insert(a);
        //     for (auto c:a) cerr<<c<<" ";
        //     cerr<<endl;
        // }
    }
}
