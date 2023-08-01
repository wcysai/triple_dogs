#include<bits/stdc++.h>
using namespace std;
int n,a[1050505];
int main(){
    cin >> n;
    for (int i=1;i<=n;i++) cin >> a[i];
    sort(a+1,a+n+1);
    cout << max(0,a[n])+max(0,a[n-1]) << endl;
}