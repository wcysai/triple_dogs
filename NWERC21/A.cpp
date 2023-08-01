#include<bits/stdc++.h>
#define MAXN 1000005
#define INF 1000000000
#define MOD 1000000007
using namespace std;
#define int long long
typedef long double db;

string s;
signed main(){
    for (int i='a';i<='z';++i) s.push_back(i);
    for (int i='0';i<='9';++i) s.push_back(i);
    for (int i='A';i<='Z';++i) s.push_back(i);
    auto query=[&](string t){
        cout<<t<<endl;
        string a,b,c,d;
        cin>>a>>b;
        if (b=="GRANTED") return 100ll;
        cin>>c>>d;
        string e=c.substr(1,c.size()-1);
        int ans=0;
        for (auto c:e){
            ans*=10;
            ans+=c-'0';
        }
        assert(ans%9==5);
        return (ans-5)/9;
    };
    int idx=-1;
    for (int i=1;i<=20;++i){
        string t;
        for (int j=0;j<i;++j) t.push_back('A');
        auto ret=query(t);
        if (ret==100) return 0;
        if (ret>0) {idx=i; break;}
    }
    string ans;
    for (int i=1;i<=idx;++i){
        string pad;
        for (int j=0;j+i<idx;++j) pad.push_back('A');
        for (auto c:s){
            string tmp=ans;
            tmp.push_back(c);
            tmp+=pad;
            auto ret=query(tmp);
            if (ret==100) return 0;
            if (ret>i) {ans.push_back(c); break;}
        }
    }
}

/*ACCESS DENIED (5 ms)*/