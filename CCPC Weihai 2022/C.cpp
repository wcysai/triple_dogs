    #include<bits/stdc++.h>
    using namespace std;
    #define int long long
    // #define __int128_t long long

    const int N=50017;
    const int INF=1e18;
    int a[N],b[N];
    int c[N];
    signed main(){
        ios::sync_with_stdio(false);
        cin.tie(0), cout.tie(0);
        int _;
        cin>>_;
        while (_--){
            int n,k;
            cin>>n>>k;
            for (int i=0;i<n;++i) cin>>a[i];
            for (int i=0;i<k;++i) cin>>b[i];
            int L=0, R=1e18;
            while (L<R){
                int md=(L+R)>>1;
                auto solve=[&](int u){
                    __int128_t fk=0;
                    for (int i=0;i<n;++i){
                        if ((__int128_t)a[i]*u>INF) return 0;
                        c[i]=a[i]*u;
                        fk+=c[i];
                    }
                    if (fk>INF) return 0;
                    int rem=0;
                    for (int i=k-1;i>-1;--i){
                        int sum=2*rem;
                        for (int j=0;j<n;++j){
                            sum+=c[j]/(1<<i);
                            c[j]%=(1<<i);
                        }
                        if (sum>=b[i]) rem=sum-b[i];
                        else {
                            rem=0;
                            sort(c,c+n);
                            reverse(c,c+n);
                            int kkk=min(b[i]-sum,n);
                            for (int j=0;j<kkk;++j) c[j]=0;
                        } 
                    }
                    if (rem) return 0;
                    else return 1;
                };
                if (solve(md+1)) L=md+1;
                else R=md;
            }
            cout<<L<<"\n";
        }
    }