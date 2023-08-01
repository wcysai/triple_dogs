#include<bits/stdc++.h>
using namespace std;
struct node{
    int a,b,c;
};
map<string,node> f;
int n,sum,ans;
int main(){
    cin >> n;
    while (n--){
        string s,t; int x;
        cin >> s >> t >> x;
        if (t[0]=='l') f[s].a+=x;
        else if (t[0]=='r') f[s].b+=x;
        else f[s].c+=x;
        sum+=x;
    }
    for (auto nd:f){
        node t=nd.second;
        ans+=max(max(t.a,t.b),1);
    }
    if (ans<sum) printf("%d\n",ans+1); else puts("impossible");
}