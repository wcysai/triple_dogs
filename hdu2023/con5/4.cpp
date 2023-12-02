#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 200005
using namespace std;
typedef long long ll;
struct PAM{
    int s[MAXN],now,ans;
    int nxt[MAXN][26],fail[MAXN],f[MAXN],l[MAXN],last,tot;
    int cnt[MAXN],id[MAXN],cont[MAXN];
    vector<int> G[MAXN];
    void clear(){ //1: odd root 0: even root
        for(int i=1;i<=tot;i++) {G[i].clear(); cont[i]=0;}
        s[0]=l[1]=-1;
        fail[0] = tot = now =1;
        last = l[0]=0;
        memset(nxt[0],0,sizeof(nxt[0]));
        memset(nxt[1],0,sizeof(nxt[1]));
        memset(cnt,0,sizeof(cnt));
    }
    PAM(){clear();}
    int newnode(int len){
        tot++;
        memset(nxt[tot],0,sizeof nxt[tot]);
        fail[tot]=0;
        l[tot]=len;
        return tot;
    }
    int get_fail(int x){
        while (s[now-l[x]-2]!=s[now-1]) x=fail[x];
        return x;
    }
    void add(int ch){
        s[now++] = ch;
        int cur = get_fail(last);
        if(!nxt[cur][ch]){
            int tt = newnode(l[cur]+2);
            fail[tt] = nxt[get_fail(fail[cur])][ch];
            nxt[cur][ch] = tt;
            if(l[fail[tt]]<=l[tt]>>1) f[tt]=fail[tt];
            else{
                int p=f[cur];
                while((l[p]+2>l[tt]>>1)||(s[now-1]!=s[now-l[p]-2])) 
                {
                    p=fail[p];
                }
                f[tt]=nxt[p][ch];
            }
        }
        last=nxt[cur][ch];
        id[now-1]=last;
    }
    void solve(string str){
        for (int i=0;i<(int)str.size();i++) add(str[i] - 'a');
        for(int i=2;i<=tot;i++) if(l[i]%2==0&&l[f[i]]*2==l[i])  cont[i]++;
        for(int i=2;i<=tot;i++) cont[i]+=cont[fail[i]];
        ll ans=0;
        for(int i=1;i<=(int)str.size();i++) {ans+=cont[id[i]]; printf("%lld ",ans);}
        printf("\n");
    }
}pam;
int T,n;
string str;
int main()
{
    cin>>T;
    while(T--){
        cin>>str;
        pam.clear();
        pam.solve(str);
    }
    return 0;
}
