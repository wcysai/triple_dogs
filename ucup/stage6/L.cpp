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
int n,k,a[MAXN];
map<string,string> mp;
string str;
int main()
{
    mp["CCC"]="STOP";
    mp["ACG"]="NEXT";
    mp["UGA"]="PREV";
    mp["UGC"]="INC";
    mp["UAC"]="DEC";
    mp["GCG"]="OUT";
    mp["UCC"]="IN";
    mp["AGG"]="BEGIN";
    mp["UGU"]="END";
    cin>>str;
    int space=0;
    for(int i=0;i<(int)str.size();i+=3) 
    {
        string t=mp[str.substr(i,3)];
        if(t=="END") space-=2;
        for(int j=0;j<space;j++) printf(" ");
        cout<<mp[str.substr(i,3)]<<endl; 
        if(t=="BEGIN") space+=2;
    }
    return 0;
}

