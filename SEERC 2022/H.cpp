#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 505
#define INF 1000000000
#define MOD 1000000007
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
int n,k,p[MAXN];
vector<int> cur;
vector<P> op;
void ins(int x)
{
    op.push_back(P(1,2));
    vector<int> tmp;
    while(cur.size()&&cur.back()<x)
    {
        tmp.push_back(cur.back());
        op.push_back(P(3,1));
        cur.pop_back();
    }
    op.push_back(P(2,3));
    cur.push_back(x);
    while(tmp.size())
    {
        cur.push_back(tmp.back());
        op.push_back(P(1,3));
        tmp.pop_back();
    }
}
int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&p[i]);
    for(int i=n;i>=1;i--) ins(p[i]);
    printf("%d\n",(int)op.size());
    for(auto p:op) printf("%d %d\n",p.F,p.S);
    return 0;
}

