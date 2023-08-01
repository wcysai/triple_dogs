#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int M=1000000009;
typedef long long ll;
int n,m,f[1005][1005],op;
bool ban[2005];
set<int> R,C;
bool check(int n,int m){
    R.clear(); C.clear();
    int num=0;
    for (int i=0;i<n;i++)
    for (int j=0;j<m;j++) num+=f[i][j];
    if (num*2!=n*m) return 0;
    for (int i=0;i<n;i++){
        int p=0;
        for (int j=0;j<m;j++){
            p=(p*2+f[i][j])%M;
        }
        if (R.find(p)==R.end()) R.insert(p); else return 0;
    }
    for (int i=0;i<m;i++){
        int p=0;
        for (int j=0;j<n;j++){
            p=(p*2+f[j][i])%M;
        }
        if (C.find(p)==C.end()) C.insert(p); else return 0;
    }
    return 1;
}
void print(int n,int m,int op){
    cout << "YES" << endl;
    if (!op){
        for (int i=0;i<n;i++){
            for (int j=0;j<m;j++) cout << f[i][j];
            cout << endl;
        }
    } else {
        for (int i=0;i<m;i++){
            for (int j=0;j<n;j++) cout << f[j][i];
            cout << endl;
        }
    }
}
void solve(int n,int m){
    op=0;
    if (n<m) swap(n,m),op=1;
    if (n*m%2==1){
        //cout << "NO" << endl;
        return;
    }
    if (n>(1<<m)){
        //cout << "NO" << endl;
        return;
    }
    if (m==1){
        f[0][0]=0;
        f[1][0]=1;
        print(n,m,op);
        return;
    }
    int s=1;
    while ((1<<s)<n) s++;
    memset(ban,0,sizeof(ban));
    int tot=1<<(s-1);
    if (n%2==1){
        for (int i=0;i<m/2;i++){
            f[n-1][i]=0;
            f[n-1][i+m/2]=1;
        }
        int mask=0;
        for (int i=0;i<s;i++) if (f[n-1][i]) mask|=1<<i;
        tot--; ban[mask]=ban[(1<<s)-1-mask]=1;
    }
    for (int i=(1<<(s-1))-1;i>=0;i--) if (!ban[i]&&tot>n/2){
        tot--; ban[i]=ban[(1<<s)-1-i]=1;
    }
    int pos=0;
    for (int i=0;i<(1<<s);i++) if (!ban[i]){
        for (int j=0;j<s;j++) f[pos][j]=(i>>j)&1;
        pos++;
    }
    int col=s;
    while (col+2<=m){
        int r=(col-s)/2;
        for (int i=0;i<n/2*2;i++) f[i][col]=0,f[i][col+1]=1;
        swap(f[r][col],f[r][col+1]);
        col+=2;
    }
    if (col<m){
        for (int i=0;i<n/2;i++) f[i][col]=1,f[i+n/2][col]=0;
        col++;
    }
    if (!check(n,m)){
        cout<<n<<' '<<m<<endl;
    }
    //print(n,m,op);
}
int main(){
    for (int i=1;i<=135;i++)
    for (int j=1;j<=135;j++) solve(i,j);
    return 0;
    int _; cin >> _;
    while (_--){
        cin >> n >> m;
        solve(n,m);
    }
}

