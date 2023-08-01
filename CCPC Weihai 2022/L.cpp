#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=5007;
int n;
int a[N],x[N];
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin>>n;
    for (int i=0;i<(1<<n);++i) cin>>a[i];
    for (int i=0;i<=(1<<n-1);++i){
        int k=0;
        for (int j=0;j<=(1<<n-1);++j){
            if (j==i) continue;
            a[j]-=2*k, k++;
        }
    }
    for (int i=(1<<n-1)+1;i<(1<<n);++i){
        for (int j=0;j<(1<<n-1)-1;++j) a[j]-=2*j;
        a[i]-=2*(1<<n-1)-2;
    }
    for (int i=(1<<n-1)+1;i<(1<<n);++i) {
        x[i]=a[i];
        for (int j=0;j<(1<<n-1)-1;++j) a[j]-=x[i];
    }
    int sum=0;
    for (int i=0;i<=(1<<n-1);++i) cerr<<a[i]<<" ";
    cerr<<endl;
    for (int i=0;i<=(1<<n-1);++i) sum+=a[i];
    if (sum%(1<<n-1)){
        cout<<"NO";
        return 0;
    } 
    sum/=(1<<n-1);
    for (int i=0;i<=(1<<n-1);++i) x[i]=sum-a[i];
    cout<<"YES\n";
    cout<<(1<<n)<<endl;
    for (int i=0;i<=(1<<n-1);++i){
        int k=0;
        cout<<x[i]<<" ";
        for (int j=0;j<=(1<<n-1);++j){
            if (j==i) continue;
            cout<<j<<" ";
            a[i]-=2*k, k++;
        }
        cout<<"\n";
    }
    for (int i=(1<<n-1)+1;i<(1<<n);++i){
        cout<<x[i]<<" ";
        for (int j=0;j<(1<<n-1)-1;++j) cout<<j<<" ";
        cout<<i<<"\n";
    }
}