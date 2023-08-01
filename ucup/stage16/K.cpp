#include<bits/stdc++.h>
#define int long long
using namespace std;

const int N=1e6+7;
const int mod=998244353;
int f[N],rf[N];
int modpow(int u,int v){
	int ans=1, t=u;
	while (v){
		if (v&1) ans=ans*t%mod;
		t=t*t%mod, v>>=1;
	}
	return ans;
}
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	f[0]=1;
	for (int i=1;i<N;++i) f[i]=f[i-1]*i%mod;
	rf[N-1]=modpow(f[N-1],mod-2);
	for (int i=N-1;i>0;--i) rf[i-1]=rf[i]*i%mod;
	auto C=[&](int u,int v){
	    return f[u]*rf[v]%mod*rf[u-v]%mod;
	};
	int n,k;
	cin>>n>>k;
	int inv2=(mod+1)/2;
	int tmp=(n+1)*inv2%mod;
	tmp=tmp*modpow(n,k)%mod;
	if (k&1){
		cout<<tmp;
		return 0;
	}
	int ans=0;
	for (int i=1;i<=n;++i){
		ans=(ans+C(k,k/2)*modpow(i,k/2)%mod*modpow(n-i,k/2))%mod;
	}
	tmp=(tmp-ans*inv2%mod+mod)%mod;
	cout<<tmp;
	return 0;
}
