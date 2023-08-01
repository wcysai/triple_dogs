#include<bits/stdc++.h>
using namespace std;
 
map<string,int> st;
int n;
int cnt[10];
int main(){
    cin>>n;
    for (int i=0;i<n;++i){
        for (int j=1;j<=5;++j){
            string s;
            cin>>s;
            st[s]=j;
        }
    }
    int m,sz;
    cin>>m;
    for (int i=1;i<=m;++i){
        string s;
        int t;
        cin>>s>>t;
        cnt[t]++;
        if(st.find(s)!=st.end()) sz++;
    }
    int fk=sz;
    for (int i=1;i<=5;++i) fk=min(fk,cnt[i]);
    cout<<fk;
}