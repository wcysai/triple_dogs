#include<bits/stdc++.h>
using namespace std;
string a[100005];
int n,ans,ok[100005];
map<string,int> f;
int gid(string t){
    if (f.find(t)==f.end()) return -1;
    return f[t];
}
bool check(int x){
    if (x==-1) return 0;
    if (ok[x]!=-1) return ok[x];
    int &ret=ok[x];
    if (a[x].size()==1) return ret=1;
    string t1,t2;
    for (int i=0;i<a[x].size()-1;i++) t1+=a[x][i],t2+=a[x][i+1];
    return ret=check(gid(t1))&&check(gid(t2));
}
int main(){
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> a[i];
        f[a[i]]=i;
    }
    memset(ok,-1,sizeof(ok));
    for (int i=1;i<=n;i++){
        if (check(i)) ans=max(ans,(int)a[i].size());
    }
    cout << ans << endl;
}