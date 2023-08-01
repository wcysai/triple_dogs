#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int t,n,k,a[MAXN];
string str;
vector<int> v;
bool isrep(vector<int> &v){
    if(!v.size()) return false;
    for(int i=1;i<(int)v.size();i++){
        if(v[i]!=v[i-1]) return false;
    }
    return true;
}
vector<int> dec(vector<int> &a,vector<int> &b){
    vector<int> z((int)a.size());
    int lend=0;
    for(int i=0;i<(int)a.size();i++){
        int y=(i<(int)b.size()?b[i]:0);
        z[i]=(a[i]-y-lend);
        if(z[i]<0){
            z[i]+=10;
            lend=1;
        }
        else lend=0;
    }
    if(lend||z.back()<0) return vector<int>();
    while(z.size()>0&&z.back()==0) z.pop_back();
    return z;
}
void print(vector<int> &a){
    for(int i=(int)a.size()-1;i>=0;i--) printf("%d",a[i]);
}
int main()
{
    scanf("%d",&t);
    while(t--){
        cin>>str;
        v.clear();
        for(int i=0;i<(int)str.size();i++){
            v.push_back(str[i]-'0');
        }
        reverse(v.begin(),v.end());
        int sz=(int)v.size();
        vector<int> a;
        bool f=false;
        for(int i=1;i<=9;i++){
            if(f) continue;
            a.clear();
            a.resize(sz);
            for(int j=0;j<sz;j++) a[j]=i;
            vector<int> b=dec(v,a);
            if(isrep(b)) {
                f=true;
                print(a); printf(" ");
                print(b); printf("\n");
                break;
            }
        }
        for(int i=1;i<=9;i++){
            if(f) continue;
            a.clear();
            a.resize(sz-1);
            for(int j=0;j<sz-1;j++) a[j]=i;
            vector<int> b=dec(v,a);
            if(isrep(b)) {
                f=true;
                print(a); printf(" ");
                print(b); printf("\n");
                break;
            }
        }
        assert(f);
    }
    return 0;
}

