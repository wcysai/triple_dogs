// #pragma comment(linker, "/STACK:102400000,102400000")
#pragma GCC optimize("O3")
#pragma GCC optimize("O2")
// #pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
// #pragma GCC optimize("trapv")
#include<bits/stdc++.h>
// #include <bits/extc++.h>
// #define int __int128_t
#define int long long
#define double long double
// #define i128 long long
// #define double long double
using namespace std;
 
#define rep(i,n) for (int i=0;i<(int)(n);++i)
#define rep1(i,n) for (int i=1;i<=(int)(n);++i)
#define range(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define pb push_back
#define F first
#define S second
 
typedef long long ll;
typedef unsigned long long ull;
// typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

mt19937 rng(1234);
const int N=200017;
const int mod=1e9+7;
const int INF=LLONG_MAX/4;

int a[N],pref[N];
signed main(){
  int _;
  cin>>_;
  while (_--){
    int n;
    cin>>n;
    rep1(i,n) cin>>a[i];
    rep1(i,n) pref[i]=pref[i-1]^a[i];
    if (pref[n]){
        if (n==1) cout<<"NO\n";
        else {
            cout<<"YES\n";
            cout<<2<<"\n";
            cout<<1<<" "<<1<<"\n";
            cout<<2<<" "<<n<<"\n";
        }
    } 
    else{
        int idx1=-1,val1=-1, idx2=-1;
        rep1(i,n){
            if (pref[i]){
                if (val1==-1) idx1=i, val1=pref[i];
                if (pref[i]==val1) continue;
                else idx2=i;
            }
        }
        if (idx2==-1) cout<<"NO\n";
        else{
            cout<<"YES\n";
            cout<<3<<"\n";
            cout<<1<<" "<<idx1<<"\n";
            cout<<idx1+1<<" "<<idx2<<"\n";
            cout<<idx2+1<<" "<<n<<"\n";
        }
    }
  }
}

/*
1
6 23
22 1
3 6
3 9
12 4
13 1
16 6
*/
