#include<bits/stdc++.h>
#define MAXN 100005
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n;
set<string> st;
bool check(string &s)
{
    for(int i=0;i<=(int)s.size()-3;i++)
    {
        if(s[i]=='b'&&s[i+1]=='i'&&s[i+2]=='e') return true;
    }
    return false;
}
int main()
{
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        int t;
        scanf("%d",&t);
        bool f=false;
        for(int j=0;j<t;j++)
        {
            string str;
            cin>>str;
            if(check(str)&&!st.count(str))
            {
                cout<<str<<endl;
                st.insert(str);
                f=true;
            }
        }
        if(!f) cout<<"Time to play Genshin Impact, Teacher Rice!"<<endl;
    }
    return 0;
}