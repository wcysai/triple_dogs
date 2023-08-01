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
int T,n,k,a[MAXN];
map<string,char> mp;
string str;
int main()
{
    mp["UUU"]=mp["UUC"]='F';
    mp["UUA"]=mp["UUG"]=mp["CUU"]=mp["CUC"]=mp["CUA"]=mp["CUG"]='L';
    mp["AUU"]=mp["AUC"]=mp["AUA"]='I';
    mp["AUG"]='M';
    mp["GUU"]=mp["GUC"]=mp["GUA"]=mp["GUG"]='V';
    mp["UCU"]=mp["UCC"]=mp["UCA"]=mp["UCG"]=mp["AGU"]=mp["AGC"]='S';
    mp["CCU"]=mp["CCC"]=mp["CCA"]=mp["CCG"]='P';
    mp["ACU"]=mp["ACC"]=mp["ACA"]=mp["ACG"]='T';
    mp["GCU"]=mp["GCC"]=mp["GCA"]=mp["GCG"]='A';
    mp["UAU"]=mp["UAC"]='Y';
    mp["CAU"]=mp["CAC"]='H';
    mp["CAA"]=mp["CAG"]='Q';
    mp["AAU"]=mp["AAC"]='N';
    mp["AAA"]=mp["AAG"]='K';
    mp["GAU"]=mp["GAC"]='D';
    mp["GAA"]=mp["GAG"]='E';
    mp["UGU"]=mp["UGC"]='C';
    mp["UGG"]='W';
    mp["CGU"]=mp["CGC"]=mp["CGA"]=mp["CGG"]=mp["AGA"]=mp["AGG"]='R';
    mp["GGU"]=mp["GGC"]=mp["GGA"]=mp["GGG"]='G';
    mp["UAA"]=mp["UAG"]=mp["UGA"]='Z';
    scanf("%d",&T);
    while(T--){
        cin>>str;
        string ans="";
        for(int i=0;i<(int)str.size();i+=3){
            char ch=mp[str.substr(i,3)];
            if(ch=='Z') break;
            else ans+=ch;
        }
        cout<<ans<<endl;
    }
    return 0;
}

