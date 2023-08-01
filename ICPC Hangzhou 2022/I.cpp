#include<bits/stdc++.h>
using namespace std;
mt19937_64 gen(time(0));
const int N=1000000000;
int ask(int x){
    cout << "walk " << x << endl;
    fflush(stdout);
    int ret; cin >> ret;
    return ret;
}
const int E=10000;
const int B=2000;
int p[2005],q[2005];
int main(){
    int mx=0;
    for (int i=0;i<E-B*2-1;i++){
        mx=max(mx,ask(gen()%(N+1)));
    }
    for (int i=B-1;i>=0;i--) p[i]=ask(1);
    q[0]=ask(mx);
    for (int i=1;i<B;i++) q[i]=ask(B);
    int ans=N*2;
    for (int i=0;i<B;i++)
        for (int j=0;j<B;j++)
            if (p[i]==q[j]) ans=min(ans,mx+i+j*B);
    assert(ans<=N);
    cout << "guess " << ans << endl;
    return 0;
}