#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1e6+5;
const int N=182;
const int M=16;
int _;
ll x,y,k,p;
void solve(){
    cin >> x >> y >> k;
    if (k==0){
        cout << abs(x-y) << endl;
        return;
    }
    if (x==y){
        cout << 0 << endl;
        return;
    }
    if (x>y) swap(x,y);
    p=1; while (p<=k) p<<=1;
    if (x/p==y/p){
        if ((x^y)<=k) cout << 1 << endl;
        else cout << 2 << endl;
        return;
    }
    ll tmp,ans=0;
    tmp=x/p*p+p-1;
    if (tmp==x) ans+=0; else if ((tmp^x)<=k) ans+=1; else ans+=2;
    tmp=y/p*p;
    if (tmp==y) ans+=0; else if ((tmp^y)<=k) ans+=1; else ans+=2;
    ans++; 
    if (p==k+1) ans+=2*(y/p-x/p-1); else ans+=3*(y/p-x/p-1);
    cout << ans << endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> _;
    while (_--) solve();
}