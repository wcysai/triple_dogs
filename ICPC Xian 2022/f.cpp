#include<bits/stdc++.h>
using namespace std;
char s[5];
int c1,c2,n,ans;
int main(){
    cin >> n >> c1 >> c2; 
    c1=min(c1,c2);
    c2=min(c2,c1*2);
    while (n--){
        cin >> s;
        if (s[0]==s[1]||s[0]==s[2]||s[1]==s[2]) ans+=c1+c2;
        else ans+=c1*3;
    }
    cout << ans << endl;
}