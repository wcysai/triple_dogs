#include<bits/stdc++.h>
using namespace std;

const int N=100000;
int n,k;
int a[N];
int main(){
    cin>>n>>k;
    for (int i=1;i<=n;++i) cin>>a[i];
    for (int i=n+1;i<N;++i) a[i]=max(2*a[i-1]-a[i-2],0);
    int idx=-1;
    for (int i=1;i<N;++i){
        if (a[i]<k) {cout<<"Python 3."<<i<<" will be faster than C++"; return 0;}
    }
    cout<<"Python will never be faster than C++";
}