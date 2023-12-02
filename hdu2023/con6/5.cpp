#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn=1005;
const int M=1000000007;
int a[maxn][maxn],r[maxn][maxn],x[maxn][maxn],c[maxn][maxn],b[maxn][maxn];
int r2[maxn][maxn],x2[maxn][maxn],c2[maxn][maxn];
int sa[maxn][maxn],sb[maxn][maxn],n,m;
int _;
void add(int &x,int y){x+=y;if(x>=M)x-=M;}
bool check(int xl,int xr,int yl,int yr){
    return sa[xr][yr]-sa[xl-1][yr]-sa[xr][yl-1]+sa[xl-1][yl-1]==(xr-xl+1)*(yr-yl+1);
}
void solve(){
    memset(r,0,sizeof(r));
    memset(x,0,sizeof(x));
    memset(c,0,sizeof(c));
    memset(r2,0,sizeof(r));
    memset(x2,0,sizeof(x));
    memset(c2,0,sizeof(c));
    cin >> n >> m;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            cin >> a[i][j];
            sa[i][j]=sa[i-1][j]+sa[i][j-1]-sa[i-1][j-1]+a[i][j];
        }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            cin >> b[i][j];
            sb[i][j]=((ll)sb[i-1][j]+sb[i][j-1]-sb[i-1][j-1]+b[i][j])%M;
        }
    int ans=0;
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            int L=0,R=min(n-i+1,n-j+1)+1;
            while (R-L>1){
                int mid=(L+R)>>1;
                if (check(i,i+mid-1,j,j+mid-1)) L=mid; else R=mid;
            }
            add(ans,1ll*L*(L+1)/2*sb[i-1][j-1]%M);
            r[i-1][j]++;
            r[i-1][j+L]--;
            r2[i-1][j]-=j-1;
            r2[i-1][j+L]+=j-1;
            c[i][j-1]++;
            c[i+L][j-1]--;
            c2[i][j-1]-=i-1;
            c2[i+L][j-1]+=i-1;
            x[i][j]++;
            x[i+L][j+L]--;
            x2[i][j]-=min(i,j)-1;
            x2[i+L][j+L]+=min(i,j)-1;
        }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++){
            r[i][j]+=r[i][j-1];
            c[i][j]+=c[i-1][j];
            x[i][j]+=x[i-1][j-1];
            r2[i][j]+=r2[i][j-1];
            c2[i][j]+=c2[i-1][j];
            x2[i][j]+=x2[i-1][j-1];
            int cof=((1ll*x[i][j]*min(i,j)%M+x2[i][j]-(1ll*r[i][j]*j%M+r2[i][j])-(1ll*c[i][j]*i%M+c2[i][j]))%M+M)%M;
            add(ans,1ll*cof*sb[i][j]%M);
        }
    cout << ans << endl;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    cin >> _;
    while (_--) solve();
}
