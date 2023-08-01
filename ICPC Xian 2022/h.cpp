#include<bits/stdc++.h>
#define pb push_back
using namespace std;
int vis[65537],c[65537],n,x,y,z;
typedef vector<int>vi;
vi ax,ay,az;
void solve(){
    cin >> n >> x >> z >> y; //x:& y:^ z:|
    for (int i=0;i<n;i++) c[i]=0,vis[i]=0;
    for (int i=0;i<n;i++){
        int p; cin >> p;
        c[p]++;
    }
    ax.clear(); ay.clear(); az.clear();
    if (!x){
        for (int i=n-1;i>=0;i--) if (c[i]){
            if (c[i]%2==0&&z>0){
                z--; c[i]--; 
                az.pb(i);
            } 
            while (c[i]){
                c[i]--;
                if (y) y--,ay.pb(i); else z--,az.pb(i);
                vis[i]^=1;
            }
        }
        for (auto u:az) vis[u]=1;
        for (int i=n-1;i>=0;i--) cout << vis[i]; cout << endl;
        for (int i=0;i<ay.size();i++) cout << "^";
        for (int i=0;i<az.size();i++) cout << "|"; cout << endl;
        for (int i=0;i<ay.size();i++) cout << ay[i] << " ";
        for (int i=0;i<az.size();i++) cout << az[i] << " "; cout << endl;
    } else {
        if (!(y+z)){
            for (int i=n-1;i>=0;i--) cout << 0; cout << endl;
            for (int i=0;i<x;i++) cout << "&"; cout << endl;
            for (int i=0;i<n;i++)
                for (int j=0;j<c[i];j++)
                    cout << i << " "; 
            cout << endl;
            return;
        }
        if (z){
            int cnt=y+z,pos=-1;
            for (int i=n-1;i>=0;i--) if (c[i]){
                if (cnt){
                    cnt--; 
                    vis[i]=1;
                    c[i]--;
                    if (pos==-1&&c[i]>0){
                        az.pb(i); z--;
                        pos=i;
                    } else {
                        if (y) ay.pb(i),y--;
                        else az.pb(i),z--;
                    }
                } else {
                    pos=i;
                }
            }
            assert(pos!=-1);
            c[pos]--; 
            for (int i=n-1;i>=0;i--) cout << vis[i]; cout << endl;
            for (int i=0;i<y;i++) cout << "^";
            for (int i=0;i<z;i++) cout << "|"; 
            for (int i=0;i<x;i++) cout << "&";
            for (int i=0;i<ay.size();i++) cout << "^"; 
            for (int i=0;i<az.size();i++) cout << "|"; cout << endl;
            for (int i=0;i<n;i++)
                for (int j=0;j<c[i];j++)
                    cout << i << " ";
            cout << pos << " ";
            for (int i=0;i<ay.size();i++) cout << ay[i] << " ";
            for (int i=0;i<az.size();i++) cout << az[i] << " "; cout << endl;
        } else {
            int pos=-1;
            for (int i=n-1;i>=0;i--) if (c[i]){
                if (y){
                    ay.pb(i); y--;
                    vis[i]=1;
                    c[i]--;
                } else {
                    pos=i;
                }
            }
            if (pos==-1&&x==1){
                for (int i=n-1;i>=0;i--) if (c[i]%2==1) pos=i;
            }
            int ban=-1;
            if (pos==-1&&x==1){
                for (int i=0;i<n;i++) if (vis[i]) {vis[i]=0;ban=i;pos=i;break;}
            }
            if (pos!=-1){
                if (ban==-1) c[pos]--;
                for (int i=n-1;i>=0;i--) cout << vis[i]; cout << endl;
                if (ban!=-1){
                    for (int i=0;i<y+1;i++) cout << "^";
                    for (int i=0;i<x;i++) cout << "&";
                    for (int i=0;i<ay.size()-1;i++) cout << "^"; cout << endl;
                } else {
                    for (int i=0;i<y;i++) cout << "^";
                    for (int i=0;i<x;i++) cout << "&";
                    for (int i=0;i<ay.size();i++) cout << "^"; cout << endl;
                }
                for (int i=0;i<n;i++)
                    for (int j=0;j<c[i];j++)
                        cout << i << " ";
                cout << pos << " ";
                for (int i=0;i<ay.size();i++){
                    if (ay[i]!=ban) cout << ay[i] << " "; 
                }
                cout << endl;
                return;
            }
            assert(x>1);
            int u=-1,v=-1;
            for (int i=0;i<n;i++) if (c[i]>0){
                if (u==-1) u=i;
                else if (v==-1) v=i;
            }
            if (u!=-1&&v!=-1){
                c[u]--; c[v]--;
                for (int i=n-1;i>=0;i--) cout << vis[i]; cout << endl;
                for (int i=0;i<y;i++) cout << "^";
                for (int i=0;i<x;i++) cout << "&";
                for (int i=0;i<ay.size();i++) cout << "^"; cout << endl;
                for (int i=0;i<n;i++)
                    for (int j=0;j<c[i];j++)
                        cout << i << " ";
                cout << u << " " << v << " ";
                for (int i=0;i<ay.size();i++) cout << ay[i] << " "; cout << endl;
            } else {
                int ban=-1;
                if ((c[u]-x)%2==1){
                    for (int i=0;i<n;i++) if (vis[i]){
                        vis[i]=0;
                        ban=i; break;
                    }
                }
                for (int i=n-1;i>=0;i--) cout << vis[i]; cout << endl;
                if (ban!=-1){
                    for (int i=0;i<y+1;i++) cout << "^";
                    for (int i=0;i<x;i++) cout << "&";
                    for (int i=0;i<ay.size()-1;i++) cout << "^"; cout << endl;
                } else {
                    for (int i=0;i<y;i++) cout << "^";
                    for (int i=0;i<x;i++) cout << "&";
                    for (int i=0;i<ay.size();i++) cout << "^"; cout << endl;
                }
                for (int i=0;i<n;i++)
                    for (int j=0;j<c[i];j++)
                        cout << i << " ";
                if (ban!=-1) cout << ban << " ";
                //cout << u << " " << v << " ";
                for (int i=0;i<ay.size();i++){
                    if (ay[i]!=ban) cout << ay[i] << " "; 
                }
                cout << endl;
            }
        }
    }
}
int main(){
    int T; cin >> T;
    while (T--) solve();
}